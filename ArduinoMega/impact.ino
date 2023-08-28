const int vib1=2; // 좌측 진동 센서 
const int vib2=3; // 중앙 진동 센서
const int vib3=4; // 우측 진동 센서
int lastState1 = LOW;
int lastState2 = LOW;
int lastState3 = LOW;
int count1 = 0;
int count2 = 0;
int count3 = 0;
unsigned long previousMillis = 0;
const long interval = 1000; // 1초

int i = 0;
int State;
 
void setup()
{
  Serial.begin(115200); //시리얼통신 설정 1152000
  Serial3.begin(9600); // 메가와 우노 사이의 시리얼 통신을 위한 소프트웨어 시리얼 객체
  pinMode(vib1, INPUT_PULLUP); //센서핀 입력
  pinMode(vib2, INPUT_PULLUP); //센서핀 입력
  pinMode(vib3, INPUT_PULLUP); //센서핀 입력
}

void loop()
{
  int currentState1 = digitalRead(vib1);
  int currentState2 = digitalRead(vib2);
  int currentState3 = digitalRead(vib3);

  unsigned long currentMillis = millis();

//digital 상태가 변할 때 마다 카운트
  if (currentState2 == LOW && lastState2 == HIGH) { 
    count2++;
  }

  if (currentState3 == LOW && lastState3 == HIGH) {
    count3++;
  }

  if (currentState1 == LOW && lastState1 == HIGH) {
    count1++;
  }
// 1초동안 센서의 변화 값이 일정 값보다 크면 G 전송
  if (currentMillis >= previousMillis + interval) {
    previousMillis = currentMillis;

  if (count2 >= 20 && count1 >= 10 && count3 >= 10) {
    if(i==0)
    {
      Serial3.write('G');// 우노에 충격 신호 전송
      i++;
      Serial.write('G');// 라즈베리파이에 충격 신호 전송
      Serial.end();
      delay(10);
    }
  }

//카운트 초기화
  count1 = 0;
  count2 = 0;
  count3 = 0;
  
// 이전 상태 초기화
lastState1 = currentState1;
lastState2 = currentState2;
lastState3 = currentState3;

  }
  
  Serial.begin(115200);
  
  if (Serial.available())// 메가에서 라즈베리파이로부터 지문 인식 결과 수신
  {
    
    char receivedChar = Serial.read();
    if (receivedChar == 'S') 
    {
      i = 0;//값 초기화(다시 주행 중 충격인식할 수 있도록 설정)
      // 지문 인식 O
      Serial3.write('S'); // 지문 인식 신호 우노로 전송
    }
  }
  
}
