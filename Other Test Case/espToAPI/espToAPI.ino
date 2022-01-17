#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Avinash";
const char* password = "Avi7071955977";

void setup () {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=5146MN3GIAT14GB6");
    int httpCode = http.GET();
    if (httpCode > 0) 
    { 
      String payload = http.getString();  
      Serial.println(payload);            
    }
    http.end();   
  }
  delay(10000);   
}
