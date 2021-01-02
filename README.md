# Build

## Ideas

### pH Buffer Solutions:

Instead of using peristaltic pumps to pump buffer solutoin, 500mL syringes can be used,
with a stepper motor driving actuation of the plunger.

### Outlet Port for fraction collector/spectrophotometry/reagent testing

Using [soft/flexible tubing](https://www.mcmaster.com/tubing/flexibility~flexible/soft-tubing-for-air-and-water/soft-plastic-tubing-for-air-and-water/), a solenoid can be used to shut inlets as a cost-effective way to
create an electronically actuated valve with a small inner diameter.

## Parts
- Temperature Control:
    * Temperature Sensor: [Waterproof 1-Wire DS18B20](https://www.adafruit.com/product/381) (Uses OneWire library)
    * Heater Element: [Electric Heating Pad - 14cm x 5cm](https://www.adafruit.com/product/4308) (12V)
    * Cooling Element: [Peltier Thermo-Electric Cooler Module+Heatsink Assembly](https://www.adafruit.com/product/1335) (12V)
    * Idea:
        - Designed like a water-cooled reflux tube
        - Separate reservoir filled with mineral water, with both heating and cooling elements around the exterior.
        - A tube bended to be a coil contains liquid to be cooled or heated.
        - Recirculating pump is used to force liquid through tank.
    * Maybe a solar water-heater or ground cooling can be used in-lieu of thermoelectric heaters
- [12V Peristaltic Pump](https://www.adafruit.com/product/1150)
- [12" eTape Liquid Level Sensor (w/ Teflon Jacket)](https://www.adafruit.com/product/1786)
- Tubing:
    * 2mm:
      - [Smooth-Flow Soft Plastic Tubing for Food and Beverage](https://www.mcmaster.com/tubing/id~2mm/food-beverage-and-dairy-tubing/)
    
### Electrodes:

* A [custom amplifier circuit](https://electronics.stackexchange.com/questions/289548/building-a-ph-meter-circuit-is-it-feasible) will be necessary for probes
  
* I do not know if these electrodes will work properly for continuous use 
  
* Nitrate:
    * [ThermoScientific Orion Nitrate Sensor](https://www.thermofisher.com/order/catalog/product/970701#/970701) ($1,100}
    * [Manual](https://www.thermofisher.com/document-connect/document-connect.html?url=https%3A%2F%2Fassets.thermofisher.com%2FTFS-Assets%2FLSG%2Fmanuals%2FD15888~.pdf&title=Tml0cmF0ZSBJb24gU2VsZWN0aXZlIEVsZWN0cm9kZQ==)
    
* Ammonia:
    * [ThermoScientific Orion Ammonia Sensor](https://www.thermofisher.com/order/catalog/product/9512BNWP#/9512BNWP) ($790}
    * [Manual](https://www.thermofisher.com/document-connect/document-connect.html?url=https%3A%2F%2Fassets.thermofisher.com%2FTFS-Assets%2FLSG%2Fmanuals%2FD01250~.pdf&title=U3RhbmRhcmQgQW1tb25pYSBJb24gU2VsZWN0aXZlIEVsZWN0cm9kZSAtIFVzZXIgR3VpZGU=)

## Project References
- [Chilled Drinkibot](https://learn.adafruit.com/chilled-drinkibot)
- [reef-pi](https://learn.adafruit.com/search?q=reef-pi)