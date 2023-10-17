/*
	Created by Ernesto Sola-Thomas, October 16th 2023
	Licensed for non-commercial use, must include this license message
  Fell free to modify the code in any way, just give me credit for my work :)
	TLDR; Wil Wheaton's Law
*/

#include <ArduinoBLE.h>
#include <GT_521F52.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEByteCharacteristic G_LED_Characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic R_LED_Characteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// Initialize fingerprint sensor UART interface using pins D14 - tx / D13 - rx
//GT521F52 fps(Serial1);

void setup() {
  // Ini
  Serial.begin(115200);
  
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  BLE.begin();
  BLE.setLocalName("LED Controller");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(G_LED_Characteristic);
  ledService.addCharacteristic(R_LED_Characteristic);
  BLE.addService(ledService);
  G_LED_Characteristic.writeValue(0);
  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    while (central.connected()) {
      if (G_LED_Characteristic.written()) {
        if (G_LED_Characteristic.value()) {
          digitalWrite(LEDG, LOW);
          //fps.SetLED(true);
        } else {
          digitalWrite(LEDG, HIGH);
          //fps.SetLED(false);
        }
      }
      if (R_LED_Characteristic.written()) {
        if (R_LED_Characteristic.value()) {
          digitalWrite(LEDB, LOW);
        } else {
          digitalWrite(LEDB, HIGH);
        }
      }
    }
  }
}