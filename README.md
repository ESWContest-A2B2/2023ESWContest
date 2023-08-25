# Team A2B2

## Team Members

| Profile | Mail | Role |
| ------- | ---- | ---- |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/dd8736d0-a3ea-4dae-8b10-202b5c2a2855" width="70px;" alt=""/><br/><sub><b>지민영</b><sub></a></div> | <div align="center">adamminyoung@konkuk.ac.kr | Planning and General Management<br/>S/W Development - Development of RasberryPi Behavior after Shock Detection<br/>H/W Development - Development of Arduino Mega for Shock Detection |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/da63ace4-d7a5-4b2c-a0b3-79af0bdbb1c0" width="70px;" alt=""/><br/><sub><b>윤지민</b><sub></a></div> | <div align="center">ske0910@konkuk.ac.kr | S/W Development - Speed Control Idea Devising and Implementation<br/>H/W Development - Development of Arduino Uno for RC Car Control |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/dd8736d0-a3ea-4dae-8b10-202b5c2a2855" width="70px;" alt=""/><br/><sub><b>이소은</b></sub></a></div> | <div align="center">sy3048@konkuk.ac.kr | S/W Development - Development of RasberryPi Behavior after Shock Detection<br/>H/W Development - Development of Arduino Uno for RC Car Control<br/>Web Development - Uploading Fingerprint Recognition Data to Web using Flask |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/dd8736d0-a3ea-4dae-8b10-202b5c2a2855" width="70px;" alt=""/><br/><sub><b>차서연</b></sub></a></div> | <div align="center">chasy0826@konkuk.ac.kr | H/W Development - Development of Arduino Uno for RC Car Control |

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
