# Team A2B2

## BoongBoong-E
<img src="https://github.com/ESWContest-A2B2/2023ESWContest_free_1017/assets/141810581/61a8f374-50a8-4c9d-9653-3fa86bc17cac" alt=""/>

## System Functionality
Our system has been designed to prevent driver escapes in the event of a hit-and-run accident. If an impact occurs while the vehicle is in motion, our system gradually reduces the car's max speed for a duration of 1 minute. After max speed has been reduced, the car can continue operating, not exceeding the reduced top speed for 2 minutes. By this algorithm we can ensure that the flow of surrounding traffic is not disrupted and the potential for accidents is minimized. However, if the driver does not undergo fingerprint recognition even after total 3 minutes, the car is programmed to come to a complete stop. Through this system, we anticipate a society where hit-and-run accidents are eradicated.

## System Configuration
![](./imgs/system_config.png)

## Functional Specification
![](./imgs/func_spec.png)

## Hardware Diagram
![](./imgs/hardware_diagram.png)

## Competitive Differentiation of Development

### Safety-Conscious System
In the case of the existing hit-and-run prevention system, the car stopped immediately when an impact was detected. However, through continuous meetings, our team thought that sudden stops on the road could interfere with traffic flow and cause accidents. To solve this problem, we designed a brand-new system to gradually lower the maximum speed of the car and stop if fingerprint recognition is not performed for a certain period of time.

### Innovatary Method Extracting Driver's Information
The hit-and-run prevention system developed so far has used methods such as dropping license plates on the roadway or dropping the car's RFID chip when shock is detected. However, leaving objects on the roadway can affect the safety of other drivers, and there is a risk of being lost depending on weather conditions. Accordingly, our system allows the driver's information, collision time, and collision place to be extracted through fingerprint recognition.

## GitHub Tree

📦2023ESWContest_free_1017 <br/>
 ┣ 📂ArduinoMega <br/>
 ┃ ┗ 📜test.ino <br/>
 ┣ 📂ArduinoUno <br/>
 ┃ ┗ 📜rc.ino <br/>
 ┣ 📂RasberryPi <br/>
 ┃ ┗ 📜raspi01.py <br/>
 ┣ 📂Web <br/>
 ┃ ┗ 📜test.ino <br/>
 ┣ 📂imgs <br/>
 ┃ ┣ 🖼️func_spec.png <br/>
 ┃ ┣ 🖼️hardware_diagram.png <br/>
 ┃ ┗ 🖼️system_config.png <br/>
 ┣ 🖼️A2B2.png <br/> 
 ┗ 📜README.md

## Team Introduction
We are a team of four students majoring in Electrical and Electronic Engineering at Konkuk University, Seoul, South Korea. We are interested in the collaborative relationship between embedded software and the industry.

## Team Members

| Profile | Position | Contact | Role |
| ------- | -------- |---- | ---- |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/dd8736d0-a3ea-4dae-8b10-202b5c2a2855" width="90px;" alt=""/><br/><sub><b>Minyoung Ji</b><sub></a></div> | <div align="center">Team<br/>Leader | <div align="center">adamminyoung@konkuk.ac.kr | Planning and General Management<br/>S/W Development - Development of RasberryPi Behavior after Shock Detection<br/>H/W Development - Development of Arduino Mega for Shock Detection |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest/assets/141810581/da63ace4-d7a5-4b2c-a0b3-79af0bdbb1c0" width="90px;" alt=""/><br/><sub><b>Jimin Yoon</b><sub></a></div> | <div align="center">Team Member | <div align="center">ske0910@konkuk.ac.kr | S/W Development - Speed Control Idea Devising and Implementation<br/>H/W Development - Development of Arduino Uno for RC Car Control |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest_free_1017/assets/141810581/821dc47d-ea6c-4ca1-b678-c4c636d1b20f" width="90px;" alt=""/><br/><sub><b>Soeun Lee</b></sub></a></div> | <div align="center">Team Member | <div align="center">sy3048@konkuk.ac.kr | S/W Development - Development of RasberryPi Behavior after Shock Detection<br/>H/W Development - Development of Arduino Uno for RC Car Control<br/>Web Development - Uploading Fingerprint Recognition Data to Web using Flask |
| <div align="center"><img src="https://github.com/ESWContest-A2B2/2023ESWContest_free_1017/assets/141810581/39478535-1cb5-4837-98e3-0ddffaee9691" width="90px;" alt=""/><br/><sub><b>Seoyeon Cha</b></sub></a></div> | <div align="center">Team Member | <div align="center">chasy0826@konkuk.ac.kr | H/W Development - Development of Arduino Uno for RC Car Control |

## Todos

- Add comparing process with MariaDB's fingerprints of suspect
- Optimize RasberryPi/raspi01.py
