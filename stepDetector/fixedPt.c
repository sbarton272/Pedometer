/**
 * Fixed point representation
 */

/*==================================
 * Includes
 *==================================*/

#include "fixedPt.h"

/*==================================
 * Public
 *==================================*/

fixed_t fixedMult(fixed_t a, fixed_t b) {
	return 0;
}

fixed_t fixedAdd(fixed_t a, fixed_t b) {
	return 0;
}

fixed_t fixedPtFromInt(int32_t decimal, int16_t offset) {
  return (fixed_t) ((decimal << FIXED_PT_LOC) / offset);
}

/*==================================
 * Private
 *==================================*/

