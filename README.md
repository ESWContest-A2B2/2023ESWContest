# Team A2B2

## Team Members

| Profile | Mail | Role |
| ------- | ---- | ---- |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/dd8736d0-a3ea-4dae-8b10-202b5c2a2855" width="70px;" alt=""/><br/><sub><b>지민영</b><sub></a></div> | adamminyoung@konkuk.ac.kr | 기획 및 총괄<br/>S/W개발 - 충격 감지 후 RasberryPi 동작 개발<br/>H/W개발 - 충격 감지용 Arduino Mega 개발 |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/da63ace4-d7a5-4b2c-a0b3-79af0bdbb1c0" width="70px;" alt=""/><br/><sub><b>윤지민</b><sub></a></div> | ske0910@konkuk.ac.kr | S/W개발 - 속도 제어 알고리즘 아이디어 및 구현<br/>H/W개발 - RC카 제어용 Arduino Uno 개발 |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/dd8736d0-a3ea-4dae-8b10-202b5c2a2855" width="70px;" alt=""/><br/><sub><b>이소은</b></sub></a></div> | sy3048@konkuk.ac.kr | S/W개발 - RasberryPi 동작 개발<br/>H/W개발 - RC카 제어용 Arduino Uno 개발<br/>Web개발 - Flask 이용 지문인식 데이터 Web에 업로드 |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/dd8736d0-a3ea-4dae-8b10-202b5c2a2855" width="70px;" alt=""/><br/><sub><b>차서연</b></sub></a></div> | chasy0826@konkuk.ac.kr | H/W개발 – RC카 제어용 Arduino Uno 개발 |

## GitHub Tree

📦2023ESWContest_free_1017 <br/>
 ┣ 📂ArduinoMega <br/>
 ┃ ┗ 📜test.ino <br/>
 ┣ 📂ArduinoUno <br/>
 ┃ ┗ 📜test.ino <br/>
 ┣ 📂RasberryPi <br/>
 ┃ ┗ 📜raspi01.py <br/>
 ┣ 📂Web <br/>
 ┃ ┗ 📜test.ino <br/>
 ┣ 📂imgs <br/>
 ┃ ┣ 🖼️func_spec.png <br/>
 ┃ ┗ 🖼️system_config.png <br/>
 ┣ 🖼️A2B2.png <br/> 
 ┗ 📜README.md

## System Configuration
![](./imgs/system_config.png)

## Functional Specification
![](./imgs/func_spec.png)

## Differentiation of Development

### Safety-Conscious System
In the case of the existing hit-and-run prevention system, the car stopped immediately when an impact was detected. However, through continuous meetings, our team thought that sudden stops on the road could interfere with traffic flow and cause accidents. To solve this problem, we designed a brand-new system to gradually lower the maximum speed of the car and stop if fingerprint recognition is not performed for a certain period of time.

### Revolutional Way of Extracting Driver's Information
The hit-and-run prevention system developed so far has used methods such as dropping license plates on the roadway or dropping the car's RFID chip when shock is detected. However, leaving objects on the roadway can affect the safety of other drivers, and there is a risk of being lost depending on weather conditions. Accordingly, our system allows the driver's information, collision time, and collision place to be extracted through fingerprint recognition.

## Todos

- Add comparing process with MariaDB's fingerprints of suspect
- RasberryPi/raspi01.py code optimization
