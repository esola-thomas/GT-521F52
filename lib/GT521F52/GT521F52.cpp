#include <GT521F52.h>

class Comand_packet{
    public:
        class Commands{
            public:
                byte Open[12]           = {0x55, 0xAA, 0x01, 0x00, 0x00, 
                                         0x00, 0x00, 0x00, 0x01, 0x00, 
                                         0x01, 0x01};
                byte Close[12]          = {0x55, 0xAA, 0x01, 0x00, 0x00, 
                                         0x00, 0x00, 0x00, 0x02, 0x00, 
                                         0x02, 0x01};
                // USBInternalCheck
                byte ChangeBaudrate[12] = {};
                byte led_on[12]         = {0x55, 0xAA, 0x01, 0x00, 0x01, 
                                         0x00, 0x00, 0x00, 0x12, 0x00, 
                                         0x13, 0x01};
                byte led_off[12]        = {0x55, 0xAA, 0x01, 0x00, 0x00, 
                                         0x00, 0x00, 0x00, 0x12, 0x00, 
                                         0x12, 0x01};
                byte GetEnrollCount[12] = {0x55, 0xAA, 0x01, 0x00, 0x00, 
                                         0x00, 0x00, 0x00, 0x20, 0x00, 
                                         0x20, 0x01}; // check
                byte CheckEnrolled[12]  = {0x55, 0xAA, 0x01, 0x00, 0x00, 
                                         0x00, 0x00, 0x00, 0x21, 0x00, 
                                         0x21, 0x01}; // check
                byte EnrollStart[12]    = {0x55, 0xAA, 0x01, 0x00, 0x00, 
                                         0x00, 0x00, 0x00, 0x22, 0x00, 
                                         0x22, 0x01}; // check
                byte Enroll1[12]        = {0x55, 0xAA, 0x01, 0x00, 0x01, 
                                         0x00, 0x00, 0x00, 0x23, 0x00, 
                                         0x24, 0x01}; // check
                byte Enroll2[12]        = {0x55, 0xAA, 0x01, 0x00, 0x02,
                                         0x00, 0x00, 0x00, 0x23, 0x00, 
                                         0x24, 0x01}; // check probs wrong
                byte Enroll3[12]        = {0x55, 0xAA, 0x01, 0x00, 0x03, 
                                         0x00, 0x00, 0x00, 0x23, 0x00, 
                                         0x24, 0x01}; // check probs wrong
                byte IsPressFinger[12]  = {0x55, 0xAA, 0x01, 0x00, 0x00, 
                                         0x00, 0x00, 0x00, 0x26, 0x00, 
                                         0x26, 0x01}; // check
                byte DeleteID[12]       = {0x55, 0xAA, 0x01, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x40, 0x00, 
                                         0x40, 0x01}; // check
                byte DeleteAll[12]      = {0x55, 0xAA, 0x01, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x41, 0x00, 
                                            0x41, 0x01}; // check
                byte Verify1_1[12]      = {0x55, 0xAA, 0x01, 0x00, 0x01,
                                            0x00, 0x00, 0x00, 0x50, 0x00, 
                                            0x51, 0x01}; // check
                byte Identify1_N[12]    = {0x55, 0xAA, 0x01, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x51, 0x00, 
                                            0x51, 0x01}; // check   
                byte CaptureFinger[12]  = {0x55, 0xAA, 0x01, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x60, 0x00, 
                                         0x60, 0x01}; // check
                byte MakeTemplate[12]    = {0x55, 0xAA, 0x01, 0x00, 0x02,
                                         0x00, 0x00, 0x00, 0x61, 0x00, 
                                         0x62, 0x01}; // check
                byte GetImage[12]        = {0x55, 0xAA, 0x01, 0x00, 0x01,
                                         0x00, 0x00, 0x00, 0x62, 0x00, 
                                         0x63, 0x01}; // check
                byte GetRawImage[12]     = {0x55, 0xAA, 0x01, 0x00, 0x01,
                                         0x00, 0x00, 0x00, 0x63, 0x00, 
                                         0x64, 0x01}; // check
                byte GetTemplate[12]     = {0x55, 0xAA, 0x01, 0x00, 0x01,
                                         0x00, 0x00, 0x00, 0x70, 0x00, 
                                         0x71, 0x01}; // check
                byte SetTemplate[12]     = {0x55, 0xAA, 0x01, 0x00, 0x02,
                                         0x00, 0x00, 0x00, 0x71, 0x00, 
                                         0x72, 0x01}; // check
                byte GetDatabaseStart[12]= {0x55, 0xAA, 0x01, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x72, 0x00, 
                                         0x72, 0x01}; // check
                byte GetDatabaseEnd[12]  = {0x55, 0xAA, 0x01, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x73, 0x00, 
                                         0x73, 0x01}; // check
                byte UpgradeFirmware[12] = {0x55, 0xAA, 0x01, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x80, 0x00, 
                                         0x80, 0x01}; // check
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