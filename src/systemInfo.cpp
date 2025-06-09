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
    tft.setTextSize(2);
    tft.setCursor(10, 20);
    tft.println("System Info");

    tft.setTextSize(1);

    tft.setCursor(5, 40);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Chip: ");
    tft.setTextColor(ST77XX_GREEN);
    tft.println(ESP.getChipModel());

    tft.setCursor(5, 60);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Cores: ");
    tft.setTextColor(ST77XX_GREEN);
    tft.println(ESP.getChipCores());

    tft.setCursor(5, 80);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Revision: ");
    tft.setTextColor(ST77XX_GREEN);
    tft.println(ESP.getChipRevision());

    tft.setCursor(5, 100);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Free RAM: ");
    tft.setTextColor(ST77XX_GREEN);
    tft.print(ESP.getFreeHeap() / 1024);
    tft.println(" KB");

    tft.setCursor(5, 120);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Flash size: ");
    tft.setTextColor(ST77XX_GREEN);
    tft.print(ESP.getFlashChipSize() / 1024 / 1024);
    tft.println(" MB");

    tft.setCursor(5, 140);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("MAC WiFi: ");
    tft.setTextColor(ST77XX_GREEN);
    tft.println(WiFi.macAddress());
}
