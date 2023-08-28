#include <LiquidCrystal_I2C.h> //lcd 모니터 사용을 위한 라이브러리 선언
#include <Wire.h>
#include <Scheduler.h> //스케줄러, 세마포어를 사용을 위한 라이브러리 선언
#include <Scheduler/Semaphore.h>
#include <Servo.h> //서보모터 사용을 위한 라이브러리 선언
#include <SoftwareSerial.h> //블루투스 모듈 사용을 위해 라이브러리 선언

// I2C LCD 초기화
LiquidCrystal_I2C lcd(0x27, 16, 2); //주소, 열 수, 행 수

// 변수 및 객체 선언
String ms = "";
int a = 2;
int pa = 90;
int sp = 100;
int slow = 250;
int num = 2;
int ta;
char inChar = 'S';
int i = 0;
int pnum = 0;

Semaphore mutex; //세마포어 선언
Servo myServo;  //servo 모터 객체
SoftwareSerial mySerial(8, 9); //블루투스 통신을 위한 핀

void setup()
{
  lcd.begin(); //LCD 초기화
  lcd.backlight(); //LCD 배경화면 활성화
  Serial.begin(9600); // 시리얼 통신 초기화
  mySerial.begin(9600); // 블루투스 시리얼 통신 초기화
  myServo.attach(3); //서보모터 핀 3번에 연결
  Scheduler.startLoop(loop1); //두 번째 루프 시작
  pinMode(6, OUTPUT); //핀 6번 출력
  pinMode(11, OUTPUT); //핀 11번 출력
}

unsigned long previousMillis = 0; // 이전 시간 저장 변수
const unsigned long delayInterval = 1000; // 1000ms마다 반복

void loop()
{
  unsigned long currentMillis = millis();

    if (Serial.available())
    {
      inChar = Serial.read(); //시리얼 입력 확인
    }
    if (inChar == 'G') //'G'가 입력됐을 때
    {
      mutex.wait(); //세마포어 획득
      {
        if (currentMillis - previousMillis >= delayInterval){ //1초에 한 번 씩
        previousMillis = currentMillis; // 시간 업데이트
        if (i < 60) // 60번 반복
        {
            slow = slow - 2; // 2씩 감소
        } // slow 130
        else if (i >= 60 && i < 180) //120번 반복
        {
          // Do nothing
        }
        else if (i >= 180 && i < 190) //10번 반복
        {
            slow = slow - 13; //13씩 감소
        } // slow 0
        sp = min(sp, slow); //스레드가 실행될 때마다 sp값을 sp와 slow 중 작은 값으로 변경
        i += 1; //i 값을 증가시켜 if문의 범위 변경
      }
      }
    
      mutex.signal(); // 세마포어를 해제
    }
    
    else if (inChar == 'S') //'S'가 입력됐을 때
    {
      mutex.wait(); //세마포어 획득
      slow = 250; //최고 속도를 250으로 초기화
      i = 0; //i값을 0으로 초기화
      mutex.signal(); //세마포어 해제
    } 
}

void loop1()
{
    mutex.wait();// 세마포어를 획득 loop1 실행
    {
      if (mySerial.available()) {
      String ms = mySerial.readStringUntil('c');
      int a = ms.toInt(); //문자열을 정수로 변환

      if (a == 4) {
        sp = max(min(sp, slow) - 10, 0); //sp값 현재속도와 최고속도 중 작은 값에서 10 감소
      } else if (a == 5) {
        sp = min(sp + 10, slow); //sp값 10 증가
        }

      if (a < 4) {
        num = a;
      }
      if(a==6){
        pa = pa + 10; // 서보모터 왼쪽으로 10도
        pa = min(pa, 130);
        myServo.write(pa);
      }
      if(a==7){
        pa = pa - 10; // 서보모터 오른쪽으로 10도
        pa = max(pa,50);
        myServo.write(pa);
      }
      }
      if (num == 1) { // 전진
        analogWrite(6, sp);
        analogWrite(11, 0);
        pnum = 1;
      } else if (num == 2) { //정지
        if (pnum == 1) { //이전에 전진일 때는 짧은 시간 후진 후 정지
          analogWrite(6, 0);
          analogWrite(11, sp);
          delay(10);
        } else if (pnum == 3) { //이전에 후진일 때 짧은 시간 전진 후 정지
          analogWrite(6, sp);
          analogWrite(11, 0);
          delay(10);
        }
        analogWrite(6, 0); //정지
        analogWrite(11, 0);
        pnum = 0;
        sp = 0; //sp값 0으로 초기화
      } else if (num == 3) { //후진
        analogWrite(6, 0);
        analogWrite(11, sp);
        pnum = 3;
      }
      lcd.setCursor(0,0); //LCD 화면 첫 번째 줄 출력
      lcd.print("max :");
      lcd.print(slow);
      lcd.print("   ");
      lcd.setCursor(0,1); //LCD 화면 두 번째 줄 출력
      lcd.print("speed :");
      lcd.print(sp);
      lcd.print("   ");
  }
    mutex.signal();// 세마포어 해제 loop 실행
}