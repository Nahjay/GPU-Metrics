
// Read the sysfs files and return the values

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "get_stats.h"

#define MAX_SIZE 1024

// Function to extract the frequency value of the GPU from the sysfs file
int get_gpu_freq()
{
    // Open the file
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int freq = 0;

    // Create a file pointer and open the file
    fp = fopen("/sys/devices/gpu.0/devfreq/57000000.gpu/cur_freq", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file\n");
        return -1;
    }

    // Read the file and extract the frequency value
    while ((read = getline(&line, &len, fp)) != -1)
    {
        freq = atoi(line);
    }

    // Close the file and free the memory
    fclose(fp);
    if (line)
        free(line);

    // Return the frequency value
    return freq;
}

// Function to extract the temperature value of the GPU from the sysfs file
int get_gpu_temp()
{
    // Open the file
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int temp = 0;

    // Create a file pointer and open the file
    fp = fopen("/sys/class/thermal/thermal_zone2/temp", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file\n");
        return -1;
    }

    // Read the file and extract the temperature value
    while ((read = getline(&line, &len, fp)) != -1)
    {
        temp = atoi(line);
    }

    // Close the file and free the memory
    fclose(fp);
    if (line)
        free(line);

    // Return the temperature value
    return temp;
}

// Function to truncate the GPU Temperature
int truncate_gpu_temp(int temp)
{
    return (double) temp / 1000;
}

// Function to truncate the GPU Frequency
int truncate_gpu_freq(int freq)
{
    return (double) freq / 1000000;
}


// Function to format the output of the GPU frequency and temperature into a string
char *get_gpu_stats()
{
    // Get the GPU frequency and temperature
    int freq = get_gpu_freq();
    int temp = get_gpu_temp();

    // Truncate the values
    freq = truncate_gpu_freq(freq);
    temp = truncate_gpu_temp(temp);

    // Allocate memory for the string   
    char *stats = malloc(MAX_SIZE * sizeof(char));

    // Check if memeory allocation was successful
    if (stats == NULL)
    {
        printf("Error: Unable to allocate memory\n");
        free(stats);
        return NULL;
    }


    // Format the string and return it
    sprintf(stats, "GPU Frequency: %.1f GPU Temperature: %.1f ", freq, temp);
    return stats;
}


int main (void)
{
    printf("%s", get_gpu_stats());
    return 0;
}