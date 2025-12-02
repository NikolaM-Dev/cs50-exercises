# Volume

## Notes

- WAV files has a 44-byte header
- After the header the samples take 2-byte (16-bit)
- To modify the volume we need to operate the bytes.
- Usage input.wav output.wav factor
- Use `uint8_t` to store the header.
- Use `int16_t` to store the samples. Since we already know that every sample
  uses 2-bytes (16-bit)

## Volume Algorithm

- [x] Read the header of the file from input.wav
- [x] Write the header of the file into output.wav
- [x] Review the hexadecimal codes from the file. Using `xxd my_file`
- [x] Repeat for each sample
  - [x] Read the sample from the input.wav
  - [x] Modify the sample based on the factor
  - [x] Write the new sample into the output.wav

# To Distill

- [ ] How to use `fread` and `fwrite`.
  - [ ] Describe that the reading is linear, so it doesn't rest the position
        when keep reading.
- [ ] How to use `xxd` to see binaries in hexadecimal.
- [ ] How to use the `%x` to print hexadecimal.
- [ ] How to cast in `clang`.
- [ ] How to handle `fread` errors in `clang`.
- [ ]
