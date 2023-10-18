#include <Arduino.h>
#include <ArduinoBLE.h>

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

// Setup BLE service
BLEService gtService("59cda1c2-b6af-488b-95ba-d152095a449a"); // Creating a BLE service

BLEIntCharacteristic commandCharacteristic("5a72f814-6d87-11ee-b962-0242ac120002", BLERead | BLEWrite); // Characteristic for receiving commands


void executeCommand(byte cmd[], int cmdLength);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  
  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("BLE initialization failed!");
    while (1);
  }

  BLE.setLocalName("GT_Controller");
  BLE.setAdvertisedService(gtService);

  // Adding characteristics
  gtService.addCharacteristic(commandCharacteristic);
  
  BLE.addService(gtService);

  commandCharacteristic.setValue(0);
  
  BLE.advertise();
  
  Serial.println("Bluetooth device active, waiting for connections..."); 
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    
    while (central.connected()) {
      if (commandCharacteristic.written()) {
        int command = commandCharacteristic.value();
        
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
            Serial.print("Invalid Command");
            break;
        }
      }
    }
    
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
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
  
  int index = 0;
  byte responseBytes[20];
  String response = "";
  
  while (Serial1.available() && index < 20) {
    byte currentByte = Serial1.read();
    responseBytes[index++] = currentByte;
    
    response += String(currentByte, HEX);
    response += " ";
  }
  
  Serial.print("Response from GT-521F52: ");
  Serial.println(response);
}
