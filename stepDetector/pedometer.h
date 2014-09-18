/**
 * Main file to load data and convert it to
 *  the correct type for the algorithm
 */


#ifndef _PEDOMETER_H
#define _PEDOMETER_H

/*==================================
 * Includes
 *==================================*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

#include "stepDetector.h"
#include "fixedPt.h"

/*==================================
 * Macros and Consts
 *==================================*/

#define CHR_TO_INT(c) (c - '0')

const char SPLIT_TOK[2] = ",";

#define DATA_BUFF_SIZE 64
#define NUM_ACCEL_DATA 3

#define INPUT_SCALAR 10000 // 10^4
#define DECIMAL_PRECISION 4

/*==================================
 * Structs
 *==================================*/

/*==================================
 * Public
 *==================================*/

/*
 * Expects filename via command line
 * Parses file and converts data to pedometer_data_t
 */
int main(int argc, char *argv[]);

/*==================================
 * Private
 *==================================*/

/*
 * Extract all of the values in the file and store in data
 */
static void parseXyzData(FILE* fp, pedometer_data_t data[], uint16_t nSamples);

/*
 * Given a float in string format, convert to fixed point type
 * NOTE modifies tok pointer and truncates instead of rounding once the precision
 *  point is reached.
 */
static fixed_t parseValue(char* tok);


#endif // _PEDOMETER_H