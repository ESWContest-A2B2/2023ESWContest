import pymysql
from geopy.geocoders import Nominatim

def geocoding_reverse(lat_lng_str): 
    geolocoder = Nominatim(user_agent = 'South Korea', timeout=None)
    address = geolocoder.reverse(lat_lng_str) 

    return address
#위,경도값을 주소값으로 반환하는 함수



class Finger:
    def getFinger(self):
        ret = []
        db = pymysql.connect(host = "172.20.10.2", user="a2b2", password="a2b2", charset="utf8") #finger_template가 저장된 데이터베이스 접속
        curs = db.cursor() #sql문에 사용할 커서를 만든다.

        sql = "SELECT * FROM raspi_db.finger_template" #finger_template에서 가져온 값을 sql에 저장한다.

        curs.execute(sql) #sql을 실행한다.

        rows = curs.fetchall() #모든 줄을 가져온다.
        i=1
        for e in rows: #반복문을 통해 한 줄씩 리스트에 저장한다.
            temp = {'no' : str(i), 'collect_time' : e[0], 'finger_char': e[1], 'latitude': e[2], 'longitude': e[3], 'address': geocoding_reverse(e[2]+','+e[3])}
            i=i+1
            ret.append(temp) #리스트에 저장한 데이터를 배열에 저장한다.

        db.commit()
        db.close()
        return ret #데이터베이스의 데이터를 옮긴 배열을 반환한다.

    
    
