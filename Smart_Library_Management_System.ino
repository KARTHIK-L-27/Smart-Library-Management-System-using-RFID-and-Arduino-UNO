#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
int buzzer = 8;

void setup() {
  SPI.begin();
  rfid.PCD_Init();
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("RFID Detected: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  Serial.println("Book Issued / Returned");

  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);

  rfid.PICC_HaltA();
}
