/*
  Proje: RFID Kart ile LED Kontrolü
  Platform: Arduino UNO
  Hazırlayan: Robomer
  Web: https://robomer.com

  Açıklama:
  Kayıtlı RFID kart okutulduğunda LED yanar.
  Yetkisiz kart okutulduğunda LED yanmaz.

  Bağlantılar:
  RC522 SDA / SS -> D10
  RC522 SCK      -> D13
  RC522 MOSI     -> D11
  RC522 MISO     -> D12
  RC522 RST      -> D9
  RC522 3.3V     -> 3.3V
  RC522 GND      -> GND

  LED uzun bacak -> 1K direnç üzerinden D7
  LED kısa bacak -> GND
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 7

MFRC522 rfid(SS_PIN, RST_PIN);

// Buraya kendi kart UID degerinizi yazin.
// UID okumak icin code/rfid-uid-okuyucu.ino dosyasini kullanin.
byte authorizedUIDs[][4] = {
  {0x39, 0xBC, 0x12, 0x07}
};

const byte authorizedCardCount = sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]);

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("RFID Kart ile LED Kontrolu");
  Serial.println("Kartinizi okutun...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  printUID();

  if (isAuthorizedCard(&rfid.uid)) {
    Serial.println("Yetkili kart. LED yaniyor.");
    digitalWrite(LED_PIN, HIGH);
    delay(3000);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    Serial.println("Yetkisiz kart. LED yanmaz.");
    digitalWrite(LED_PIN, LOW);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool isAuthorizedCard(MFRC522::Uid *uid) {
  if (uid->size != 4) {
    return false;
  }

  for (byte cardIndex = 0; cardIndex < authorizedCardCount; cardIndex++) {
    bool match = true;

    for (byte i = 0; i < 4; i++) {
      if (uid->uidByte[i] != authorizedUIDs[cardIndex][i]) {
        match = false;
        break;
      }
    }

    if (match) {
      return true;
    }
  }

  return false;
}

void printUID() {
  Serial.print("Okunan UID: ");

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
}
