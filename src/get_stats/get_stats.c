
// Read the sysfs files and return the values

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


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

    printf("GPU Frequency: %d\n", freq);

    return freq;
}

int main (void)
{
    get_gpu_freq();
    return 0;
}