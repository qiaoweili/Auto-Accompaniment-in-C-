//
// Created by 李俏蔚 on 2021/9/10.
//

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "NumCpp.hpp"
#include "score_following.h"
#include "global_config.h"
#include "RtMidi.h"
#include <cmath>
#include <math.h>
#include <aubio/aubio.h>
#include <fftw3.h>
#define PI acos(-1)

using namespace std;


auto ScoreFollower::load_score(char *midi_path, int RESOLUTION) {
    RtMidiIn *midiin = new RtMidiIn();
    auto midi_file = midi_path; //TODO
//    midi_file = pretty_midi.PrettyMIDI(midi_path)
//    instrument = midi_file.instruments[0]

    double score_tempo = 70;//TODO:shared_utils.average(midi_file.get_tempo_changes()[1])

    double sax_length = 1000; //TODO math.ceil(max([note.end for note in instrument.notes]) / resolution) + 1  # include 0
    nc::NdArray<double> sax_time = nc::arange<double>(0, sax_length * resolution, resolution);
    nc::NdArray<double> sax_pitch = nc::zeros<double>(sax_length);
    nc::NdArray<double> sax_onset = nc::zeros<double>(sax_length);

    nc::NdArray<double> pitches = nc::ones<double>(sax_length);
    pitches = signal_processing.PitchProcessorCore.NO_PITCH; //TODO: signal processing

    for note in instrument.notes:
    double start = math.ceil(note.start / resolution);
    double end = ceil(note.end / resolution) + 1 ;// # end will never go out of range
    //# truncate of note is too long
    if (end - start > int(1 / resolution)){
        end = start + int(1 / resolution);
    }
    pitches[start : end] = note.pitch
    sax_onset[start] = 1;
    score_pitch_proc = signal_processing.PitchProcessorCore()
    for i in range(sax_length):
    sax_pitch[i] = score_pitch_proc(pitches[i])
    return {score_tempo, sax_time, sax_pitch, sax_onset, sax_length};
}

auto ScoreFollower::compute_f_i_j_given_d(nc::NdArray<double> time_axis, double d, double score_tempo, double estimated_tempo)
{
    double rate_ratio;
    if (estimated_tempo >0 ){
        rate_ratio = estimated_tempo / score_tempo;
    }else{
        rate_ratio = 1e-5 / score_tempo ;
    }
    double sigma_square = log(1 / (21 * d) + 1);
    double sigma = pow(sigma_square,2);
    double mu = log(d * rate_ratio) - sigma_square / 2;
    auto f_i_j_given_d = nc::divide(1, time_axis, where=time_axis != 0) * sigma * math.sqrt(2 * math.pi) * np.exp(
            - ((np.log(time_axis, where=time_axis != 0) - mu) ** 2 / (2 * sigma ** 2)));
    f_i_j_given_d[0] = 0;
    cout << "f(i,j|d)="<< f_i_j_given_d << endl;
//    cout << "length of f(i,j|d)" << len(f_i_j_given_d) << endl;
    return f_i_j_given_d;
}

auto ScoreFollower::compute_f_i_given_d(nc::NdArray<double> f_source, nc::NdArray<double> f_i_j_given_d, double cur_pos, int axis_length){
//# apply a window here to enhance performance, but remember to avoid index overflow
    double half_win_size = ceil(window_ij / 2 * this -> points_per_second);
    double left = max(0, cur_pos - half_win_size);
    double right = min(cur_pos + half_win_size, axis_length);
    auto f_i_given_d = nc::zeros<double>(axis_length)
    auto f_source_w = f_source[left:right]
    f_i_j_given_d_w = f_i_j_given_d[:right - left]
    f_i_given_d_w = np.convolve(f_source_w, f_i_j_given_d_w)
    f_i_given_d_w = f_i_given_d_w[:right - left]  # slice to window size
    f_i_given_d[left:right] = f_i_given_d_w
    return f_i_given_d
}
auto ScoreFollower::compute_f_v_given_i(nc::NdArray<double> pitch_axis, nc::NdArray<double> onset_axis, double cur_pos,int axis_length,
                                        nc::NdArray<double> audio_pitch,nc::NdArray<double> audio_onset, pitch_proc, nc::NdArray<double> w){
    auto f_v_given_i = nc::zeros<double>(axis_length);
    //# apply a window here to enhance performance, but remember to avoid index overflow
    // TODO: remove the window
    double half_win_size = ceil(window_v / 2 * this -> points_per_second);
    double left = max(0, cur_pos - half_win_size);
    double right = min(cur_pos + half_win_size, axis_length);
    for(int i = left; i < right+1; i++){
        //TODO: window
        if (audio_pitch == signal_processing.PitchProcessorCore.NO_PITCH){
            //# performance side makes no sound
            if(pitch_axis[i] == signal_processing.PitchProcessorCore.NO_PITCH){
                //# score side also makes no sound
                f_v_given_i[i] = 0.1;
            }
            else{
                //# score side makes sound
                f_v_given_i[i] = 1e-11;
            }
        }
        else{
            //# performance side makes sound
            if(pitch_axis[i] == signal_processing.PitchProcessorCore.NO_PITCH){
                //# score side makes no sound
                f_v_given_i[i] = 1e-11;
            }
            else{
                //# score side also makes sound
                f_v_given_i[i] = pow(
                        pow(self._norm_pdf(pitch_proc.result(pitch_axis[i]), pitch_axis[i], 1), w[0])
                        * pow(self._similarity(audio_onset, onset_axis[i]), w[1]),
                        w[2]);
            }
        }

    }
    return f_v_given_i
}

