# TODO's

- [x] Read requirements
- [x] See CS50 video
- [x] Review source code
- [x] Implement grayscale filter
  - [x] Make `calc_average_grayscale` function
  - [x] Use the function `calc_average_grayscale` in every pixel.
- [x] Implement reflect algorithm
- [x] Implement blur algorithm
  - [x] See video
  - [x] Implement the algorithm
  - [x] See if it's right
- [x] Implement edges algorithm
  - [x] See video
  - [x] Why Charlie used `di` and `dj` .
  - [x] Create `Gx` and `Gy` matrices.
  - [x] Plan using GoodNotes
  - [x] Algorithm
    - [x] Compute `Gx` and `Gy` for every channel in the pixel.
    - [x] Pixels out of the boundaries will treats as 0.
    - [x] The new value of each channel is `sqrt(Gx^2 + Gy^2)`
      - [x] Cap to maximum and minimum channel values `0-255`
  - [x] Check the code in terms of High Quality Code using `opencode`

# 🧬 References

- [Filter - CS50](https://cs50.harvard.edu/extension/2025/fall/psets/4/filter/more/)
