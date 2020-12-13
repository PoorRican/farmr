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
   * @var depth (unsigned int) : debugging argument simulating returned sensor value
   * @return true if water is above threshold
   */
  bool above_threshold(unsigned int = 0);

  /**
   * Measures remaining fill volume of reservoir.
   * @var depth (unsigned int) : debugging argument simulating returned sensor value
   * @return Amount of liquid left in reservoir, as a fraction of 1.
   */
  double measure_volume(unsigned int = 0);
  // =====================
  // Calibration Functions
  // =====================

  /**
   * Used to calibrate sensor when reservoir is full.
   */
  void calibrateFull(unsigned int = 0);

  /**
   * Calibrate reservoir empty
   */
  void calibrateEmpty(unsigned int = 0);


  // Getter functions
  unsigned int getEmpty();
  unsigned int getFull();
  double getThreshold();

private:
  Ultrasonic* sensor;
  /**
   * WaterPump should stop when reservoir reaches 25%
   */
  const double reservoir_thresh = .25;

  // Distances (in CM)
  unsigned int fullDepth = 0;
  unsigned int emptyDepth = 0;
};

#endif //FARMR_RESERVOIR_H
