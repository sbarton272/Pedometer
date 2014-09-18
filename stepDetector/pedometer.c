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

/* Note this function is note super safe as the user specifies
 *  the data size, but I am not worring about safety for this one
 *  as this is a simple demo.
 */
int main(int argc, char *argv[]) {

  // Check input, want data filename and num sampels
  if (argc != 3) {
    printf("Please provide data file name\npedometer <filename> <nSamples>\n");
    exit(EXIT_FAILURE);
  }

  // Read in and parse data
  char* filename = argv[1];
  FILE* dataFp = fopen(filename, "r");

  // Error check
  if (dataFp == NULL) {
    printf("Please provide valid data file name\n");
    exit(EXIT_FAILURE);
  }

  // Create data object to store data
  uint16_t nSamples = atoi(argv[2]);
  // Malloc may not be a good idea for embedded but neccessary since don't know
  //  nSamples until runtime.
  pedometer_data_t* data = malloc(nSamples*sizeof(pedometer_data_t));

  // Parse out data into data object
  parseXyzData(dataFp, data, nSamples);

  // Close file
  fclose(dataFp);

  // Clean-up mallocs
  free(data);

}

/*==================================
 * Private
 *==================================*/

void parseXyzData(FILE* fp, pedometer_data_t data[], uint16_t nSamples) {

  char x[64];
  char y[DATA_BUFF_SIZE];
  char z[DATA_BUFF_SIZE];
  char* buf;
  char* tok;

  // Read line by line and parse x, y, z values
  // Assume there is no first line header
  // NOTE I removed the header in my data file

  int linesRead = 0;
  while ((fscanf(fp, "%s", x) == 1) &&
         (linesRead < nSamples)) {
    buf = x;
    while ((tok = strsep(&buf, ",")) != NULL) {
      printf("%d:%s\n", linesRead, tok);
    }
    linesRead++;
  }

  // if (feof(fp)) {
  //   // Hit end of file
  //   return;
  // } else {
  //   // Error
  //   printf("Error parsing data\n");
  // }
}

