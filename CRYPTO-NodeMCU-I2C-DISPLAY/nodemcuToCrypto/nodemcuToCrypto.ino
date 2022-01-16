#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266HTTPClient.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "Avinash";
const char* password = "Avi";
String payload;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=ZW67LQXPRSLIVU6C");
    int httpCode = http.GET();
    if (httpCode > 0) 
    { 
      payload = http.getString();  
      Serial.println(payload); 
      int len = payload.length();
      Serial.println(len);
      payload.remove(len - 7, 7);
      Serial.println(payload);  
      payload.remove(0,10);
      Serial.println(payload);         
    }
    http.end();   
  }
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("BTC in Rs ");
  display.print(payload);
  display.display(); 
  display.clearDisplay();
  delay(5000);
}


