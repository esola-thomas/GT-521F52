#include <ArduinoBLE.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEByteCharacteristic G_LED_Characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic R_LED_Characteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN;
#include <ArduinoBLE.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEByteCharacteristic G_LED_Characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic R_LED_Characteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN;

void setup() {
  pinMode(ledPin, OUTPUT);
  BLE.begin();
  BLE.setLocalName("LED Controller");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(G_LED_Characteristic);
  ledService.addCharacteristic(R_LED_Characteristic);
  BLE.addService(ledService);
  G_LED_Characteristic.writeValue(0);
  BLE.advertise();
  pinMode(ledPin, OUTPUT);
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
          digitalWrite(ledPin, LOW);
        } else {
          digitalWrite(ledPin, HIGH);
        }
      }
      if (R_LED_Characteristic.written()) {
        if (R_LED_Characteristic.value()) {
          digitalWrite(ledPin, LOW);
        } else {
          digitalWrite(ledPin, HIGH);
        }
      }
    }
  }
}