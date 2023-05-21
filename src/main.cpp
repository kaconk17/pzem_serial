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
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();
  StaticJsonDocument<200> doc;
    doc["voltage"] = voltage;
    doc["current"] = current;
    doc["power"] = power;
    doc["energy"] = energy;
    doc["freq"] = frequency;
    doc["pf"] = pf;
    serializeJson(doc,Serial);
    Serial.println();
}

void resetKwh(){
  StaticJsonDocument<200> doc;
  bool stat = pzem.resetEnergy();
    doc["status"] = stat;

    serializeJson(doc,Serial);
    Serial.println();
}