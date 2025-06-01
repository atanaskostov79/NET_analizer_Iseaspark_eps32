#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <WiFi.h>
#include "wifiScanner.h"
#include "my_image.h"

#define TFT_CS     15
#define TFT_DC      2
#define TFT_RST     4
#define TFT_MOSI   23
#define TFT_SCLK   18

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
    Serial.begin(115200);

    tft.init(170, 320);
    tft.setRotation(2);
    tft.drawRGBBitmap(0, 0, my_image, 170, 320);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void loop() {
    wifiScanner(tft);

}
