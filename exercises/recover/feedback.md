# `recover.h`

```c
#ifndef RECOVER_H
#define RECOVER_H

#include <stdbool.h>
#include <stdint.h>

#define FAT_BLOCK_SIZE 512
#define IMAGE_FILENAME_MAX 16

typedef uint8_t BYTE;

// Returns true if buffer begins with a valid JPEG header.
// Requires buffer to contain at least 4 bytes.
bool is_jpeg_signature(const BYTE buffer[static 4]);

#endif
```

# `recover.c`

```c
FILE *memory_card = fopen(filename, "rb");
if (!memory_card) {
    fprintf(stderr, "Error: cannot open %s\n", filename);
    return EXIT_FAILURE;
}

BYTE buffer[FAT_BLOCK_SIZE];
FILE *output = NULL;
int image_count = 0;

while (true) {
    size_t bytes_read = fread(buffer, 1, FAT_BLOCK_SIZE, memory_card);
    if (bytes_read == 0) break;

    if (is_jpeg_signature(buffer)) {
        if (output) fclose(output);

        char outname[IMAGE_FILENAME_MAX];
        snprintf(outname, sizeof(outname), "%03d.jpg", image_count++);

        output = fopen(outname, "wb");
        if (!output) {
            fprintf(stderr, "Error: cannot create %s\n", outname);
            fclose(memory_card);
            return EXIT_FAILURE;
        }
    }

    if (output) fwrite(buffer, 1, bytes_read, output);
}

if (output) fclose(output);
fclose(memory_card);
```

```c
bool is_jpeg_signature(const BYTE buffer[static 4]) {
    return buffer[0] == 0xFF &&
           buffer[1] == 0xD8 &&
           buffer[2] == 0xFF &&
           (buffer[3] & 0xF0) == 0xE0;
}
```
