/**
 * Main file to load data and convert it to
 *  the correct type for the algorithm
 */

/*==================================
 * Includes
 *==================================*/

#include "pedometer.h"

/*==================================
 * Public
 *==================================*/

// Note this function is note super safe as the user specifies
//  the data size, but I am not worring about safety for this one
//  as this is a simple demo.
int main(int argc, char *argv[]) {

	// Check input, want data filename and num sampels
	if (argc != 2) {
		printf("Please provide data file name\npedometer <filename> <nSamples>\n");
		exit(EXIT_FAILURE);
	}

	// Read in and parse data
	char* filename = argv[1];
	FILE* dataFp = fopen(filename, "r");

	// Error check
	if (file == NULL) {
		printf("Please provide valid data file name\n");
		exit(EXIT_FAILURE);
	}

	// Create data object to store data
	uint16_t nSamples = atoi(argv[2]);
	// Malloc may not be a good idea for embedded but neccessary since don't know
	//  nSamples until runtime.
	pedometer_data_t[nSamples] data = malloc(nSamples*sizeof(pedometer_data_t));

	// Parse out data into data object

	// Close file
	fclose(dataFp);

	// Clean-up mallocs
	free(data);

}

/*==================================
 * Private
 *==================================*/

void parseXyzData(FILE* fp, pedometer_data_t[] data, uint16_t nSamples) {

	char[READ_BUFF_SIZE] buff;
	char* accelData;

	// Read line by line and parse x, y, z values
	// Assume there is no first line header
	// NOTE I removed the header in my data file
	for (int i = 0; i < nSamples; i++) {

		// Read line
		if ( fgets(buff, sizeof buff, fp) == NULL) {
			// Hit end of file or error
			break;
		}

		// Split into tokens for x,y,z
		for (int j = 0; j < NUM_ACCEL_DATA; j++) {
		accelData = strtok(buff,SPLIT_TOK);
		printf("%s\n", accelData);

		// Convert double in string format to fixed point
		// TODO read 
		}

	}

	// TODO catch errors
}

#endif // _PEDOMETER_H