
// Read the sysfs files and return the values

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "get_stats.h"


// Function to extract the frequency value of the GPU from the sysfs file
int get_gpu_freq()
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int freq = 0;

    fp = fopen("/sys/devices/gpu.0/devfreq/57000000.gpu/cur_freq", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file\n");
        return -1;
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        freq = atoi(line);
    }

    fclose(fp);
    if (line)
        free(line);

    return freq;
}

// Function to extract the temperature value of the GPU from the sysfs file
int get_gpu_temp()
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int temp = 0;

    fp = fopen("/sys/class/thermal/thermal_zone2/temp", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file\n");
        return -1;
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        temp = atoi(line);
    }

    fclose(fp);
    if (line)
        free(line);

    return temp;
}

// Function to format the output of the GPU frequency and temperature into a string
char *get_gpu_stats()
{
    int freq = get_gpu_freq();
    int temp = get_gpu_temp();
    char *stats = malloc(100 * sizeof(char));
    sprintf(stats, "GPU Frequency: %d\nGPU Temperature: %d\n", freq, temp);
    return stats;
}


int main (void)
{
    get_gpu_freq();
    get_gpu_temp();
    printf("%s", get_gpu_stats());
    return 0;
}