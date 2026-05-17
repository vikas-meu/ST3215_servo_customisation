#include <SCServo.h>

SMS_STS sms_sts;

// ESP32 UART pins
#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);

  // Initialize UART for servo communication
  Serial2.begin(1000000, SERIAL_8N1, RXD2, TXD2);

  // Attach serial port to servo library
  sms_sts.pSerial = &Serial2;

  delay(1000);

  Serial.println("Changing servo ID...");

  // Change ID from 1 to 3
  // Old ID, New ID
  sms_sts.unLockEprom(1);   // unlock EEPROM first
  delay(20);

  sms_sts.writeByte(1, SMS_STS_ID, 3);  
  delay(100);

  sms_sts.LockEprom(3);     // lock again using new ID
  delay(100);

  Serial.println("Done!");
  Serial.println("Servo ID changed from 1 to 3");
}

void loop() {
}
