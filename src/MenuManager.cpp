#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "MenuManager.h"
#include "wifiScanner.h"
#include "systemInfo.h"
#include "statusBar.h"
#include "lanLink.h"
#include "my_image.h"

extern Adafruit_ST7789 tft;

MenuState currentMenu = MENU_MAIN;
int menuIndex = 0;

const char* menuItems[] = {
    "Wi-Fi Scan",
    "LAN Link",
    "System Info",
    "Settings"
};
const int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

void drawMenu() {


    tft.drawRGBBitmap(0, 0, my_image, 170, 320);
    drawStatusBar(tft, true);
    tft.setCursor(10, 20);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.println("Main Menu");
    // tft.setTextSize(1);
    for (int i = 0; i < menuCount; ++i) {
        tft.setCursor(10, 60 + i * 25);
        if (i == menuIndex) {
            tft.setTextColor(ST77XX_YELLOW);
            tft.print("> ");
        } else {
            tft.print("  ");
            tft.setTextColor(ST77XX_WHITE);
        }
        tft.println(menuItems[i]);
    }

}

void handleMenu() {

    switch (currentMenu) {
        case MENU_MAIN:
            drawMenu();
            break;
        case MENU_WIFI:
            wifiScan(tft);
            currentMenu = MENU_MAIN;
            break;
        case MENU_LAN:
            lanLink(tft);
            currentMenu = MENU_MAIN;
            break;
        case MENU_SYSINFO:
            showSystemInfo(tft);
            currentMenu = MENU_MAIN;
            break;

        default:
            currentMenu = MENU_MAIN;
            break;
    }
}

void handleButtonA() {
    if (currentMenu == MENU_MAIN) {
        menuIndex = (menuIndex + 1) % menuCount;
        drawMenu();
    }
}

void handleButtonB() {
    if (currentMenu == MENU_MAIN) {
        switch (menuIndex) {
            case 0: currentMenu = MENU_WIFI; break;
            case 1: currentMenu = MENU_LAN; break;
            case 2: currentMenu = MENU_SYSINFO; break;


            case 3: /* Settings */ break;
        }
        handleMenu();
    }
}
