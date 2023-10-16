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


// #include <Arduino.h>
// #include <ArduinoBLE.h>
// #include <GT_521F52.h>

// // Declare BLE Globals
//   BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
//   BLEByteCharacteristic G_LED_Characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
//   BLEByteCharacteristic G_LED_Characteristic2("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(LEDR, OUTPUT);
//   pinMode(LEDG, OUTPUT);
//   pinMode(LEDB, OUTPUT);
//   digitalWrite(LEDR, LOW);
//   // Initialize Serial to pc
//   Serial.begin(9600);
//   while (!Serial);
//   Serial.println("Serial initialized");

//   BLE.begin();
//   BLE.setLocalName("FPS");
//   BLE.setAdvertisedService(ledService);
//   ledService.addCharacteristic(G_LED_Characteristic);
//   ledService.addCharacteristic(G_LED_Characteristic2);
//   BLE.addService(ledService);
//   G_LED_Characteristic.writeValue(0);
//   G_LED_Characteristic2.writeValue(0);
//   BLE.advertise();
// }

// void loop() {
//   BLEDevice central = BLE.central();

//   if (central) { // If a central is connected to peripheral
//     Serial.print("Connected to central: ");
//     Serial.println(central.address());
//     while (central.connected()) {
//       if (G_LED_Characteristic.written()) {
//         if (G_LED_Characteristic.value()) {
//           Serial.println("Received 1");
//           digitalWrite(LEDG, LOW);
//         } else {
//           Serial.println("Received 0");
//           digitalWrite(LEDG, HIGH);
//         }
//       }
//       if (G_LED_Characteristic2.written()) {
//         if (G_LED_Characteristic2.value()) {
//           Serial.println("Received 1");
//           digitalWrite(LEDG, LOW);
//         } else {
//           Serial.println("Received 0");
//           digitalWrite(LEDG, HIGH);
//         }
//       }
//     }
//   }
// }