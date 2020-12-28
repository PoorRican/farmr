//
// Created by Josue Figueroa on 12/25/20.
//

#include "ui.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

AnalogButtons analogButtons(A0, INPUT, 2, 20);
Button b1 = Button(0, &bSel);               // right
Button b2 = Button(256, &bUp);              // down
Button b3 = Button(98, &bDwn);              // up
Button b4 = Button(410, &bEsc);             // left
//Button b5 = Button(640, &b5Click);        // select

chainStream<0> in(NULL);


// TODO: initialize default values for fields

// Reservoir Pumping
bool pumpingOn = false;
unsigned int threshold = 25;
uint16_t reservoirDuration = 5;
uint16_t reservoirInterval = 4;

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
float idealPh = 7.5;
bool phMonitoring = false;
uint16_t phPollInterval = 15;
uint16_t phPumpDuration = 2;

TOGGLE(phMonitoring, togglePhMonitor, "Mon.: ", doExit, enterEvent, noStyle
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

MENU(mainMenu, "Main Menu", doNothing, noEvent, wrapStyle
     ,SUBMENU(reservoirMenu)
     ,SUBMENU(phMonitorMenu)
     );

#define MAX_DEPTH 3

MENU_OUTPUTS(out, MAX_DEPTH
,LIQUIDCRYSTAL_OUT(lcd,{0,0,16,2})
,NONE
);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);   //the navigation root object

void pollUi() {
  nav.poll();
  analogButtons.check();
}

// Reservoir Callbacks
void turnOnReservoirPump() {
  reservoir_pump.startPumpOnTimer();
}
void turnOffReservoirPump() {
  reservoir_pump.startPumpOnTimer();
}

result setReservoirThreshold(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Threshold set to ");
  Serial.println(threshold);
#endif
  reservoir_pump.setThreshold(threshold);
  return proceed;
}

result setReservoirDuration(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir pump duration set to ");
  Serial.println(reservoirDuration);
#endif
  reservoir_pump.setDuration(reservoirDuration);
  return proceed;
}

result setReservoirInterval(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir pump interval set to ");
  Serial.println(reservoirInterval);
#endif
  reservoir_pump.setInterval(reservoirInterval);
  return proceed;
}


// pH Monitor Callbacks
result setIdealPh(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Ideal pH set to ");
  Serial.println(idealPh);
#endif
  ph_monitor.setIdeal(idealPh);
  return proceed;
}

result setPhPollInterval(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("pH Poll Interval set to ");
  Serial.println(phPollInterval);
#endif
  ph_monitor.setInterval(phPollInterval);
  return proceed;
}

result setPhPumpDuration(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("pH Pump Duration set to ");
  Serial.println(phPumpDuration);
#endif
  ph_monitor.setDuration(phPumpDuration);
  return proceed;
}

void turnOnPhMonitor() {
  ph_monitor.startPolling();
}
void turnOffPhMonitor() {
  ph_monitor.stopPolling();
}


void bSel(){
  nav.doNav(enterCmd);
}

void bDwn(){
  nav.doNav(downCmd);
}

void bUp(){
  nav.doNav(upCmd);
}

void bEsc(){
  nav.doNav(escCmd);
}
