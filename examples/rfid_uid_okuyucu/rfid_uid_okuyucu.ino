/*
  Proje: RC522 RFID UID Okuyucu
  Platform: Arduino UNO
  Hazırlayan: Robomer
  Web: https://robomer.com

  Açıklama:
  Bu kod RC522 RFID modül ile kart veya anahtarlık UID değerini okur
  ve Arduino IDE Seri Monitör ekranına yazdırır.

  Bağlantılar:
  RC522 SDA / SS -> D10
  RC522 SCK      -> D13
  RC522 MOSI     -> D11
  RC522 MISO     -> D12
  RC522 RST      -> D9
  RC522 3.3V     -> 3.3V
  RC522 GND      -> GND

  Seri Monitör:
  Baud rate: 9600
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  Serial.println("RC522 RFID UID Okuyucu");
  Serial.println("Kartinizi okutun...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Kart UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print("0x");

    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1) {
      Serial.print(", ");
    }
  }

  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
