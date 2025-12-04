#include <math.h>
#include <string.h>

#include "helpers.h"

/**
 * `calc_average` returns the average of the RGBTRIPLE values rounded to the
 * nearest integer
 */
int calc_average(RGBTRIPLE pixel) {
  float result = (float)(pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3;

  return round(result);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int average = calc_average(image[i][j]);

      image[i][j].rgbtRed = average;
      image[i][j].rgbtGreen = average;
      image[i][j].rgbtBlue = average;
    }
  }
}

// `validate_rbg_range` returns a valid RGB int in the range 0 to 255
int validate_rbg_range(int rgb) {
  if (rgb > 255) {
    return 255;
  } else if (rgb < 0) {
    return 0;
  } else {
    return rgb;
  }
}

// `calc_sepia_red` returns the sepia red version of the pixel
int calc_sepia_red(RGBTRIPLE pixel) {
  float result =
      pixel.rgbtRed * .393 + pixel.rgbtGreen * .769 + pixel.rgbtBlue * .189;

  return validate_rbg_range(round(result));
}

// `calc_sepia_green` returns the sepia green version of the pixel
int calc_sepia_green(RGBTRIPLE pixel) {
  float result =
      pixel.rgbtRed * .349 + pixel.rgbtGreen * .686 + pixel.rgbtBlue * .168;

  return validate_rbg_range(round(result));
}

// `calc_sepia_blue` returns the sepia blue version of the pixel
int calc_sepia_blue(RGBTRIPLE pixel) {
  float result =
      pixel.rgbtRed * .272 + pixel.rgbtGreen * .534 + pixel.rgbtBlue * .131;

  return validate_rbg_range(round(result));
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE pixel = image[i][j];

      image[i][j].rgbtRed = calc_sepia_red(pixel);
      image[i][j].rgbtGreen = calc_sepia_green(pixel);
      image[i][j].rgbtBlue = calc_sepia_blue(pixel);
    }
  }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0, half = width / 2; j < half; j++) {
      RGBTRIPLE tmp = image[i][j];
      image[i][j] = image[i][width - j - 1];
      image[i][width - j - 1] = tmp;
    }
  }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE original[height][width];
  memcpy(original, image, sizeof original);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int red_sum = 0, green_sum = 0, blue_sum = 0;
      int count = 0;

      for (int h = i - 1, row_limit = h + 3; h < row_limit; h++) {
        for (int k = j - 1, col_limit = k + 3; k < col_limit; k++) {
          if (h >= 0 && k >= 0 && h < height && k < width) {
            red_sum += original[h][k].rgbtRed;
            green_sum += original[h][k].rgbtGreen;
            blue_sum += original[h][k].rgbtBlue;
            count++;
          }
        }
      }

      image[i][j].rgbtRed = round((float)red_sum / count);
      image[i][j].rgbtGreen = round((float)green_sum / count);
      image[i][j].rgbtBlue = round((float)blue_sum / count);
    }
  }
}
