#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>

int round_maximum(float rgb);
int begin(int ij, int unit);
int end(int begin, int unit, int height, int width, int which);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int r = image[j][i].rgbtRed;
            int g = image[j][i].rgbtGreen;
            int b = image[j][i].rgbtBlue;
            float num = (r + g + b) / 3.0;
            int average = round(num);
            image[j][i].rgbtRed = average;
            image[j][i].rgbtGreen = average;
            image[j][i].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int R = image[j][i].rgbtRed;
            int G = image[j][i].rgbtGreen;
            int B = image[j][i].rgbtBlue;
            float red = 0.393 * R + 0.769 * G + 0.189 * B;
            float green = 0.349 * R + 0.686 * G + 0.168 * B;
            float blue = 0.272 * R + 0.534 * G + 0.131 * B;
            int r = round_maximum(red);
            int g = round_maximum(green);
            int b = round_maximum(blue);
            image[j][i].rgbtRed = r;
            image[j][i].rgbtGreen = g;
            image[j][i].rgbtBlue = b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            RGBTRIPLE temporary;
            temporary = image[j][i];
            image[j][i] = image[j][width - 1 - i];
            image[j][width - 1 - i] = temporary;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; 
    int unit = 3; 
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int begin_i = begin(i, unit);
            int begin_j = begin(j, unit);
            int end_i = end(begin_i, unit, height, width, 2);
            int end_j = end(begin_j, unit, height, width, 1);
            int R = 0;
            int G = 0;
            int B = 0;
            for (int clm = begin_j; clm <= end_j; clm++)
            {
                for (int row = begin_i; row <= end_i; row++)
                {
                    R = R + image[clm][row].rgbtRed;
                    G = G + image[clm][row].rgbtGreen;
                    B = B + image[clm][row].rgbtBlue;
                }
            }
            int h = end_j - begin_j + 1; //求取色范围的边长
            int w = end_i - begin_i + 1;
            float averageR = (float) R / (h * w); 
            float averageG = (float) G / (h * w);
            float averageB = (float) B / (h * w);
            int r = round_maximum(averageR);
            int g = round_maximum(averageG);
            int b = round_maximum(averageB);
            copy[j][i].rgbtRed = r;
            copy[j][i].rgbtGreen = g;
            copy[j][i].rgbtBlue = b;
        }
    }
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            image[j][i].rgbtRed = copy[j][i].rgbtRed;
            image[j][i].rgbtGreen = copy[j][i].rgbtGreen;
            image[j][i].rgbtBlue = copy[j][i].rgbtBlue;
        }
    }
    return;
}

int round_maximum(float rgb)
{
    int n = round(rgb);
    if (n > 255)
    {
        n = 255;
    }
    return n;
}

int begin(int ij, int unit)
{
    int n = ij - (unit - 1) / 2;
    if (n < 0)
    {
        n = 0;
    }
    return n;
}

int end(int begin, int unit, int height, int width, int which)
{
    int n = begin + unit - 1;
    if (which == 1) 
    {
        if (n > height - 1)
        {
            n = height - 1;
        }
    }
    if (which == 2)
    {
        if (n > width - 1)
        {
            n = width - 1;
        }
    }
    return n;
}

