// สร้างโดย Allnewstep.com รายละเอียดเพิ่มเติมที่นี่ https://www.allnewstep.com/p/146
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

void setup() {
  Serial.begin(9600);
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }else{
    Serial.println("AllNewStep: NFC Module is Ready !!!");
  }
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
  Serial.println("Input RFID/NCF card");
}

void loop() {
  boolean success;  //rfid pn532
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // บัฟเฟอร์สำหรับเก็บเลข ID ของ Tag
  uint8_t uidLength;                        // ความยาวของ ID (4 หรือ 7 ไบท์ ขึ้นกับประเภทของ Tag )
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength); // สั่งอ่าน Tag RFID
  if (success) {
    Serial.print("Found a card UID Value: ");
    for (uint8_t i = 0; i < uidLength; i++) // แสดงผลเลข ID ของ Tag RFID
    {
      Serial.print(" 0x"); Serial.print(uid[i], HEX);
    }
    Serial.println("");
    Serial.println("1111111111");
    delay(1000);
  }
  else
  {
    Serial.println("Timed out waiting for a card");
  }
}