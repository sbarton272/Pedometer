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

    // Norm is simply sum of squares, do not take sqrt for precision purposes
    normData[i] = sumSqrs(data[i]);
  }

  // Filter data with band pass filter, note modifies normData
  bandpassFilter(normData, dataLen);

  // TODO remove this test
  for (i = 0; i < dataLen; i++) {
    printf("%d\n", normData[i]);
  }

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

  // Iterate through all terms
  uint16_t i, j;
  for (i = 0; i < dataLen; i++) {

    // Place cur term in buf at most recent pos
    bufIndex = i % BPF_LEN;
    pastBuf[bufIndex] = data[i];

    // Perform filter convolution on current buffer
    fixed_t filteredValue = 0;
    uint16_t k;
    for (j = 0; j < BPF_LEN; j++) {

      /*
       * The bufIndex is the starting point. The pastBuf has
       * values added to the right, so iterate left from the starting
       * point to iterate through successively older values.
       * Add BPF_LEN so that this term doesn't go negative.
       */
      k = (BPF_LEN + bufIndex - j) % BPF_LEN;

      // BPF coefficients are ordered new to old
      filteredValue += fixedMult(pastBuf[k], bandpassFilterCoef[j]);
    }

    // Update data
    data[i] = filteredValue;
  }
}

uint16_t countSteps(fixed_t data[], uint16_t dataLen) {
	
  // Iterate through data over time looking for min followed by max
  // Look for max/min within a window
  uint16_t i;
  fixed_t min, max;
  bool priorPeak = false;
  uint16_t stepCount = 0;
  for (i = STEP_WINDOW_SIZE; i < (dataLen - STEP_WINDOW_SIZE); i++) {

    // Search for min in window before cur index and max in following window
    min = minimum(&data[i - STEP_WINDOW_SIZE], STEP_WINDOW_SIZE);
    max = maximum(&data[i], STEP_WINDOW_SIZE);

    // If difference in min followed by max peak is large enough this is a step
    if ((max - min) > MIN_MAX_THRESHOLD) {
      if (!priorPeak) {
        // TODO remove debug print
        printf("Peak at %d\n", i);
        stepCount++;
      }
      priorPeak = true;
    } else {
      priorPeak = false;
    }
  }
  return stepCount;
}

fixed_t minimum(fixed_t nums[], uint16_t len) {

  // Iter through to find min
  uint16_t i;
  fixed_t min = *nums;
  for (i = 0; i < len; i++) {
    if (nums[i] <= min) {
      min = nums[i];
    }
  }
  return min;
}

fixed_t maximum(fixed_t nums[], uint16_t len) {
 
  // Iter through to find max
  uint16_t i;
  fixed_t max = *nums;
  for (i = 0; i < len; i++) {
    if (nums[i] >= max) {
      max = nums[i];
    }
  }
  return max;
}