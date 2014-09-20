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

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#include "fixedPt.h"

/*==================================
 * Macros
 *==================================*/

/*
 * Calculated from matlab.
 */ 
#define BPF_LEN 33

/*
 * This constant is calculated based on the bandpass filter.
 * The bandpass filter allows 3Hz maximum so peaks are no closer
 * than .33 sec. Since Fs = 20Hz this is 6.67 samples. As long 
 * as I search for a max/min in a window less than 6.67 I am 
 * guaranteed not to find 2 of the same extreema.
 */
#define STEP_WINDOW_SIZE 5

/*
 * This value (0.3) was calculated in matlab. It was the best seperator
 * between step min-max differences and min-max pairs not due to steps.
 */
#define MIN_MAX_THRESHOLD 614

/*==================================
 * Constants
 *==================================*/

/*
 * Coefficients calculated in matlab for an FIR filter with
 *  a passband between 1Hz and 3Hz. Steps are expected to fall
 *  at around 1.5Hz. People walk about 1.3 m/s or .67/.76 m step 
 *  size (women/men). This means that steps occur at frequencies
 *  at about 1.9Hz (women) or 1.7Hz (men).
 */
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
 * Take the sum of the squares of the x,y,z components.
 * This is the twoNorm^2
 */
static fixed_t sumSqrs(pedometer_data_t xyz);

/*
 * Apply the predetermined bandpass filter to the data.
 * NOTE This destructively modifies data.
 */
static void bandpassFilter(fixed_t data[], uint16_t dataLen);

/*
 * Iterates through filtered data and finds min-max pairs (aka a minimum
 *  followed by a maximum). If these extrema have a large enough difference
 *  this is classified as a step.
 */
static uint16_t countSteps(fixed_t data[], uint16_t dataLen);

/*
 * Take min of given numbers
 */
static fixed_t minimum(fixed_t nums[], uint16_t len);

/*
 * Take max of given numbers
 */
static fixed_t maximum(fixed_t nums[], uint16_t len);


#endif // _STEP_DETECTOR_H