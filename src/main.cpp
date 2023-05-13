#include <Arduino.h>
#include <ArduinoJson.h>
#include <PZEM004Tv30.h>


#if defined(ESP32)
    #error "Software Serial is not supported on the ESP32"
#endif

/* Use software serial for the PZEM
 * Pin 12 Rx (Connects to the Tx pin on the PZEM)
 * Pin 13 Tx (Connects to the Rx pin on the PZEM)
*/
#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 12
#define PZEM_TX_PIN 13
#endif

SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);

// put function declarations here:
void getVal();
void resetKwh();

void setup() {
  Serial.begin(19200);
  
}

void loop() {
  if (Serial.available() > 0)
    {
        int commNo = Serial.read()- '0';

        switch (commNo)
        {
        case 1:
            getVal();
            break;
        case 0:
            resetKwh();
            break;
        
        default:
            break;
        }
    }
}

// put function definitions here:

void getVal(){
  StaticJsonDocument<200> doc;
    doc["voltage"] = 220;
    doc["current"] = 0.3;
    doc["power"] = 10;
    doc["energy"] = 11;
    doc["freq"] = 50;
    doc["pf"] = 0.2;
    serializeJson(doc,Serial);
    Serial.println();
}

void resetKwh(){
  StaticJsonDocument<200> doc;
    doc["status"] = false;

    serializeJson(doc,Serial);
    Serial.println();
}