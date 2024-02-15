
// Read the sysfs files and return the values

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
#include "get_stats.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

// Changing approach to be a kernel module

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nahjay Battieste");
MODULE_DESCRIPTION("Get GPU Frequency and Temperature");

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
int truncate_gpu_temp(double temp)
{
    double temp_c = (double) temp / 1000;
    return temp_c;
}

// Function to truncate the GPU Frequency
int truncate_gpu_freq(double freq)
{
    double freq_mhz = (double) freq / 1000000;
    return freq_mhz;
}


// Function to format the output of the GPU frequency and temperature into a string
char *get_gpu_stats()
{
    // Get the GPU frequency and temperature
    int freq = get_gpu_freq();
    int temp = get_gpu_temp();

    // Truncate the values
    double freq_mhz = truncate_gpu_freq(freq);
    double temp_c = truncate_gpu_temp(temp);

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
    sprintf(stats, "GPU Freq: %.1f MHZ GPU Temp: %.1f C\n", freq_mhz, temp_c);
    return stats;
}


int main (void)
{
    printf("%s", get_gpu_stats());
    return 0;
}