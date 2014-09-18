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

/*
 * Convert the decimal number which has the given decimal offset
 *  to a fixed pt definition.
 * Ex) 1.0034 comes into the system. It is parsed to 10034. Therefore
 *     decimal = 10034 and offset = 10000.
 */
fixed_t fixedPtFromInt(int32_t decimal, int16_t offset);

/*==================================
 * Private
 *==================================*/

#endif // _FIXED_PT_H