#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // RGBTRIPLE pixel = image[0][1];
    // printf("Before: %x %x %x\n", pixel.rgbtBlue, pixel.rgbtGreen, pixel.rgbtRed);
    // int avg = (int) round(pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed / 3.0);
    // printf("%i\n", avg);
    // pixel.rgbtBlue = avg;
    // pixel.rgbtGreen = avg;
    // pixel.rgbtRed = avg;
    // printf("After: %x %x %x\n", pixel.rgbtBlue, pixel.rgbtGreen, pixel.rgbtRed);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("%x %x %x\n", image[i][j].rgbtBlue, image[i][j].rgbtGreen,
            //  image[i][j].rgbtRed);

            // Finding the average of each pixel to find the grayscale shade
            int avg = (int) round(
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Using these formulas for each color to find the sepia shade
            int sepiaRed = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                       .189 * image[i][j].rgbtBlue);
            int sepiaGreen = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                         .168 * image[i][j].rgbtBlue);
            int sepiaBlue = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                        .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfOfWidth = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfOfWidth; j++)
        {
            // swapping each pixel from the start and at the end
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;

            int jReflect = width - (j + 1);

            image[i][j].rgbtRed = image[i][jReflect].rgbtRed;
            image[i][j].rgbtGreen = image[i][jReflect].rgbtGreen;
            image[i][j].rgbtBlue = image[i][jReflect].rgbtBlue;

            image[i][width - (j + 1)].rgbtRed = tempRed;
            image[i][width - (j + 1)].rgbtGreen = tempGreen;
            image[i][width - (j + 1)].rgbtBlue = tempBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // copying each pixel to copy[i][j] to maintain the original image version
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 1;

            int sumRed = copy[i][j].rgbtRed;
            int sumGreen = copy[i][j].rgbtGreen;
            int sumBlue = copy[i][j].rgbtBlue;

            // Visiting all possible neighbouring values and keeping track of count variable
            if ((j - 1) >= 0 && (j - 1) < width)
            {
                sumRed += copy[i][j - 1].rgbtRed;
                sumGreen += copy[i][j - 1].rgbtGreen;
                sumBlue += copy[i][j - 1].rgbtBlue;
                count++;
            }
            if ((j + 1) >= 0 && (j + 1) < width)
            {
                sumRed += copy[i][j + 1].rgbtRed;
                sumGreen += copy[i][j + 1].rgbtGreen;
                sumBlue += copy[i][j + 1].rgbtBlue;
                count++;
            }

            if ((i - 1) >= 0 && (i - 1) < height)
            {
                sumRed += copy[i - 1][j].rgbtRed;
                sumGreen += copy[i - 1][j].rgbtGreen;
                sumBlue += copy[i - 1][j].rgbtBlue;
                count++;

                if ((j - 1) >= 0 && (j - 1) < width)
                {
                    sumRed += copy[i - 1][j - 1].rgbtRed;
                    sumGreen += copy[i - 1][j - 1].rgbtGreen;
                    sumBlue += copy[i - 1][j - 1].rgbtBlue;
                    count++;
                }
                if ((j + 1) >= 0 && (j + 1) < width)
                {
                    sumRed += copy[i - 1][j + 1].rgbtRed;
                    sumGreen += copy[i - 1][j + 1].rgbtGreen;
                    sumBlue += copy[i - 1][j + 1].rgbtBlue;
                    count++;
                }

            }

            if ((i + 1) >= 0 && (i + 1) < height)
            {
                sumRed += copy[i + 1][j].rgbtRed;
                sumGreen += copy[i + 1][j].rgbtGreen;
                sumBlue += copy[i + 1][j].rgbtBlue;
                count++;

                if ((j - 1) >= 0 && (j - 1) < width)
                {
                    sumRed += copy[i + 1][j - 1].rgbtRed;
                    sumGreen += copy[i + 1][j - 1].rgbtGreen;
                    sumBlue += copy[i + 1][j - 1].rgbtBlue;
                    count++;
                }
                if ((j + 1) >= 0 && (j + 1) < width)
                {
                    sumRed += copy[i + 1][j + 1].rgbtRed;
                    sumGreen += copy[i + 1][j + 1].rgbtGreen;
                    sumBlue += copy[i + 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            // Finding average for all three colors to find the blur shade
            int avgRed = (int) round(sumRed / (count * 1.0));
            int avgGreen = (int) round(sumGreen / (count * 1.0));
            int avgBlue = (int) round(sumBlue / (count * 1.0));

            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtBlue = avgBlue;
        }
    }

    return;
}
