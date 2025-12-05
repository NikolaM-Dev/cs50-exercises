#include <stdbool.h>
#include <stdint.h>

#define FAT_BLOCK_SIZE 512
#define IMAGE_FILENAME_SIZE 8

typedef uint8_t BYTE;

// `is_jpeg_signature` verify if the buffer start with a JPEG signature
bool is_jpeg_signature(BYTE buffer[FAT_BLOCK_SIZE]);
