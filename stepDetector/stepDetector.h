/**
 * stepDetector contains the step detection algorithm
 *
 * 1) The data is filtered using a bandpass filter with
 * 	  passband 1Hz to 3Hz. Steps are expected to have a 
 *    fundamental frequency of about 2Hz walking speed.
 * 2) The data is passed through a peak detector that looks
 *    for a minimum followed by a maximum value. If the 
 *
 * Notes
 * - This algorithm is designed for the specified sampling 
 *	 frequency
 * - The data is expected to be for walking
 */


#ifndef _STEP_DETECTOR_H
#define _STEP_DETECTOR_H

/*==================================
 * Includes
 *==================================*/

#include <stdio.h>
#include <inttypes.h>

#include "fixedPt.h"

/*==================================
 * Macros
 *==================================*/

#define BPF_LEN (33)

/*==================================
 * Constants
 *==================================*/

extern const fixed_t bandpassFilterCoef[BPF_LEN];

/*==================================
 * Structs
 *==================================*/

typedef struct {
  fixed_t x;
  fixed_t y;
  fixed_t z;
} pedometer_data_t;

/*==================================
 * Public
 *==================================*/

/*
 * Given data 
 */
uint16_t stepDetector(pedometer_data_t data[], uint16_t dataLen);

/*==================================
 * Private
 *==================================*/

/*
 * Take the sum of the squares of the x,y,z components
 */
static fixed_t sumSqrs(pedometer_data_t xyz);

/*
 * Apply the predetermined bandpass filter to the data
 */
static fixed_t* bandpassFilter(fixed_t data[], uint16_t dataLen);

/*
 * Iterates through filtered data and finds min-max pairs (aka a minimum
 *  followed by a maximum). If these extrema have a large enough difference
 *  this is classified as a step.
 */
static uint16_t countSteps(fixed_t data[], uint16_t dataLen);

static fixed_t min(fixed_t nums[], uint16_t len);

static fixed_t max(fixed_t nums[], uint16_t len);


#endif // _STEP_DETECTOR_H