//
// Created by 李俏蔚 on 2021/9/17.
//

#ifndef CLION_GLOBAL_CONFIG_H
#define CLION_GLOBAL_CONFIG_H
#include <string>

extern const char* name;
extern const int perf_mode;
extern const char* perf_audio;
extern const int perf_sr;
extern const double perf_chunk;
extern const int resolution_multiple;
extern const int window_ij;
extern const float window_v;
extern const int pos_report_interval;
extern const int tempo_estimate_interval;
extern const int regression_depth;
extern const int audio_input_latency;
extern char* score_midi;
extern const char* acco_midi;
extern const int acco_mode;
extern const char* acco_device;
extern const int trunc_time;
extern const bool dump;


#endif //CLION_GLOBAL_CONFIG_H
