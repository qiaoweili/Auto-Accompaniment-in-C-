//
// Created by 李俏蔚 on 2021/9/10.
//
#include <iostream>
#include <string>
#include "accompaniment.h"
#include "RtMidi.h"
#include "NumCpp.hpp"
using namespace std; //std::
using FunctionType = std::function<double(const nc::NdArray<double>&, const nc::NdArray<double>&)>;


//midi file names
string midi_name = "017";

//concat midi_file path
const string midi_path_prefix = "pop909_converted/pop909_melody/";
const string midi_path_suffix = ".mid";
string midi_path =midi_path_prefix + midi_name + midi_path_suffix;
//audio end time
int trunc_time = 100;

Accompaniment::Accompaniment(){
//    string midi_path;
//    int start_time;
    nc::NdArray<float> fax_time = { [float(-x) for(auto& value : regression_depth)] }; // 一行式for(auto& value : a)
    nc::NdArray<float> fax_pos = { [float(-x) for(auto& value : regression_depth)] };; // np.arraynp.array([float(-x) for x in range(self._config['regression_depth'])])
    int* fax_conf; // np.full
    int peer_start_time;
    int peer_score_tempo;
};

//score_midi, score_axis, score_onsets, onsets, raw_score_midi, axis_loudness = get_time_axis(resolution, midi_file)
// self._score_tempo, self._sax_time, self._sax_pitch, self._sax_onset, self._sax_length = \
//     ScoreFollower._load_score(self._midi_path, self._resolution)





int main(){
    cout<< midi_path <<endl;
    for (int i :) {

    }
}
