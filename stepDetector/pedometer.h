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

#include "stepDetector.h"
#include "fixedPt.h"

/*==================================
 * Macros and Consts
 *==================================*/

const char SPLIT_TOK[2] = ",";

#define DATA_BUFF_SIZE 64
#define NUM_ACCEL_DATA 3
#define INPUT_SCALAR 10000

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

static void parseXyzData(FILE* fp, pedometer_data_t data[], uint16_t nSamples);

#endif // _PEDOMETER_H