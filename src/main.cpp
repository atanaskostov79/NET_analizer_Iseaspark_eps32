#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <WiFi.h>

#include "my_image.h"
#include "wifiScanner.h"
#include "MenuManager.h"
#include "statusBar.h"
#include <BluetoothSerial.h>

#define TFT_CS     15
#define TFT_DC      2
#define TFT_RST     4
#define TFT_MOSI   23
#define TFT_SCLK   18

#define BUTTON_PIN 0  // GPIO0 = BOOT

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

unsigned long buttonPressStart = 0;
bool buttonPressed = false;
BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_BT"); // Име на Bluetooth устройството
    Serial.println("Bluetooth е стартиран");

    tft.init(170, 320);
    tft.setRotation(2);
    tft.fillScreen(ST77XX_BLACK);
    WiFi.mode(WIFI_STA);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    handleMenu();
    drawStatusBar(tft, true);


}

void loop() {




    if (!digitalRead(BUTTON_PIN)) {
        if (!buttonPressed) {
            buttonPressStart = millis();
            buttonPressed = true;
        } else {
            if (millis() - buttonPressStart > 1000) {
                handleButtonB();  // задържане = избор
                while (!digitalRead(BUTTON_PIN)); // чакай отпускане
                buttonPressed = false;
            }
        }
    } else {
        if (buttonPressed && millis() - buttonPressStart < 1000) {
            handleButtonA();  // кратко натискане = навигация
        }
        buttonPressed = false;
    }

      drawStatusBar(tft);
}
