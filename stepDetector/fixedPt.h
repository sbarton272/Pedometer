/**
 * Fixed point representation
 */

#ifndef _FIXED_PT_H
#define _FIXED_PT_H

/*==================================
 * Includes
 *==================================*/

#include <stdio.h>
#include <inttypes.h>

/*==================================
 * Macros
 *==================================*/

/* The fixed point location was determined in fixedPt.py
 *  to meet the contraints of the data and the filter coef.
 */
#define FIXED_PT_LOC 11

typedef int16_t fixed_t;

/*==================================
 * Structs
 *==================================*/

/*==================================
 * Public
 *==================================*/

fixed_t fixedMult(fixed_t a, fixed_t b);

fixed_t fixedAdd(fixed_t a, fixed_t b);

/*==================================
 * Private
 *==================================*/

#endif // _FIXED_PT_H