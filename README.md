# MENTSensor
## Senior Design Project - Trinia Medrano, Akshansh Gupta, and Eric Gidzinski

### Known Issues
- When the sensors were wired up to fit inside the case, the TMRPcm audio stopped working when if ESP8266-01 WiFi module initiateESP8266 function is ran.

### Prework
WiFi Modules must be flashed to a baud rate of 9600 before installing MENTSensor since SoftwareSerial does not like rates beyond 9600. Script to input AT commands via Arduino Uno is provided in the "ESP8266ATCommandInput" folder. Use the AT command '''code "AT+UART_DEF=9600,8,1,0,0" '''

### How to Run
- Connect sensors to an Arduino Uno according to the list at the top of the TagSensorV1 file. As of writing (4/18/2020), this list is:
PINOUT:
  ESP8266
    TX: A1
    RX: A0
    Power: 3.3V
    CH_EN: 3.3V
    GND: GND

  Speaker
    Red: 9
    GND: GND

  SD Card
    CS:   4
    SCK:  13
    MOSI: 11
    MISO: 12
    VCC:  5V
    GND:  GND

  PIR Sensor
    Out: 6
    VCC: 5V
    GND: GND

- Connect Arduino Uno to computer via USB.
- In Arduino IDE, run the TagSensorV1 file. 
