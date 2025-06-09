#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <WiFi.h>
#include <BluetoothSerial.h>

#include "my_image.h"
#include "wifiScanner.h"
#include "MenuManager.h"
#include "statusBar.h"

// === Дисплей конфигурация ===
#define TFT_CS     15
#define TFT_DC      2
#define TFT_RST     4

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// === Бутон ===
#define BUTTON_PIN 0              // GPIO0 (BOOT бутон)
#define DEBOUNCE_MS 50
#define LONG_PRESS_MS 1000

unsigned long lastButtonPress = 0;
bool buttonState = false;
bool buttonWasPressed = false;
bool longPressHandled = false;

// === Bluetooth ===
BluetoothSerial SerialBT;

// === Debounce функция ===
void updateButton() {
    bool reading = !digitalRead(BUTTON_PIN); // active LOW

    if (reading && !buttonState && millis() - lastButtonPress > DEBOUNCE_MS) {
        buttonState = true;
        lastButtonPress = millis();
        longPressHandled = false;
    } else if (!reading && buttonState) {
        buttonState = false;
        if (!longPressHandled) {
            buttonWasPressed = true;
        }
    }
}

bool wasButtonPressed() {
    if (buttonWasPressed) {
        buttonWasPressed = false;
        return true;
    }
    return false;
}

// === Setup ===
void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_BT");
    Serial.println("Bluetooth е стартиран");

    tft.init(170, 320);
    tft.setRotation(2);
    tft.fillScreen(ST77XX_BLACK);

    WiFi.mode(WIFI_STA);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    handleMenu();
    drawStatusBar(tft, true);
}

// === Loop ===
void loop() {
    updateButton();

    if (wasButtonPressed()) {
        handleButtonA();
    }

    if (buttonState && !longPressHandled && millis() - lastButtonPress > LONG_PRESS_MS) {
        handleButtonB();
        longPressHandled = true;
        while (!digitalRead(BUTTON_PIN)) {
            delay(10);
        }
        buttonState = false;
    }

    drawStatusBar(tft);
}
