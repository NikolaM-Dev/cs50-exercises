// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[]) {
  // Check command-line arguments
  if (argc != 4) {
    printf("Usage: ./volume input.wav output.wav factor\n");
    return 1;
  }

  // Open files and determine scaling factor
  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    printf("Could not open file.\n");
    return EXIT_FAILURE;
  }

  FILE *output = fopen(argv[2], "w");
  if (output == NULL) {
    printf("Could not open file.\n");
    return EXIT_FAILURE;
  }

  float factor = atof(argv[3]);

  // Copy header from input file to output file
  uint8_t header[HEADER_SIZE];
  if (fread(header, HEADER_SIZE, 1, input) != 1) { // compared against the size
    fprintf(stderr, "Invalid input file.\n");
    return EXIT_FAILURE;
  }
  fwrite(header, HEADER_SIZE, 1, output);

  // Read samples from input file and write updated data to output file
  int16_t buffer;
  while (fread(&buffer, sizeof(buffer), 1, input) != 0) {
    // Modify the sample based on the factor
    buffer = (int16_t)(buffer * factor);
    fwrite(&buffer, sizeof(buffer), 1, output);
  }

  // Close files
  fclose(input);
  fclose(output);

  return EXIT_SUCCESS;
}
