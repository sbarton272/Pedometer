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

  // Get number of steps
  uint16_t nSteps = stepDetector(data, nSamples);

  // Close file
  fclose(dataFp);

  // Clean-up mallocs
  free(data);

}

/*==================================
 * Private
 *==================================*/

void parseXyzData(FILE* fp, pedometer_data_t data[], uint16_t nSamples) {

  char buf[DATA_BUFF_SIZE];
  char* parse;
  char* tok;

  // Read line by line and parse x, y, z values
  // Assume there is no first line header
  // NOTE I removed the header in my data file
  int16_t linesRead = 0;
  while ((fscanf(fp, "%s", buf) == 1) &&
         (linesRead < nSamples)) {

    // Parse x,y,z
    // Extract double but convert to integer representation
    // TODO will crash if not 3 values
    parse = buf;
    tok = strsep(&parse, ",");
    data[linesRead].x = parseValue(tok);
    tok = strsep(&parse, ",");
    data[linesRead].y = parseValue(tok);
    tok = strsep(&parse, ",");
    data[linesRead].z = parseValue(tok);

    linesRead++;

    printf("Read(%d) %d, %d, %d\n", linesRead, data[linesRead].x, data[linesRead].y, data[linesRead].z);

  }

  if (feof(fp)) {

    // Hit end of file
    return;
  } else {
    
    // Error
    printf("Error parsing data\n");
  }
}

fixed_t parseValue(char* tok) {

  // Check if negative
  bool isNeg = false;
  char c = *tok; // Parsing char
  if (c == '-') {

    // If negative sign present move to look at next char
    isNeg = true;
    tok++;
  }

  // Form integer by extracting digits and mult cumulative
  //  sum by 10. Only extract a few places past decimal.
  bool isDecimalPassed = false;
  int16_t decimalPlacesPassed = 0;
  int32_t sum = 0;

  // Iterate until read given number of digits past decimal place
  while ( (decimalPlacesPassed <= DECIMAL_PRECISION) &&
          (c != '\n')) {
    
    // Get char and move to ptr to next char
    c = *tok;
    tok++;
  
    if (c == '.') {

      // If decimal place keep track that now parsing past the decimal
      isDecimalPassed = true;
    } else {

      // Add current number at the ones place
      sum = (10 * sum) + CHR_TO_INT(c);
    }

    // If past the decimal place keep track of how far
    if (isDecimalPassed) {
      decimalPlacesPassed++;
    }
  }

  // Convert to negative if necessary
  if (isNeg) {
    sum = -sum;
  }

  // Convert sum to fixed point
  return fixedPtFromInt(sum, INPUT_SCALAR);
}
