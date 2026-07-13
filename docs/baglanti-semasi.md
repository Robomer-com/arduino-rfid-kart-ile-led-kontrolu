# Bağlantı Şeması - RFID Kart ile LED Kontrolü

## RC522 RFID Modül

| RC522 | Arduino UNO |
|---|---|
| SDA / SS | D10 |
| SCK | D13 |
| MOSI | D11 |
| MISO | D12 |
| RST | D9 |
| 3.3V | 3.3V |
| GND | GND |

## LED

| LED | Arduino UNO |
|---|---|
| Uzun bacak | 1K direnç üzerinden D7 |
| Kısa bacak | GND |

## Not

RC522 modülü 3.3V ile besleyin. 5V besleme modüle zarar verebilir.
