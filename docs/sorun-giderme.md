# Sorun Giderme - RFID Kart ile LED Kontrolü

## Kart okunmuyor

- RC522 modülün 3.3V ile beslendiğinden emin olun.
- SDA, SCK, MOSI, MISO ve RST bağlantılarını kontrol edin.
- MFRC522 kütüphanesinin kurulu olduğundan emin olun.
- Kartı modüle birkaç santimetre mesafeden okutun.

## LED yanmıyor

- LED yönünü kontrol edin.
- Direncin LED uzun bacağı ile D7 arasında olduğundan emin olun.
- Kart UID değerinin koda doğru girildiğini kontrol edin.
- Önce UID okuyucu kodu ile kart UID değerini yeniden okuyun.

## UID eşleşmiyor

- Kart UID değerlerini HEX formatında ve virgüllerle yazın.
- Ana koddaki `authorizedUIDs` alanını kontrol edin.
