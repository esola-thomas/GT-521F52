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

#define OPEN_CMD_OFFSET 769
#define CLOSE_CMD_OFFSET 770
#define LED_ON_CMD_OFFSET 771
#define LED_OFF_CMD_OFFSET 772
#define GET_ENROLL_COUNT_OFFSET 774
#define CHECK_ENROLLMENT_OFFSET 775
#define ENROLL_START_OFFSET 776
#define IS_PRESS_FINGER_OFFSET 780
#define DELETE_ID_OFFSET 781
#define VERIFY_1_1_OFFSET 783
#define IDENTIFY_1_N_OFFSET 784


BLEService customService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Define a custom service UUID
BLEIntCharacteristic write_command_characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLEWrite); // Define a custom characteristic UUID with read and notify permissions
BLEStringCharacteristic str_resp_notification_characteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLENotify, 20);
BLEIntCharacteristic read_command_characteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead); // Define a custom characteristic UUID with read and notify permissions

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

int return_value;
void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    
    while (central.connected()) {
      if (write_command_characteristic.written()) {
        int command = write_command_characteristic.value();
        Serial.print("BLE Command Recived: 0x");
        Serial.println(command);
       switch (command){
          case OPEN_CMD:
          case  OPEN_CMD_OFFSET:
            fps.Open();
            break;

          case CLOSE_CMD:
          case CLOSE_CMD_OFFSET:
            fps.Close();
            break;

          case LED_ON_CMD:
          case LED_ON_CMD_OFFSET:
            fps.SetLED(true);
            
            break;

          case LED_OFF_CMD:
          case LED_OFF_CMD_OFFSET:
            fps.SetLED(false);
            break;

          case CHANGE_BAUDRATE_CMD:
            fps.ChangeBaudRate(115200);
            break;

          case GET_ENROLL_COUNT_CMD:
          case GET_ENROLL_COUNT_OFFSET:
            return_value = fps.GetEnrollCount();
            read_command_characteristic.writeValue(return_value);
            break;

          case CHECK_ENROLLED_CMD:
          case CHECK_ENROLLMENT_OFFSET:
            bool enrolled = fps.CheckEnrolled(command);
            return_value = enrolled ? 1 : 0;
            read_command_characteristic.writeValue(return_value);
            break;
          
          // Return:
          //	0 - ACK
          //	1 - Database is full
          //	2 - Invalid Position
          //	3 - Position(ID) is already used
          case ENROLL_START_CMD:
          case ENROLL_START_OFFSET:
            return_value = fps.EnrollStart(command);
            read_command_characteristic.writeValue(return_value);
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
          case IS_PRESS_FINGER_OFFSET:
            bool isPressed = fps.IsPressFinger();
            return_value = isPressed ? 1 : 0;
            read_command_characteristic.writeValue(return_value);
            break;

          case DELETE_ID_CMD:
          case DELETE_ID_OFFSET:
            bool delete_success = fps.DeleteID(command);
            return_value = delete_success ? 1 : 0;
            read_command_characteristic.writeValue(return_value);
            break;

          case DELETE_ALL_CMD:
            fps.DeleteAll();
            break;

          //	0 - Verified OK (the correct finger)
          //	1 - Invalid Position
          //	2 - ID is not in use
          //	3 - Verified FALSE (not the correct finger)
          case VERIFY_1_1_CMD:
          case VERIFY_1_1_OFFSET:
            return_value = fps.Verify1_1(command);
            read_command_characteristic.writeValue(return_value);
            break;

          //	Verified against the specified ID (found, and here is the ID number)
          //    0-2999, if using GT-521F52
          //  Failed to find the fingerprint in the database
          // 	  3000, if using GT-521F52
          case IDENTIFY_1_N_CMD:
          case IDENTIFY_1_N_OFFSET:
            return_value = fps.Identify1_N();
            read_command_characteristic.writeValue(return_value);
            break;

          // case CAPTURE_FINGER_CMD:
          //   fps.CaptureFinger();
          //   break;
          default:
            Serial.print("Invalid Command 0x");
            Serial.println(command);
            break;
        }
        String command_str = "Data Recived :)";
        str_resp_notification_characteristic.setValue(command_str);
      }
    }
    
    Serial.println("Disconnected from central: ");
    fps.SetLED(false);
    fps.Close();
    Serial.println(central.address());
  }
}