# TODO:

## Functionality

### High Pri
- Logging (via Eth/SD Card):
  - Temp
  - pH
  - EC
  - Reservoir levels
  - NH3/Nitrate/Nitrite
- Filtering functionality:
  - backup
  - logging
  - sensing

### Low Pri
- Implement `Reservoir` calibration via UI
- Python setup/implementation script
- Python client
- Show build flags in settings menu
- Failsafes:
  - backup reservoir pump/flow sensor
  - backup filter/valve
- Communication with other systems:
  - `testr` for -NO2/-NO3/-NH3 readings
  - `reactr` for managing bioreactor
- Change types used in `Settings::getAddresses`


## Test:
- Test `setDuration` updates timer correctly changes duration
- Pump/cycle timing
- pumpMode
- `MonitorTemp::setSetpoint`