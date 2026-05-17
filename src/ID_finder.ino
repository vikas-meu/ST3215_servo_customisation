#include <SCServo.h>

SMS_STS sms_sts;

// ESP32 UART pins
#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);

  // Servo UART
  Serial2.begin(1000000, SERIAL_8N1, RXD2, TXD2);

  sms_sts.pSerial = &Serial2;

  delay(1000);

  Serial.println("Scanning for ST3215 servo IDs...");
  Serial.println("--------------------------------");

  // Scan IDs
  for (int id = 0; id <= 20; id++) {

    int pos = sms_sts.ReadPos(id);

    // If servo responds
    if (pos >= 0) {
      Serial.print("Servo Found! ID = ");
      Serial.print(id);

      Serial.print(" | Position = ");
      Serial.println(pos);
    }

    delay(50);
  }

  Serial.println("--------------------------------");
  Serial.println("Scan complete.");
}

void loop() {
}
