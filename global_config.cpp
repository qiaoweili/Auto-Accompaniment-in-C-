//
// Created by 李俏蔚 on 2021/9/17.
//
#include "global_config.h"
#include <string>

// Name of the profile 'name': 'yqnyh',
extern const char* name = "yqnyh";

//# Input mode of performance
// > `0` - wave file
// > `1` - microphone  'perf_mode': 1,
extern const int perf_mode = 1;

//# File path of performance wave file#
// * Takes effects only when `perf_mode` is set to `0` 'perf_audio': '',
extern const char* perf_audio = "";

//# Sample rate of performance input#
// * Takes effects only when `perf_mode` is set to `1`#
// * Advanced options 'perf_sr': 44100,
extern const int perf_sr = 44100;

//# Number of samples processed in each iteration#
// * Advanced options 'perf_chunk': 2048,
extern const double perf_chunk = 2048;

//# Number of discrete points that the probability density function keeps within the duration of one audio chunk
//#   * Advanced options
extern const int resolution_multiple = 4;

//# The size of the window of the f-IJ-given-D density function
//#   * Advanced options
extern const int window_ij = 25;

//# The size of the window of the f-V-given-D density function
//#   * Advanced options
extern const float window_v = 5;

//# The time to wait between each IPC message
//#   * Advanced options
extern const int pos_report_interval = 1;

//# The beat to wait between each tempo estimation
//#   * Advanced options
extern const int tempo_estimate_interval = 2;

//# The number of historical points the regression model takes consideration into
//#   * Advanced options
extern const int regression_depth = 4;

//# The input latency caused by the audio buffer
//#   * Advanced options
extern const int audio_input_latency = 0;

//# File path of performance MIDI file
extern char* score_midi = 'resources/pop909/pop909_melody/019.mid';

//# File path of accompaniment MIDI file
extern const char* acco_midi = 'resources/pop909/pop909_acco/019.mid';

//# Output mode of accompaniment
//#   > `0` - Virtual MIDI synthesizer
//#   > `1` - External MIDI synthesizer
extern const int acco_mode = 0;

//# Name of External MIDI Device
//#   * Takes effect only when `acco_mode` is set to `1`
extern const char* acco_device = 'CASIO USB-MIDI';

//# Save verbose information to file for debugging
//        'dump': True,
//extern const bool dump = true;

//# The time to stop before the score ends, set to `0` to disable it
//#   * Takes effect only when `dump` is set to `True`
extern const int trunc_time = 30;

