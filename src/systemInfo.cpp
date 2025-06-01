//
// Created by crom on 01.06.25.
//

#include "systemInfo.h"
#include <WiFi.h>  // за MAC и други детайли
#include "my_image.h"
#include "statusBar.h"

void showSystemInfo(Adafruit_ST7789 &tft) {
    tft.drawRGBBitmap(0, 0, my_image, 170, 320);

    drawStatusBar(tft, true);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.setCursor(10, 20);
    tft.println("System Info:");

    // Чип информация
    tft.print("Chip: ");
    tft.println(ESP.getChipModel());

    tft.print("Cores: ");
    tft.println(ESP.getChipCores());

    tft.print("Revision: ");
    tft.println(ESP.getChipRevision());

    // RAM
    tft.print("Free RAM: ");
    tft.print(ESP.getFreeHeap() / 1024);
    tft.println(" KB");

    // Flash
    tft.print("Flash size: ");
    tft.print(ESP.getFlashChipSize() / 1024 / 1024);
    tft.println(" MB");

    // MAC адрес
    tft.print("MAC: ");
    tft.println(WiFi.macAddress());
}
