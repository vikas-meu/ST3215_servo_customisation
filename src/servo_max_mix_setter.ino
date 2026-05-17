#include <SCServo.h>

SMS_STS sms_sts;

#define RXD2 16
#define TXD2 17

#define SERVO_ID 3

// ST3215 EEPROM limit registers
// (Used in SC/STS protocol)
#define MIN_ANGLE_REG 9
#define MAX_ANGLE_REG 11

int currentPos = 0;

void setup() {
  Serial.begin(115200);

  Serial2.begin(1000000, SERIAL_8N1, RXD2, TXD2);
  sms_sts.pSerial = &Serial2;

  delay(1000);

  Serial.println("===== ST3215 EEPROM LIMIT SETUP =====");
  Serial.println("L = Save current position as LOWEST limit");
  Serial.println("H = Save current position as HIGHEST limit");
  Serial.println("R = Read saved limits");
}

void loop() {

  if (Serial.available()) {

    char cmd = Serial.read();

    currentPos = sms_sts.ReadPos(SERVO_ID);

    if (currentPos < 0) {
      Serial.println("Servo not detected.");
      return;
    }

    // Unlock EEPROM before writing
    if (cmd == 'L' || cmd == 'l') {

      sms_sts.unLockEprom(SERVO_ID);
      delay(20);

      // Write 2-byte minimum angle limit
      sms_sts.writeWord(SERVO_ID, MIN_ANGLE_REG, currentPos);

      delay(50);

      sms_sts.LockEprom(SERVO_ID);

      Serial.print("Minimum limit saved = ");
      Serial.println(currentPos);
    }

    // Save max limit
    if (cmd == 'H' || cmd == 'h') {

      sms_sts.unLockEprom(SERVO_ID);
      delay(20);

      // Write 2-byte maximum angle limit
      sms_sts.writeWord(SERVO_ID, MAX_ANGLE_REG, currentPos);

      delay(50);

      sms_sts.LockEprom(SERVO_ID);

      Serial.print("Maximum limit saved = ");
      Serial.println(currentPos);
    }

    // Read back
    if (cmd == 'R' || cmd == 'r') {

      int minVal = sms_sts.readWord(SERVO_ID, MIN_ANGLE_REG);
      int maxVal = sms_sts.readWord(SERVO_ID, MAX_ANGLE_REG);

      Serial.print("Saved Min = ");
      Serial.println(minVal);

      Serial.print("Saved Max = ");
      Serial.println(maxVal);
    }
  }
}
