//
// Created by Josue Figueroa on 12/25/20.
//

#define MAX_DEPTH 3

#include "UI_Main.h"
#include "UI_Reservoir.h"
#include "UI_PhMonitor.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

chainStream<0> in(NULL);

// TODO: reservoir depth calibration

// Reservoir Menus
TOGGLE(pumpingOn, toggleReservoirPump, "Pump: ", doExit, enterEvent, noStyle
       ,VALUE("On", true, turnOnReservoirPump, noEvent)
       ,VALUE("Off", false, turnOffReservoirPump, noEvent)
       );

MENU(reservoirMenu, "Reservoir", doNothing, noEvent, noStyle
     ,SUBMENU(toggleReservoirPump)
     ,FIELD(threshold, "Threshold", "%", 1, 100, 10, 1, setReservoirThreshold, enterEvent, noStyle)
     ,FIELD(reservoirDuration, "Duration", "s", 1, 12, 1, 1, setReservoirDuration, enterEvent, noStyle)
     ,FIELD(reservoirInterval, "Interval", "s", 1, 12, 1, 1, setReservoirInterval, enterEvent, noStyle)
     ,EXIT("< Back")
     );

// pH Monitor

TOGGLE(phMonitoring, togglePhMonitor, "Monitor: ", doExit, enterEvent, noStyle
       ,VALUE("On", true, turnOnPhMonitor, noEvent)
       ,VALUE("Off", false, turnOffPhMonitor, noEvent)
       );

MENU(phMonitorMenu, "pH Monitor", doNothing, noEvent, noStyle
     ,SUBMENU(togglePhMonitor)
     ,FIELD(idealPh, "Ideal pH","", 1,14,1,0.1, setIdealPh, enterEvent, noStyle)
     ,FIELD(phPumpDuration, "Duration", "s", 1,10,1,1, setPhPumpDuration, enterEvent, noStyle)
     ,FIELD(phPollInterval, "Interval", "m", 5,120,5,1, setPhPollInterval, enterEvent, noStyle)
     ,EXIT("< Back")
     );

MENU(mainMenu, "Home", doNothing, noEvent, wrapStyle
     ,SUBMENU(reservoirMenu)
     ,SUBMENU(phMonitorMenu)
     );

MENU_OUTPUTS(out, MAX_DEPTH
,LIQUIDCRYSTAL_OUT(lcd,{0,0,16,2})
,NONE
);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);   //the navigation root object

void pollUi() {
  nav.poll();
  analogButtons.check();
}