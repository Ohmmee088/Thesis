
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
/* Uno's A4 to SDA & A5 to SCL */
String tagid = "D3 5E A1 0E";
NfcTag tag;

void setup(void) {
Serial.begin(115200);
Serial.println("NDEF Reader");
nfc.begin();
}

void loop() {
Serial.println("\nScan a NFC tag\n");

  if (nfc.tagPresent())
    {
      NfcTag tag = nfc.read();
      tag.print();   
      if (tagid.equals(tag.getUidString())) 
              {
                Serial.println("");
                Serial.println("okok");
                delay(1000);
              }
            else
              {
                  Serial.println("not ok");
              }
    }
      

Serial.println("run return");
delay(1000);
}