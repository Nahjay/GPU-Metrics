#ifndef GET_STATS_H
#define GET_STATS_H

int get_gpu_freq();
int get_gpu_temp();
char* get_gpu_stats();
int truncate_gpu_freq(int freq);
int truncate_gpu_temp(int temp);

#endif