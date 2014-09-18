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
	return 0;
}

/*==================================
 * Private
 *==================================*/

fixed_t sumSqrs(pedometer_data_t xyz) {
	return 0;
}

fixed_t* bandpassFilter(fixed_t data[], uint16_t dataLen) {
	return NULL;
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