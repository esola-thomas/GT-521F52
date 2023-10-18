#ifndef GT521F52_h
#define GT521F52_h
#include <Arduino.h>

#endif  //__GNUC__

class Comand_packet{
    public:
        class Commands{
            public:
                byte Open[12];
                byte Close[12];
                // USBInternalCheck;
                byte ChangeBaudrate[12];
                byte led_on[12];
                byte led_off[12];
                byte GetEnrollCount[12];
                byte CheckEnrolled[12];
                byte EnrollStart[12];
                byte Enroll1[12];
                byte Enroll2[12]; 
                byte Enroll3[12];
                byte IsPressFinger[12];
                byte DeleteID[12];
                byte DeleteAll[12];
                byte Verify1_1[12]; 
                byte Identify1_N[12];
                byte CaptureFinger[12];
                byte MakeTemplate[12]; 
                byte GetImage[12];
                byte GetRawImage[12]; 
                byte GetTemplate[12];
                byte SetTemplate[12];
                byte GetDatabaseStart[12];
                byte GetDatabaseEnd[12];
                byte UpgradeFirmware[12];
        };
        class GT521F52 {
        public:
            GT521F52();
            bool begin(arduino::UART* serial);
            bool verifyPassword();
            bool open();
            bool close();
            bool changeBaudrate(uint32_t baudrate);
            bool ledOn();
            bool ledOff();
            uint16_t getEnrollCount();
            bool checkEnrolled(uint16_t id);
            bool enrollStart(uint16_t id);
            bool enroll1();
            bool enroll2();
            bool enroll3();
            uint8_t isPressFinger();
            bool deleteID(uint16_t id);
            bool deleteAll();
            bool verify1_1(uint16_t id);
            uint16_t identify1_N();
            bool captureFinger();
            bool makeTemplate();
            bool getImage();
            bool getRawImage();
            bool getTemplate(uint16_t id, uint8_t *templateData);
            bool setTemplate(uint16_t id, uint8_t *templateData);
            uint16_t getDatabaseStart();
            uint16_t getDatabaseEnd();
            bool upgradeFirmware();
        private:
            arduino::UART *_serial;
            uint32_t _baudrate;
            bool sendCommand(Comand_packet::Commands command);
            bool receiveResponse(uint8_t *response, uint16_t expectedLength);
            uint16_t calculateChecksum(uint8_t *data, uint16_t length);
            bool verifyChecksum(uint8_t *data, uint16_t length);
        };
};