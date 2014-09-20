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
	
  // Cast up to larger size as mult may overflow before normalized
  fixed_long_t prod = ((fixed_long_t)a) * ((fixed_long_t)b);
  
  // Casting back will truncate so data loss is possible 
  return (fixed_t)((a * b) >> FIXED_PT_LOC);
}

fixed_t fixedAdd(fixed_t a, fixed_t b) {
	return a + b;
}

fixed_t fixedPtFromInt(int32_t decimal, int16_t offset) {
  return (fixed_t) ((decimal << FIXED_PT_LOC) / offset);
}

                         