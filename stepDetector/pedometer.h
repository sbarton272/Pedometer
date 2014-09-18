/**
 * Main file to load data and convert it to
 *  the correct type for the algorithm
 */


#ifndef _PEDOMETER_H
#define _PEDOMETER_H

/*==================================
 * Includes
 *==================================*/

#include <stdio.h>
#include <inttypes.h>
#include "stepDetector.h"

/*==================================
 * Macros and Consts
 *==================================*/

const char* SPLIT_TOK = ",";
const char* SCAN_XYZ = "%";

#define READ_BUFF_SIZE 256;
#define NUM_ACCEL_DATA 3;

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

#endif // _PEDOMETER_H