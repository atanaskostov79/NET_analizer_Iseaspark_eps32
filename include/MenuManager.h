#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H
#pragma once

enum MenuState {
    MENU_MAIN,
    MENU_WIFI,
    MENU_SYSINFO,

    MENU_BACK
};

void handleMenu();
void handleButtonA();
void handleButtonB();

#endif
