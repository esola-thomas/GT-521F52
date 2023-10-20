#include <ArduinoBLE.h>
#include <FPS_GT511C3.h>

// Defines to easily controll BLE commands
#define OPEN_CMD 1
#define CLOSE_CMD 2
#define LED_ON_CMD 3
#define LED_OFF_CMD 4
#define CHANGE_BAUDRATE_CMD 5
#define GET_ENROLL_COUNT_CMD 6
#define CHECK_ENROLLED_CMD 7
#define ENROLL_START_CMD 8
#define ENROLL_1_CMD 9
#define ENROLL_2_CMD 10
#define ENROLL_3_CMD 11
#define IS_PRESS_FINGER_CMD 12
#define DELETE_ID_CMD 13
#define DELETE_ALL_CMD 14
#define VERIFY_1_1_CMD 15
#define IDENTIFY_1_N_CMD 16
#define CAPTURE_FINGER_CMD 17


BLEService customService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Define a custom service UUID
BLEIntCharacteristic write_command_characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLEWrite); // Define a custom characteristic UUID with read and notify permissions
BLEStringCharacteristic str_resp_notification_characteristic("87124c84-6dd8-11ee-b962-0242ac120002", BLENotify, 20);

int sensorValue = 0;
FPS_GT511C3 fps;

 void setup() {
  Serial.begin(115200);
  fps.init();
  // This is set in fps construct:
  // Serial1.begin(9600);
  
  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("BLE initialization failed!");
    while (1);
  }

  BLE.setLocalName("GT_Controller");
  BLE.setAdvertisedService(customService);

  // Adding characteristics
  customService.addCharacteristic(write_command_characteristic);
  customService.addCharacteristic(str_resp_notification_characteristic);

  BLE.addService(customService);

  write_command_characteristic.setValue(0x00);
  str_resp_notification_characteristic.setValue("Hello World");
  
  BLE.advertise();
  
  Serial.println("Bluetooth device active, waiting for connections..."); 
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    
    while (central.connected()) {
      if (write_command_characteristic.written()) {
        int command = write_command_characteristic.value();

       switch (command){
          case OPEN_CMD:
            fps.Open();
            break;
          case CLOSE_CMD:
            fps.Close();
            break;
          case LED_ON_CMD:
            fps.SetLED(true);
            break;
          case LED_OFF_CMD:
            fps.SetLED(false);
            break;
          case CHANGE_BAUDRATE_CMD:
            fps.ChangeBaudRate(115200);
            break;
          case GET_ENROLL_COUNT_CMD:
            fps.GetEnrollCount();
            break;
          case CHECK_ENROLLED_CMD:
            fps.CheckEnrolled(command);
            break;
          case ENROLL_START_CMD:
            fps.EnrollStart(command);
            break;
          // case ENROLL_1_CMD:
          //   fps.Enroll1(command);
          //   break;
          // case ENROLL_2_CMD:
          //   fps.Enroll2(command);
          //   break;
          // case ENROLL_3_CMD:
          //   fps.Enroll3(command);
          //   break;
          case IS_PRESS_FINGER_CMD:
            fps.IsPressFinger();
            break;
          case DELETE_ID_CMD:
            fps.DeleteID(command);
            break;
          case DELETE_ALL_CMD:
            fps.DeleteAll();
            break;
          case VERIFY_1_1_CMD:
            fps.Verify1_1(command);
            break;
          case IDENTIFY_1_N_CMD:
            fps.Identify1_N();
            break;
          // case CAPTURE_FINGER_CMD:
          //   fps.CaptureFinger();
          //   break;
          default:
            Serial.print("Invalid Command");
            break;
        }
        String command_str = "Data Recived :)";
        str_resp_notification_characteristic.setValue(command_str);

        Serial.println(command);
      }
    }
    
    Serial.print("Disconnected from central: ");
    fps.SetLED(false);
    fps.Close();
    Serial.println(central.address());
  }
}