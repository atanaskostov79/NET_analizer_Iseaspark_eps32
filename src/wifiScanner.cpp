#include "wifiScanner.h"
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "my_image.h"
#include "statusBar.h"

// extern Adafruit_ST7789 tft;

void wifiScan(Adafruit_ST7789 &tft) {

    int n = WiFi.scanNetworks();
    tft.drawRGBBitmap(0, 0, my_image, 170, 320);
    drawStatusBar(tft, true);
    tft.setCursor(10, 20);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.println("Wi-Fi net");
    tft.setTextSize(1);

    if (n == 0) {
        tft.setCursor(10, 225);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(1);
        tft.print("No networks found");
    } else {
        for (int i = 0; i < n && i < 10; ++i) {
            int y = 40 + i * 25;

            String ssid = WiFi.SSID(i);
            String bssidstr = WiFi.BSSIDstr(i);
            int rssi = WiFi.RSSI(i);
            int strength = map(rssi, -100, -30, 0, 100); // %

            tft.setCursor(5, y);
            tft.setTextColor(ST77XX_YELLOW);
            tft.print(ssid);

            tft.setTextColor(ST77XX_GREEN);
            tft.setCursor(5, y + 10);
            tft.print(bssidstr);

            tft.setCursor(140, y);
            tft.setTextColor(ST77XX_CYAN);
            tft.print(strength);
            tft.print("%");
        }
    }

    delay(10000);
}
