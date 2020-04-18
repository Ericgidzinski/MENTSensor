# MENTSensor
## Senior Design Project - Trinia Medrano, Akshansh Gupta, and Eric Gidzinski

### Known Issues
- When the sensors were wired up to fit inside the case, the TMRPcm audio stopped working when if ESP8266-01 WiFi module initiateESP8266 function is ran.

### Prework
WiFi Modules must be flashed to a baud rate of 9600 before installing MENTSensor since SoftwareSerial does not like rates beyond 9600. Script to input AT commands via Arduino Uno is provided in the "ESP8266ATCommandInput" folder. Use the AT command '''code "AT+UART_DEF=9600,8,1,0,0" '''

### How to Run
- Connect sensors to an Arduino Uno according to the list at the top of the TagSensorV1 file. 
- Connect Arduino Uno to computer via USB.
- In Arduino IDE, run the TagSensorV1 file. 
