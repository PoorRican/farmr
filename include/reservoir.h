//
// Created by Josue Figueroa on 12/11/20.
//

#ifndef FARMR_RESERVOIR_H
#define FARMR_RESERVOIR_H

#include <Ultrasonic.h>

/**
 * This uses the Ultrasonic library to check main reservoir depth.
 * TODO: it would be cool to use an asynchronous library.
 */
class Reservoir {
public:
  // Constructors
  Reservoir(Ultrasonic*);
  Reservoir(const Reservoir&);
  const Reservoir& operator=(const Reservoir&);

  // Destructor
  ~Reservoir();

  /**
   * Checks reservoir to see if water level is above threshold.
   * @returns true if water is above threshold
   */
  bool check_reservoir();
  // =====================
  // Calibration Functions
  // =====================
  /**
   * Used to calibrate sensor when reservoir is full.
   */
  void calibrateFull();
  /**
   * Calibrate reservoir empty
   */
  void calibrateEmpty();
private:
  Ultrasonic* sensor;
  /**
   * Pump should stop when reservoir reaches 25%
   */
  const float reservoir_thresh = .25;

  // Distances (in CM)
  unsigned int fullDepth = 0;
  unsigned int emptyDepth = 0;
};

#endif //FARMR_RESERVOIR_H
