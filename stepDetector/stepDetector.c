/**
 * stepDetector contains the step detection algorithm
 */

/*==================================
 * Includes
 *==================================*/

#include "stepDetector.h"

/*==================================
 * Constants
 *==================================*/

const fixed_t bandpassFilterCoef[BPF_LEN] = {5, 8, 8, 4, -4, -9, 0, 17, 16,
	-30, -121, -210, -220, -101, 116, 327, 415, 327, 116, -101, -220,
	-210, -121, -30, 16, 17, 0, -9, -4, 4, 8, 8, 5};


/*==================================
 * Public
 *==================================*/

uint16_t stepDetector(pedometer_data_t data[], uint16_t dataLen) {
	
  // Create new data object to contained normalized value
  fixed_t* normData = malloc(dataLen*sizeof(fixed_t));
  uint16_t i;
  for (i = 0; i < dataLen; i++) {

    // Norm is simply sum of squares
    normData[i] = sumSqrs(data[i]);
  }

  // Filter data with band pass filter
  bandpassFilter(normData, dataLen);

  // Count and return steps
  uint16_t nSteps = countSteps(normData, dataLen);

  // Clean-up memory
  free(normData);

  return nSteps;
}

/*==================================
 * Private
 *==================================*/

fixed_t sumSqrs(pedometer_data_t xyz) {
	return fixedMult(xyz.x, xyz.x) + fixedMult(xyz.y, xyz.y)
      + fixedMult(xyz.z, xyz.z);
}

void bandpassFilter(fixed_t data[], uint16_t dataLen) {
	
  // Init past value buffer to 0, this is effectively zero padding the data
  fixed_t pastBuf[BPF_LEN] = {0};

  // Keep track of buffer index which rotates through buffer
  uint16_t bufIndex = 0;

  // TODO make loop and multiply

  return;
}

uint16_t countSteps(fixed_t data[], uint16_t dataLen) {
	return 0;
}

fixed_t min(fixed_t nums[], uint16_t len) {
	return 0;
}

fixed_t max(fixed_t nums[], uint16_t len) {
	return 0;
}