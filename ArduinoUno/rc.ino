#include <LiquidCrystal_I2C.h> //lcd 모니터 사용을 위한 라이브러리 선언
#include <Wire.h>
#include <Scheduler.h> //스케줄러, 세마포어를 사용을 위한 라이브러리 선언
#include <Scheduler/Semaphore.h>
#include <Servo.h> //서보모터 사용을 위한 라이브러리 선언
#include <SoftwareSerial.h> //블루투스 모듈 사용을 위해 라이브러리 선언

LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd 객체 선언

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
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  mySerial.begin(9600);
  myServo.attach(3); //서보모터 핀 3번에 연결
  Scheduler.startLoop(loop1); //두 번째 루프 시작
  pinMode(6, OUTPUT); //핀 6번 출력
  pinMode(11, OUTPUT); //핀 11번 출력
}

void loop()
{
  if (Serial.available()) 
  {
    inChar = Serial.read(); //시리얼 입력을 통해 문자를 받음
  }
  if (inChar == 'G') // 시리얼 통신을 통해 G를 받음
  {
    mutex.wait(); //세마포어 획득
    {
      if(i<600) // i가 0부터 600까지
      {
        if(i%10==0) // 60번 감소
        {
          slow=slow-3; // 최고 속도 1초에 3씩 감소
        }
        delay(100);
        } //sp = 70
      
      if(600<=i and i<1800) //i가 600부터 1799까지
      {
        delay(100);
        } //2분동안 최고 속도 70
      
      if(1800<=i and i<1900) //i가 1800부터 1899까지
      {
        if(i%10==0) // 10번 감소
        {
          slow=slow-7; //최고 속도 1초에 7씩 감소
        }
        delay(100);
        } //sp = 0  

      sp=min(sp, slow); //스레드가 실행될 때마다 sp값을 sp와 slow중 작은 값으로 변경
      }
      mutex.signal();// 세마포어를 해제
      i += 1; //i의 값을 증가시켜 if문 범위 변경
    }
      
    if (inChar == 'S') //시리얼 통신을 통해 S를 받음
      {
        mutex.wait(); //세마포어 획득
        slow = 250; //최고 속도를 250으로 초기화
        i=0; //i값을 0으로 초기화
        mutex.signal(); //세마포어 해제
      }
}

void loop1()
{
    mutex.wait();// 세마포어를 획득 loop1 실행
    {
      if (mySerial.available()) {
      String ms = mySerial.readStringUntil('c');
      int a = ms.toInt();

      if (a == 4) {
        sp = max(min(sp, slow) - 10, 0); //a가 4일때 sp값을 현재속도와 최고속도 중 작은 값에서 10 감소
      } else if (a == 5) {
        sp = min(sp + 10, slow); //a가 5일때 sp값을 10 증가
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
        sp = 0;
      } else if (num == 3) { //후진
        analogWrite(6, 0);
        analogWrite(11, sp);
        pnum = 3;
      }
      lcd.setCursor(0,0); //첫번째 줄 출력
      lcd.print("max :");
      lcd.print(slow);
      lcd.print("   ");
      lcd.setCursor(0,1); //두번째 줄 출력
      lcd.print("speed :");
      lcd.print(sp);
      lcd.print("   ");
  }
    mutex.signal();// 세마포어 해제 loop 실행
}