double ScoreFollower::estimate_tempo(double score_tempo, double delta_pos, double delta_time) {
    return delta_pos * score_tempo * self._resolution / delta_time;
}

auto ScoreFollower::normalize(nc::NdArray<double> arr) {
    //numcpp no conversion for np.divide
    auto s = nc::sum(arr)(0,0);
    for(auto& value : arr){
        value = value / s ;
    }
    return arr;
}

double ScoreFollower::norm_pdf(int x, float mean, int sd = 1) {

    int var = pow(sd, 2);
    double denom = pow((2 * PI * var), 0.5);
    double num = exp(-pow((x - mean), 2) / (2 * var));
    return num / denom;
}



ScoreFollower::ScoreFollower() {
    //self._config = config ## include global_config.h
    //# the duration of each audio chunk
    this -> audio_interval = perf_chunk / perf_sr;
    //# the time distance between two adjacent data points on the density functions
    this -> resolution = this -> audio_interval / resolution_multiple;
    //# the number of data points the density functions contains within one second
//    this -> points_per_second = math.ceil(1 / self._resolution); //TODO
//# `sax_` means `Score AXis`
    auto return_loadscore = ScoreFollower::load_score(score_midi, this->resolution);
    this -> score_tempo = return_loadscore[0];
    this -> sax_time = return_loadscore[1];
    this -> sax_pitch = return_loadscore[2];
    this -> sax_onset = return_loadscore[3];
    this -> sax_length = return_loadscore[4];
    this -> f_source = nc::zeros<double>(this->sax_length);
//    this->sax_time = nc::NdArray<double>(3);
    this -> f_source[0] = 1;
    this -> cur_pos = 0;
    this -> estimated_tempo = this -> score_tempo;
    this -> prev_report_time = 0;
    this -> prev_tempo_pos = 0;
    this -> prev_tempo_time = 0;
    this -> first_run = true;
    this -> no_move = false;
//# use this x-axis to compute expectation
    this -> f_x_axis = nc::arange<double>(this -> sax_length);
    cout << "sax_length:" << this ->sax_length << endl;
    this -> tempo_ub = 1.3 * this -> score_tempo;
    this -> tempo_lb = 0.7 * this -> score_tempo;

    if (perf_mode == 0){
        //TODO
        //self._audio_input = audio_io.WaveFileInput(self._config)
    }else if (perf_mode == 1){
        //TODO
//        self._audio_input = audio_io.MicrophoneInput(self._config)
//        self._audio_input.connect_to_proc(self._proc)
//        self._pitch_proc = signal_processing.PitchProcessor(self._config)
//        self._onset_proc = signal_processing.OnsetProcessor(self._config)
//        self._msg_sender = udp_pipe.UDPSender()
//        self._live_display = None
    }
}









//score_midi, score_axis, score_onsets, onsets, raw_score_midi, axis_loudness = get_time_axis(resolution, midi_file)
// self._score_tempo, self._sax_time, self._sax_pitch, self._sax_onset, self._sax_length = \
//     ScoreFollower._load_score(self._midi_path, self._resolution)

struct score_result {int score_tempo; int sax_time; int sax_pitch; int sax_onset; int sax_length; float axis_loudness;};
score_result load_score(float RESOLUTION, string midi_path){

}

//scorefollowing
// if self._f_source[self._cur_pos] > 0.1:
//     w = (0.95, 0.05, 0.5)
// else:
//     w = (0.7, 0.3, 0.3)
float w[3];
float conf = 0;
// w 在运行中确定
// if (conf > 0.1)
// {
//     w[0] = 0.95;
//     w[1] = 0.05;
//     w[2] = 0.5;
//     //w[3] = {0.95, 0.05, 0.5};
// }else{
//     w[0] = 0.7;
//     w[1] = 0.3;
//     w[2] = 0.3;
//     //w[3] = {0.7, 0.3, 0.3};
// }
// cout << w[0] << w[1] << w[2]<< endl;


// def _compute_f_i_j_given_d(time_axis, d, score_tempo, estimated_tempo):
struct f_i_j_given_d{};//或直接array
float * compute_f_i_j_given_d(float* time_axis, int d, float score_tempo, float estimated_tempo){

}

//def _compute_f_i_given_d(f_source, f_i_j_given_d, cur_pos, axis_length):
float * compute_f_i_given_d(float* f_source, float* f_i_j_given_d, float cur_pos, int axis_length){
}


//def _compute_f_v_given_i(pitch_axis, onset_axis, cur_pos, axis_length, audio_pitch, audio_onset, pitch_proc, w):
float * compute_f_v_given_i(float* pitch_axis, float* onset_axis, float cur_pos, int axis_length, float audio_pitch, int audio_onset, int pitch_proc, float* w){

//def _estimate_tempo(self, score_tempo, delta_pos, delta_time):
// struct scorefollower{float resolution;};
    float estimate_tempo(float resolution, float score_tempo, float delta_pos,float delta_time){
        float ans = delta_pos * score_tempo * resolution / delta_time;
        return 0.1;
    }