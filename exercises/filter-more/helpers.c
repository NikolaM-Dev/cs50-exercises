#include <math.h>
#include <string.h>

#include "helpers.h"

int GX[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1},
};

int GY[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1},
};

/**
 * `calc_average_grayscale` returns the rounded value of the average or red,
 * green, and blue in the pixel
 */
int calc_average_grayscale(RGBTRIPLE pixel) {
  int sum = pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue;
  return round((float)sum / 3);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int average = calc_average_grayscale(image[i][j]);
      image[i][j].rgbtRed = average;
      image[i][j].rgbtGreen = average;
      image[i][j].rgbtBlue = average;
    }
  }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width / 2; j++) {
      RGBTRIPLE tmp = image[i][width - j - 1];
      image[i][width - j - 1] = image[i][j];
      image[i][j] = tmp;
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
          if (h >= 0 && h < height && k >= 0 && k < width) {
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

// `cap_channel` returns a valid RGB int in the range 0 to 255
int cap_channel(int channel) {
  if (channel > 255) {
    return 255;
  } else if (channel < 0) {
    return 0;
  } else {
    return channel;
  }
}

// `calc_channel_edge` returns the compute value for the edge filter
int calc_channel_edge(int gx, int gy) {
  return cap_channel(round(sqrt(pow(gx, 2) + pow(gy, 2))));
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE original[height][width];
  memcpy(original, image, sizeof original);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int gx_red = 0, gx_green = 0, gx_blue = 0;
      int gy_red = 0, gy_green = 0, gy_blue = 0;

      for (int di = 0; di < 3; di++) {
        for (int dj = 0; dj < 3; dj++) {
          int h = i - 1 + di;
          int w = j - 1 + dj;

          if (h >= 0 && h < height && w >= 0 && w < width) {
            gx_red += GX[di][dj] * original[h][w].rgbtRed;
            gy_red += GY[di][dj] * original[h][w].rgbtRed;
            gx_green += GX[di][dj] * original[h][w].rgbtGreen;
            gy_green += GY[di][dj] * original[h][w].rgbtGreen;
            gx_blue += GX[di][dj] * original[h][w].rgbtBlue;
            gy_blue += GY[di][dj] * original[h][w].rgbtBlue;
          }
        }
      }

      image[i][j].rgbtRed = calc_channel_edge(gx_red, gy_red);
      image[i][j].rgbtGreen = calc_channel_edge(gx_green, gy_green);
      image[i][j].rgbtBlue = calc_channel_edge(gx_blue, gy_blue);
    }
  }
}
