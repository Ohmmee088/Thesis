#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
const char* ssid     = "RMUTSV_IoT";
const char* password = "CoE39201";
const char* serverName = "http://172.25.17.229/waste_room/esp32/add.php?";
WiFiClientSecure client;

int a=1;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = serverName;
    url += "&smell_1=";       url +=  a;
    url += "&smell_2=";       url +=  a;
    url += "&rubbish_1=";     url +=  a;
    url += "&rubbish_2=";     url +=  a;
    url += "&rubbish_3=";     url +=  a;
    url += "&rubbish_4=";     url +=  a;
    url += "&rubbish_5=";     url +=  a;
    url += "&rubbish_6=";     url +=  a;
    url += "&rubbish_7=";     url +=  a;
    url += "&rubbish_8=";     url +=  a;
    url += "&motion_1=";      url +=  a;
    url += "&motion_2=";      url +=  a;

    Serial.println(url);
    http.begin(url); //HTTP
    int httpCode = http.GET();

    if (httpCode > 0){
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        }
    } 
    else{
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

http.end();
}

delay(10000);
} //loop





