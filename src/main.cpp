#include <Arduino.h>
// Define command numbers
#define OPEN_CMD 1
#define LED_ON_CMD 2
#define LED_OFF_CMD 3
#define CLOSE_CMD 4

// Define OPEN and LED ON commands as byte arrays
byte OPEN[]   = {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01};
byte LED_ON[] = {0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x13, 0x01};
byte LED_OFF[]= {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x12, 0x01};
byte CLOSE[]  = {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x01};

void executeCommand(byte cmd[], int cmdLength);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial.println("GT-521F52 Controller Ready. Input command number:");
}

void loop() {
  if (Serial.available()) {
    int command = Serial.parseInt();
    
    switch (command) {
      case OPEN_CMD:
        executeCommand(OPEN, sizeof(OPEN));
        break;
      case LED_ON_CMD:
        executeCommand(LED_ON, sizeof(LED_ON));
        break;
      case LED_OFF_CMD:
        executeCommand(LED_OFF, sizeof(LED_OFF));
        break;
      case CLOSE_CMD:
        executeCommand(CLOSE, sizeof(CLOSE));
        break;
      default:
        Serial.println("Invalid Command");
        break;
    }
  }
}

void executeCommand(byte cmd[], int cmdLength) {
  Serial.print("Sending Command: ");
  for (int i = 0; i < cmdLength; i++) {
    Serial1.write(cmd[i]);
    Serial.print(cmd[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  while (!Serial1.available()) {
    // Waiting for a response
  }
  
  String response = "";
  while (Serial1.available()) {
    response += String(Serial1.read(), HEX);
    response += " ";
  }
  Serial.print("Response from GT-521F52: ");
  Serial.println(response);
}


// /*
// 	Created by Ernesto Sola-Thomas, October 16th 2023
// 	Licensed for non-commercial use, must include this license message
//   Fell free to modify the code in any way, just give me credit for my work :)
// 	TLDR; Wil Wheaton's Law
// */

// #include <ArduinoBLE.h>
// #include <GT_521F52.h>

// BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");

// BLEByteCharacteristic G_LED_Characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
// BLEByteCharacteristic B_LED_Characteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// // Initialize fingerprint sensor UART interface using pins D14 - tx / D13 - rx
// GT521F52 fps;

// void setup() {
//   // Ini
//   Serial.begin(115200);
//   Serial1.begin(115200);

//   pinMode(LEDG, OUTPUT);
//   pinMode(LEDB, OUTPUT);

//   BLE.begin();
//   BLE.setLocalName("LED Controller");
//   BLE.setAdvertisedService(ledService);
//   ledService.addCharacteristic(G_LED_Characteristic);
//   ledService.addCharacteristic(B_LED_Characteristic);
//   BLE.addService(ledService);
//   G_LED_Characteristic.writeValue(0);
//   B_LED_Characteristic.writeValue(0);
//   BLE.advertise();
// }

// void loop() {
  
//   BLEDevice central = BLE.central();

//   if (central) {
//     while (central.connected()) {
//       if (G_LED_Characteristic.written()) {
//         if (G_LED_Characteristic.value()) {
//           Serial.println("LEDG on & fps LED on");
//           digitalWrite(LEDG, LOW);

//           // Open
//           Serial1.write((byte)0x55);
//           Serial1.write((byte)0xaa);
//           Serial1.write((byte)0x01);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x01);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x01);
//           Serial1.write((byte)0x01);
//           delay(50);
//           Serial1.write((byte)0x55);
//           Serial1.write((byte)0xaa);
//           Serial1.write((byte)0x01);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x01);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x12);
//           Serial1.write((byte)0x00);
//           Serial1.write((byte)0x13);
//           Serial1.write((byte)0x01);

//           // fps.Open();
//           // if(!fps.SetLED(true)){
//           //   Serial.println("Error setting fps LED on");
//           //   int i = Serial1.available();
//           //   Serial.print("There are # ");
//           //   Serial.println(i);
//           // }
//         } else {
//           Serial.println("LEDG off & fps LED off");
//           digitalWrite(LEDG, HIGH);

//         //   if(!fps.SetLED(false)){
//         //     Serial.println("Error setting fps LED off");}
//         }
//       }
//       if (B_LED_Characteristic.written()) {
//         if (B_LED_Characteristic.value()) {
//           Serial.println("LEDB on");
//           digitalWrite(LEDB, LOW);
//         } else {
//           Serial.println("LEDB off");
//           digitalWrite(LEDB, HIGH);
//         }
//       }
//     }
//   }
// }