//
// Created by 李俏蔚 on 2021/9/10.
//

#ifndef CLION_ACCOMPANIMENT_H
#define CLION_ACCOMPANIMENT_H

#define SUPER_SAMPLING_FACTOR = 5
#define RATIO_CHANGE_LEARNING_RATE = 0.2
#define RESOLUTION = 0.01
#define PERF_CHUNK = 2048
#define PERF_SR = 44100
#define regression_depth = 4
//string midi_path;
//const string midi_path_prefix;

class Accompaniment{
    string midi_path;
    int start_time;
    nc::NdArray<float> fax_time; // 需改成 numcpp格式 np.arrays
    int* fax_pos; // np.array
    int* fax_conf; // np.full
    int peer_start_time;
    int peer_score_tempo;

    Accompaniment();
};

struct score_result {int score_tempo; int sax_time; int sax_pitch; int sax_onset; int sax_length; float axis_loudness;};
score_result load_score(float RESOLUTION, string midi_path){

}



#endif //CLION_ACCOMPANIMENT_H
