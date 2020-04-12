/* *********************************************************************

MENT Tag Sensor 

Team #11 - Trinia Medrano, Akshansh Gupta, Eric Gidzinski

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
    
************************************************************************/

#include <SoftwareSerial.h>
#include <ESP8266_Simple.h>
#include <SD.h>
#include <TMRpcm.h> // WAV Player library
#include <SPI.h>

#define SD_ChipSelectPin 4   // Defines CS pin
#define PIR 6                // Define motion sensor pin
#define SPEAKER 9  // To Do: Remove once testing is done
#define BEATTIME 200 // To Do: Remove once testing is done
TMRpcm speaker;              // Create object for speaker library
ESP8266_Simple ESP8266(A1,A0); // TX, RX

char espBuffer[300];
byte responseCode;
int motion = 0;     // Variable for reading status of motion sensor
int pirState = LOW; // Start by assuming no motion detected

void initiateESP8266()
{
  // Start communication with ESP8266
  ESP8266.begin(9600);
  Serial.println("Test communication w/ ESP8266\n");
  delay(1000);
  if((responseCode = ESP8266.sendCommand(F("AT"), espBuffer, sizeof(espBuffer))) == ESP8266_OK)
  {
    // The command worked, prnt the result
    Serial.println("OK");
    Serial.println(espBuffer);
  }
  else
  {
    // An error occurred, would you like to see what
    ESP8266.debugPrintError(responseCode, &Serial);
    
    // Or you can get it as a string if you prefer
    char bufferWithMinLength50Char[50];
    ESP8266.getErrorMessage(responseCode, bufferWithMinLength50Char);    
  }
  delay(1000);
  
  Serial.println("Resetting ESP8266\n");
  if((responseCode = ESP8266.sendCommand(F("AT+RST"), espBuffer, sizeof(espBuffer))) == ESP8266_OK)
  {
    // The command worked, prnt the result
    Serial.println("OK");
    Serial.println(espBuffer);
  }
  else
  {
    // An error occurred, would you like to see what
    ESP8266.debugPrintError(responseCode, &Serial);
    
    // Or you can get it as a string if you prefer
    char bufferWithMinLength50Char[50];
    ESP8266.getErrorMessage(responseCode, bufferWithMinLength50Char);    
  }
  delay(1000);

  Serial.println("Setting Baud to 9600 (easier for software serial)\n");
  if((responseCode = ESP8266.sendCommand(F("AT+UART_DEF=9600,8,1,0,0"), espBuffer, sizeof(espBuffer))) == ESP8266_OK)
  {
    // The command worked, prnt the result
    Serial.println("OK");
    Serial.println(espBuffer);
  }
  else
  {
    // An error occurred, would you like to see what
    ESP8266.debugPrintError(responseCode, &Serial);
    
    // Or you can get it as a string if you prefer
    char bufferWithMinLength50Char[50];
    ESP8266.getErrorMessage(responseCode, bufferWithMinLength50Char);    
  }
  delay(1000);
  
  Serial.println("Changing to Station and Access Point \n");
  if((responseCode = ESP8266.sendCommand(F("AT+CWMODE=?"), espBuffer, sizeof(espBuffer))) == ESP8266_OK)
  {
    // The command worked, prnt the result
    Serial.println("OK");
    Serial.println(espBuffer);
  }
  else
  {
    // An error occurred, would you like to see what
    ESP8266.debugPrintError(responseCode, &Serial);
    
    // Or you can get it as a string if you prefer
    char bufferWithMinLength50Char[50];
    ESP8266.getErrorMessage(responseCode, bufferWithMinLength50Char);    
  }
  delay(1000);
  
  Serial.println("Creating MENT Sensor Access Point\n");
  if((responseCode = ESP8266.sendCommand("AT+CWSAP=\"MENTXYZ Sensor\",\"\",1,0,4,0", espBuffer, sizeof(espBuffer)),1) == ESP8266_OK)
  {
    // The command worked, prnt the result
    Serial.println("OK");
    Serial.println(espBuffer);
  }
  else
  {
    Serial.println("Error");
    // An error occurred, would you like to see what
    ESP8266.debugPrintError(responseCode, &Serial);
    
    // Or you can get it as a string if you prefer
    char bufferWithMinLength50Char[50];
    ESP8266.getErrorMessage(responseCode, bufferWithMinLength50Char);    
  }
  delay(1000);
}

// Used to play message through speaker
void playMessage() 
{
  // To Do: Figure out naming system of saved messages
  speaker.play("1.wav");
  return;
}

// Used to search for motion. When motion is found, function calls playMessage to play message
void detectMotion() 
{
  motion = digitalRead(PIR); // Read motion sensor input
  if (motion == HIGH) 
  {
    delay(100);
    if(pirState == LOW)
    {
      // We have just turned on
      Serial.println("Motion detected!");
      // Play message
      playMessage();
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } 
  else
  {
    delay(200);
    if(pirState == HIGH)
    {
      // We have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

// TO DO: Function that pulls audio file from app 
// Pulls audio via GET requests
// TO DO: Add name of sensor as an input to the function. Used to pull correct file from app.
void pullAudio()
{
  
}

// TO DO: Function that runs when first pairing the sensor to the app
// TO DO: Add a way (maybe a button) to reset the sensor and to enter reset mode
void pairSensor()
{
  
}

void setup()
{
  Serial.begin(9600); // TO DO: Delete once remote WiFi setup works

  // Start the SD card
  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
    Serial.println("SD fail");
    return;                               //don't do anything more if not
  }
  
  // Initiate speaker
  speaker.speakerPin = SPEAKER;
  speaker.setVolume(6); // 0 - 6. Set volume level

  // Initiate ESP8266
//  initiateESP8266(); TO DO: Figure out why ESP8266 cannot run the same time as TMRpcm speaker. Maybe SPI issue?

  // Initiate PIR sensor
  pinMode(PIR, INPUT);
  
  Serial.println("Initiation complete");

  // Pull latest 
  pullAudio();
}

void loop()
{
  detectMotion();
}
