#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "recover.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s [filename]\n", argv[0]);
    return EXIT_FAILURE;
  }
  char *filename = argv[1];

  FILE *memory_card = fopen(filename, "r");
  if (!memory_card) {
    printf("Could not open %s.\n", filename);
    return EXIT_FAILURE;
  }

  int image_count = 0;
  bool is_image_open = false;
  BYTE buffer[FAT_BLOCK_SIZE];
  FILE *image = NULL;
  while (fread(&buffer, sizeof(buffer), 1, memory_card) != 0) {
    if (is_jpeg_signature(buffer)) {
      if (is_image_open) {
        fclose(image);
      } else {
        is_image_open = true;
      }

      char img_filename[IMAGE_FILENAME_SIZE];
      sprintf(img_filename, "%03i.jpg", image_count);
      image = fopen(img_filename, "w");

      image_count++;
    }

    if (is_image_open) {
      fwrite(&buffer, sizeof buffer, 1, image);
    }
  }

  fclose(image);
  fclose(memory_card);

  return EXIT_SUCCESS;
}

bool is_jpeg_signature(BYTE buffer[FAT_BLOCK_SIZE]) {
  return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
         (buffer[3] & 0xf0) == 0xe0;
}
