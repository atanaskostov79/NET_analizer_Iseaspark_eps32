#include "wifiScanner.h"
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "my_image.h"
#include "statusBar.h"
#include <Ethernet.h>

// extern Adafruit_ST7789 tft;
#define W5500_CS 5
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;
bool testInternetConnection() {
    IPAddress testIP(8, 8, 8, 8);   // Google DNS
    const uint16_t testPort = 53;  // DNS порт

    // Пробваме да се свържем с таймаут
    if (client.connect(testIP, testPort)) {
        client.stop();
        return true;
    } else {
        client.stop();
        return false;
    }
}
void lanLink(Adafruit_ST7789 &tft) {
    tft.drawRGBBitmap(0, 0, my_image, 170, 320);
    drawStatusBar(tft, true);
    tft.setCursor(10, 20);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.println("LAN test");
    tft.setTextSize(1);


    Ethernet.init(W5500_CS);
    delay(1000);

    if (Ethernet.begin(mac) == 0) {
        tft.setCursor(10, 40);
        tft.println("DHCP Failed.");
        return;
    }

    IPAddress ip = Ethernet.localIP();

    tft.setCursor(5, 40);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("IP: ");
    tft.setTextColor(ST77XX_GREEN);
    tft.println(ip);

    tft.setCursor(5, 60);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Subnet :");
    tft.setTextColor(ST77XX_GREEN);
    tft.print(Ethernet.subnetMask());

    tft.setCursor(5, 80);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Gateway :");
    tft.setTextColor(ST77XX_GREEN);
    tft.print(Ethernet.gatewayIP());

    tft.setCursor(5, 100);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("DNS :");
    tft.setTextColor(ST77XX_GREEN);
    tft.print(Ethernet.dnsServerIP());

    tft.setTextSize(2);
    tft.setCursor(10, 130);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("Internet: ");

    tft.setTextColor(ST77XX_GREEN);

   if (testInternetConnection()) {
        tft.println("OK");
    } else {
        tft.println("FAIL");
    }

}
