#include <ArduinoBLE.h>
#include <FPS_GT511C3.h>

/*
  Green LED connection established
  Blue LED waiting for BLE connection
  RED LED setup in progress
*/ 

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


BLEService ble_service("19B10000-E8F2-537E-4F6C-D104768A1214"); // Define a custom service UUID
BLEIntCharacteristic write_command_characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLEWrite);
BLEStringCharacteristic str_resp_notification_characteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLENotify, 20);
BLEIntCharacteristic read_command_characteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead);
BLEIntCharacteristic write_user_id_characteristic("19B10004-E8F2-537E-4F6C-D104768A1214", BLEWrite);

int sensorValue = 0;
FPS_GT511C3 fps;

 void setup() {
  Serial.begin(115200);
  fps.init();
  // This is set in fps construct:
  // Serial1.begin(9600);

  // Enable the LEDs
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, HIGH);
  
  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("BLE initialization failed!");
    while (1);
  }

  BLE.setLocalName("GT_Controller");
  BLE.setAdvertisedService(ble_service);

  // Adding characteristics
  ble_service.addCharacteristic(write_command_characteristic);
  ble_service.addCharacteristic(str_resp_notification_characteristic);
  ble_service.addCharacteristic(read_command_characteristic);
  ble_service.addCharacteristic(write_user_id_characteristic);

  BLE.addService(ble_service);

  write_command_characteristic.setValue(0x00);
  str_resp_notification_characteristic.setValue("Hello World");
  read_command_characteristic.setValue(0x00);
  write_user_id_characteristic.setValue(0x00);
  
  BLE.advertise();
  
  Serial.println("Bluetooth device active, waiting for connections..."); 
}

int id;
int return_value;
bool bool_return;

// Portenta H7 inverts the HIGH and LOW due to poull up. This function inverts the logic
void set_led(unsigned led, PinStatus status);

void loop() {
  set_led(LEDG, LOW);
  set_led(LEDB, HIGH);
  set_led(LEDR, LOW);

  BLEDevice central = BLE.central();

  if (central) {
    set_led(LEDG, HIGH);
    set_led(LEDB, LOW);
    set_led(LEDR, LOW);

    Serial.print("Connected to central: ");
    Serial.println(central.address());
    
    while (central.connected()) {
      if (write_command_characteristic.written()) {
        int command = write_command_characteristic.value();
        Serial.print("BLE Command Recived: 0x");
        Serial.println(command);

        // Read BLE characteristic for id number
        id = write_user_id_characteristic.value();

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
            Serial.print("Enroll Count: ");
            Serial.println(return_value);
            read_command_characteristic.writeValue(return_value);
            break;

          case CHECK_ENROLLED_CMD:
          case CHECK_ENROLLMENT_OFFSET:
            bool_return = fps.CheckEnrolled(id);
            return_value = bool_return ? 1 : 0;
            Serial.print("Check enrrolment for id ");
            Serial.print(id);
            Serial.print(" returned ");
            Serial.println(return_value);
            read_command_characteristic.writeValue(return_value);
            break;
          
          case ENROLL_START_CMD:
          case ENROLL_START_OFFSET:
            return_value = fps.EnrollStart(id);
            read_command_characteristic.writeValue(return_value);
            Serial.print("Enroll Start for id ");
            Serial.print(id);
            Serial.print(" returned ");
            Serial.println(return_value);
            break;

          case IS_PRESS_FINGER_CMD:
          case IS_PRESS_FINGER_OFFSET:
            bool_return = fps.IsPressFinger();
            return_value = bool_return ? 1 : 0;
            read_command_characteristic.writeValue(return_value);
            Serial.print("Is Press Finger returned ");
            Serial.println(return_value);
            break;

          case DELETE_ID_CMD:
          case DELETE_ID_OFFSET:
            bool_return = fps.DeleteID(id);
            return_value = bool_return ? 1 : 0;
            read_command_characteristic.writeValue(return_value);
            Serial.print("Delete ID for id ");
            Serial.print(id);
            Serial.print(" returned ");
            Serial.println(return_value);
            break;

          case DELETE_ALL_CMD:
            fps.DeleteAll();
            break;

          case VERIFY_1_1_CMD:
          case VERIFY_1_1_OFFSET:
            return_value = fps.Verify1_1(id);
            read_command_characteristic.writeValue(return_value);
            Serial.print("Verify 1_1 for id ");
            Serial.print(id);
            Serial.print(" returned ");
            Serial.println(return_value);
            break;

          case IDENTIFY_1_N_CMD:
          case IDENTIFY_1_N_OFFSET:
            return_value = fps.Identify1_N();
            read_command_characteristic.writeValue(return_value);
            Serial.print("Identify 1_N returned ");
            Serial.println(return_value);
            break;

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

void set_led(unsigned led, PinStatus status){
  if (status == HIGH){
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }
}