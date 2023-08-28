import serial
import pynmea2
from pyfingerprint.pyfingerprint import PyFingerprint
import pymysql
import time
from tkinter import *

def wait_for_finger(f):
    # 지문 인식을 기다릴 때 호출되는 함수. 터미널 창에 문자열 표시.
    while True:
        try:
            print('지문 인식 대기 중...')
            while not f.readImage():
                pass
            return True

        except Exception as e:
            print('오류 발생:', str(e))
            time.sleep(1)  # 1초 대기 후 다시 시도

def update_message(text, color="black"):
    # Tkinter 창의 메시지를 업데이트하는 함수.
    message_label.config(text=text, fg=color)
    tk.update()
    tk.update_idletasks()

if __name__ == '__main__':
    # 아두이노 및 GPS 모듈 시리얼 연결 설정 및 Tkinter GUI 초기화
    ser = serial.Serial('/dev/ttyARDU', 115200, timeout=5.0)  # 아두이노용 시리얼 포트 설정. /dev/ttyACM0를 /dev/ttyARDU로 고정하여 사용.
    ser_gps = serial.Serial('/dev/ttyUSB0', baudrate=9600, timeout=5.0)  # GPS 모듈용 시리얼 포트 설정
    ser.flush()
    ser_gps.flush()

    tk = Tk()
    tk.title("충격")
    tk.attributes('-fullscreen', True)
    tk.configure(bg="black")

    # 주행 상태에 따라 메세지를 표시하는 레이블을 생성.
    message_label = Label(tk, text="주행 중...", bg="black", fg="white", font=('NanumMyeongjo', 20), anchor='center',
                          justify='center')
    message_label.place(relx=0.5, rely=0.5, anchor='center')

    try:
        while True:
            if ser.in_waiting > 0:
                data = ser.read()
                try:
                    if data == b'G':  # 충격 신호 수신

                        data = b'S'
                        conn = pymysql.connect(host="localhost", user="a2b2", passwd="a2b2", db="raspi_db")
                        update_message("충격이 감지되었습니다. \n 속도제어가 시작됩니다.", "white")
                        time.sleep(2)
                        update_message("속도제어를 해제하기 위해서는 지문을 인식하세요.", "white")
                        time.sleep(2)

                        while True:
                            try:
                                f = PyFingerprint('/dev/ttyAMA0', 57600, 0xFFFFFFFF, 0x00000000) # 지문 인식 데이터를 f에 저장.

                            except Exception as e:
                                print('지문 센서 초기화에 실패했습니다!')
                                print('예외 메시지: ' + str(e))
                                update_message("지문을 다시 입력해주세요", "red")  # 지문 인식 실패 메시지 표시
                                continue  # 다시 while 루프의 처음으로 돌아가서 다시 시도

                            try:
                                update_message("지문 인식 중입니다.\n 잠시만 기다려주세요.", "blue")  # 지문 인식 중 메시지 표시
                                if wait_for_finger(f):
                                    f.convertImage(0x01)
                                    characteristics = str(f.downloadCharacteristics(0x01)).encode('utf-8')

                                    # GPS 데이터 읽기
                                    while True:
                                        line = ser_gps.readline().decode('utf-8').strip()
                                        if line.startswith('$GPGGA'):
                                            gps_data = pynmea2.parse(line)
                                            latitude = gps_data.latitude
                                            longitude = gps_data.longitude
                                            break

                                    # MariaDB에 데이터 저장.
                                    cur = conn.cursor()
                                    sql = "INSERT INTO finger_template VALUES (%s, %s, %s, %s)"
                                    cur.execute(sql, (
                                    time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()), characteristics, latitude,
                                    longitude))
                                    conn.commit()

                                    # 지문 인식 완료 시 동작
                                    print('지문 데이터 저장 완료!')
                                    conn.close()
                                    update_message("지문 인식이 완료되었습니다!\n속도 제어가 해제됩니다.", "green")  # 지문 인식 완료 메시지 표시
                                    print('완료!')

                                    time.sleep(5)
                                    update_message("주행 중...", "white") # Tkinter 창 메세지를 업데이트
                                    ser.write(b'S')  # 지문 인식 결과를 아두이노 메가로 전송
                                    break

                            except Exception as e:
                                print('지문 인식 실패!')
                                print('지문 인식 오류: ' + str(e))
                                update_message("지문 인식에 실패했습니다.\n 지문을 다시 입력해주세요", "red")
                                time.sleep(1)
                                continue

                except ValueError:
                    # 라인을 정수로 변환할 수 없는 경우 무시
                    pass

            # GUI 업데이트 및 이벤트 처리
            tk.update()
            tk.update_idletasks()

    except KeyboardInterrupt:
        print("프로그램 종료.")
        tk.destroy()

    tk.mainloop()
