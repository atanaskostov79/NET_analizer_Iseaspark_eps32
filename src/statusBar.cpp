#include "statusBar.h"
#include <BluetoothSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define BATTERY_PIN 34
#define ST77XX_DARKGREY 0x7BEF

extern BluetoothSerial SerialBT;

static bool lastBtState = !true;
static int lastBatteryLevel = -1;

void drawBatteryIcon(Adafruit_ST7789 &tft, int x, int y, int level) {
    tft.drawRect(x, y, 20, 8, ST77XX_WHITE);             // рамка
    tft.fillRect(x + 20, y + 2, 2, 4, ST77XX_WHITE);     // "пин"

    int fillWidth = map(level, 0, 100, 0, 18);
    uint16_t fillColor = (level < 20) ? ST77XX_RED : (level < 50) ? ST77XX_YELLOW : ST77XX_GREEN;
    tft.fillRect(x + 1, y + 1, fillWidth, 6, fillColor);
}

void drawStatusBar(Adafruit_ST7789 &tft, bool forceRedraw) {
    bool btState = SerialBT.hasClient();
    int batteryLevel = analogRead(BATTERY_PIN) * 100 / 4095;

    if (forceRedraw || btState != lastBtState || batteryLevel != lastBatteryLevel) {
        tft.fillRect(0, 0, 170, 12, ST77XX_BLACK);

        tft.setCursor(5, 2);
        tft.setTextColor(btState ? ST77XX_CYAN : ST77XX_DARKGREY);
        tft.setTextSize(1);
        tft.print("BT:");
        tft.print(btState ? "ON" : "OFF");

        drawBatteryIcon(tft, 170 - 26, 2, batteryLevel);

        lastBtState = btState;
        lastBatteryLevel = batteryLevel;
    }
}
