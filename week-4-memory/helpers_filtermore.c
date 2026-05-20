#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            int gxR = 0;
            int gyR = 0;

            int gxG = 0;
            int gyG = 0;

            int gxB = 0;
            int gyB = 0;

            if ((i - 1) >= 0 && (i - 1) < height)
            {
                if ((j - 1) >= 0 && (j - 1) < width)
                {
                    int applyKernelX = -1;
                    int applyKernelY = -1;

                    gxR += (applyKernelX * copy[i - 1][j - 1].rgbtRed);
                    gyR += (applyKernelY * copy[i - 1][j - 1].rgbtRed);

                    gxG += (applyKernelX * copy[i - 1][j - 1].rgbtGreen);
                    gyG += (applyKernelY * copy[i - 1][j - 1].rgbtGreen);

                    gxB += (applyKernelX * copy[i - 1][j - 1].rgbtBlue);
                    gyB += (applyKernelY * copy[i - 1][j - 1].rgbtBlue);
                }
                if (j >= 0 && j < width)
                {
                    int applyKernelX = 0;
                    int applyKernelY = -2;

                    gxR += (applyKernelX * copy[i - 1][j].rgbtRed);
                    gyR += (applyKernelY * copy[i - 1][j].rgbtRed);

                    gxG += (applyKernelX * copy[i - 1][j].rgbtGreen);
                    gyG += (applyKernelY * copy[i - 1][j].rgbtGreen);

                    gxB += (applyKernelX * copy[i - 1][j].rgbtBlue);
                    gyB += (applyKernelY * copy[i - 1][j].rgbtBlue);
                }
                if ((j + 1) >= 0 && (j + 1) < width)
                {
                    int applyKernelX = 1;
                    int applyKernelY = -1;

                    gxR += (applyKernelX * copy[i - 1][j + 1].rgbtRed);
                    gyR += (applyKernelY * copy[i - 1][j + 1].rgbtRed);

                    gxG += (applyKernelX * copy[i - 1][j + 1].rgbtGreen);
                    gyG += (applyKernelY * copy[i - 1][j + 1].rgbtGreen);

                    gxB += (applyKernelX * copy[i - 1][j + 1].rgbtBlue);
                    gyB += (applyKernelY * copy[i - 1][j + 1].rgbtBlue);
                }
            }

            if ((j - 1) >= 0 && (j - 1) < width)
            {
                int applyKernelX = -2;
                int applyKernelY = 0;

                gxR += (applyKernelX * copy[i][j - 1].rgbtRed);
                gyR += (applyKernelY * copy[i][j - 1].rgbtRed);

                gxG += (applyKernelX * copy[i][j - 1].rgbtGreen);
                gyG += (applyKernelY * copy[i][j - 1].rgbtGreen);

                gxB += (applyKernelX * copy[i][j - 1].rgbtBlue);
                gyB += (applyKernelY * copy[i][j - 1].rgbtBlue);
            }
            if ((j + 1) >= 0 && (j + 1) < width)
            {
                int applyKernelX = 2;
                int applyKernelY = 0;

                gxR += (applyKernelX * copy[i][j + 1].rgbtRed);
                gyR += (applyKernelY * copy[i][j + 1].rgbtRed);

                gxG += (applyKernelX * copy[i][j + 1].rgbtGreen);
                gyG += (applyKernelY * copy[i][j + 1].rgbtGreen);

                gxB += (applyKernelX * copy[i][j + 1].rgbtBlue);
                gyB += (applyKernelY * copy[i][j + 1].rgbtBlue);
            }

            if ((i + 1) >= 0 && (i + 1) < height)
            {
                if ((j - 1) >= 0 && (j - 1) < width)
                {
                    int applyKernelX = -1;
                    int applyKernelY = 1;

                    gxR += (applyKernelX * copy[i + 1][j - 1].rgbtRed);
                    gyR += (applyKernelY * copy[i + 1][j - 1].rgbtRed);

                    gxG += (applyKernelX * copy[i + 1][j - 1].rgbtGreen);
                    gyG += (applyKernelY * copy[i + 1][j - 1].rgbtGreen);

                    gxB += (applyKernelX * copy[i + 1][j - 1].rgbtBlue);
                    gyB += (applyKernelY * copy[i + 1][j - 1].rgbtBlue);
                }
                if (j >= 0 && j < width)
                {
                    int applyKernelX = 0;
                    int applyKernelY = 2;

                    gxR += (applyKernelX * copy[i + 1][j].rgbtRed);
                    gyR += (applyKernelY * copy[i + 1][j].rgbtRed);

                    gxG += (applyKernelX * copy[i + 1][j].rgbtGreen);
                    gyG += (applyKernelY * copy[i + 1][j].rgbtGreen);

                    gxB += (applyKernelX * copy[i + 1][j].rgbtBlue);
                    gyB += (applyKernelY * copy[i + 1][j].rgbtBlue);
                }
                if ((j + 1) >= 0 && (j + 1) < width)
                {
                    int applyKernelX = 1;
                    int applyKernelY = 1;

                    gxR += (applyKernelX * copy[i + 1][j + 1].rgbtRed);
                    gyR += (applyKernelY * copy[i + 1][j + 1].rgbtRed);

                    gxG += (applyKernelX * copy[i + 1][j + 1].rgbtGreen);
                    gyG += (applyKernelY * copy[i + 1][j + 1].rgbtGreen);

                    gxB += (applyKernelX * copy[i + 1][j + 1].rgbtBlue);
                    gyB += (applyKernelY * copy[i + 1][j + 1].rgbtBlue);
                }
            }

            int sqR = (int) round(sqrt((gxR * gxR) + (gyR * gyR)));

            if (sqR > 255)
            {
                sqR = 255;
            }

            int sqG = (int) round(sqrt((gxG * gxG) + (gyG * gyG)));

            if (sqG > 255)
            {
                sqG = 255;
            }

            int sqB = (int) round(sqrt((gxB * gxB) + (gyB * gyB)));

            if (sqB > 255)
            {
                sqB = 255;
            }

            image[i][j].rgbtRed = sqR;
            image[i][j].rgbtGreen = sqG;
            image[i][j].rgbtBlue = sqB;
        }
    }

    return;
}
