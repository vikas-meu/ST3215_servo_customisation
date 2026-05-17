#include <SCServo.h>

SMS_STS sms_sts;

// ESP32 UART pins
#define RXD2 16
#define TXD2 17

#define SERVO_ID 3
#define SERVO_CENTER 2048   // ST3215 center position

void setup() {
  Serial.begin(115200);

  // Servo UART
  Serial2.begin(1000000, SERIAL_8N1, RXD2, TXD2);

  sms_sts.pSerial = &Serial2;

  delay(1000);

  Serial.println("ST3215 Center Calibration Ready");
  Serial.println("Move servo by hand to desired center.");
  Serial.println("Then press 'm' in Serial Monitor.");
}

void loop() {

  // If serial command received
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'm' || cmd == 'M') {

      // Read current position
      int currentPos = sms_sts.ReadPos(SERVO_ID);

      if (currentPos < 0) {
        Serial.println("Servo not detected!");
        return;
      }

      // Calculate offset from center
      int offset = currentPos - SERVO_CENTER;

      Serial.print("Current Pos: ");
      Serial.println(currentPos);

      Serial.print("Calculated Offset: ");
      Serial.println(offset);

      // Unlock EEPROM
      sms_sts.unLockEprom(SERVO_ID);
      delay(20);

      // Write offset correction
      sms_sts.CalibrationOfs(SERVO_ID);

      delay(100);

      // Lock EEPROM again
      sms_sts.LockEprom(SERVO_ID);

      Serial.println("New center saved successfully!");
      Serial.println("Power cycle servo to confirm.");
    }
  }
}
