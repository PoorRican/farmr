//
// Created by Josue Figueroa on 12/25/20.
//

#define MAX_DEPTH 3

#include "ui/UI_Main.h"
#include "ui/UI_Reservoir.h"
#include "ui/UI_PhMonitor.h"
#include "ui/UI_TempMonitor.h"
#include "ui/UI_Settings.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

chainStream<0> in(NULL);

// TODO: reservoir depth calibration

// Reservoir Menus
TOGGLE(pumpingOn, toggleReservoirPump, "Relay: ", doExit, enterEvent, noStyle
       , VALUE("On", true, turnOnReservoirCycle, noEvent)
       , VALUE("Off", false, turnOffReservoirCycle, noEvent)
       );

MENU(reservoirMenu, "Reservoir", doNothing, noEvent, noStyle
     ,SUBMENU(toggleReservoirPump)
     ,FIELD(reservoirLevel, "H2O Volume", "%", 0, 0, 0, 0, doNothing, noEvent, noStyle)
     ,FIELD(threshold, "Threshold", "%", 1, 100, 10, 1, setReservoirThreshold, enterEvent, noStyle)
     ,FIELD(reservoirDuration, "Duration", "m", 1, 12, 1, 1, setReservoirDuration, enterEvent, noStyle)
     ,FIELD(reservoirInterval, "Interval", "h", 1, 12, 1, 1, setReservoirInterval, enterEvent, noStyle)
     ,EXIT("< Back")
     );

// pH Monitor

MENU(phCalibrate, "Calibrate pH", doNothing, noEvent, wrapStyle
     ,OP("Set 4.0", calibratePhFour, enterEvent)
     ,OP("Set 7.0", calibratePhSeven, enterEvent)
     ,OP("Set 10.0", calibratePhTen, enterEvent)
     ,EXIT("< Back")
     )

TOGGLE(phMonitoring, togglePhMonitor, "Monitor: ", doExit, enterEvent, noStyle
       ,VALUE("On", true, turnOnPhMonitor, noEvent)
       ,VALUE("Off", false, turnOffPhMonitor, noEvent)
       );

MENU(phMonitorMenu, "pH Monitor", doNothing, noEvent, wrapStyle
     ,SUBMENU(togglePhMonitor)
     ,FIELD(currentPh, "Current pH","", 0,0,0,0, doNothing, noEvent, noStyle)
     ,FIELD(idealPh, "Ideal pH","", 1,14,1,0.1, setIdealPh, enterEvent, noStyle)
     ,FIELD(phPumpDuration, "Duration", "s", 1,10,1,1, setPhPumpDuration, enterEvent, noStyle)
     ,FIELD(phPollInterval, "Interval", "m", 5,120,5,1, setPhPollInterval, enterEvent, noStyle)
     ,SUBMENU(phCalibrate)
     ,EXIT("< Back")
     );


// pH Monitor

TOGGLE(tempMonitoring, toggleTempMonitor, "Monitor: ", doExit, enterEvent, noStyle
,VALUE("On", true, turnOnTempMonitor, noEvent)
,VALUE("Off", false, turnOffTempMonitor, noEvent)
);

MENU(tempMonitorMenu, "Temp Monitor", doNothing, noEvent, noStyle
,SUBMENU(toggleTempMonitor)
,FIELD(currentTemp, "Current Temp","C", 0,0,0,0, doNothing, noEvent, noStyle)
,FIELD(idealTemp, "Ideal Temp","C", 10,30,1,0.1, setIdealTemp, enterEvent, noStyle)
,FIELD(tempDuration, "Duration", "m", 5,20,1,1, setTempDuration, enterEvent, noStyle)
,FIELD(tempInterval, "Interval", "m", 25,120,5,1, setTempInterval, enterEvent, noStyle)
,EXIT("< Back")
);


/// Settings Menu

MENU(restoreDefaultsMenu, "Reset All", doNothing, enterEvent, noStyle
     ,OP("Yes", restoreDefaults, enterEvent)
     ,OP("No", doExit, enterEvent));

MENU(settingsMenu, "Settings", doNothing, noEvent, noStyle
     ,SUBMENU(restoreDefaultsMenu)
     ,EXIT("< Back")
);

/// Main Menu

MENU(mainMenu, "Home", doNothing, noEvent, wrapStyle
     ,SUBMENU(reservoirMenu)
     ,SUBMENU(phMonitorMenu)
     ,SUBMENU(tempMonitorMenu)
     ,SUBMENU(settingsMenu)
     );

MENU_OUTPUTS(out, MAX_DEPTH
,LIQUIDCRYSTAL_OUT(lcd,{0,0,16,2})
,NONE
);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);   //the navigation root object

void pollUi() {
  analogButtons.check();
  nav.poll();
}