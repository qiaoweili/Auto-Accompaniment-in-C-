//
// Created by 李俏蔚 on 2021/9/12.
//

#ifndef CLION_SCORE_FOLLOWING_H
#define CLION_SCORE_FOLLOWING_H


class ScoreFollower {

    private:
        //# the duration of each audio chunk
        double audio_interval;// = config->perf_chunk / config->perf_sr
        //# the time distance between two adjacent data points on the density functions
        double resolution; //= audio_interval / self._config['resolution_multiple']
        //# the number of data points the density functions contains within one second
        int points_per_second; //= math.ceil(1 / self._resolution)
        //# `sax_` means `Score AXis`
        double score_tempo;
        nc::NdArray<double> sax_time;  //TODO: auto in header files?
        nc::NdArray<double> sax_pitch;
        nc::NdArray<double> sax_onset;
        double sax_length;
    // = \self._load_score(self._config['score_midi'], self._resolution)
//        struct load_score(string score_midi, int RESOLUTION);
        nc::NdArray<double> f_source;//self._f_source = np.zeros(self._sax_length)
            //self._f_source[0] = 1
        double cur_pos;//self._cur_pos = 0
        double estimated_tempo;//self._estimated_tempo = self._score_tempo
        double prev_report_time;//self._prev_report_time = 0
        double prev_tempo_pos; //self._prev_tempo_pos = 0
        double prev_tempo_time;//self._prev_tempo_time = 0
        bool first_run;// self._first_run = True
        bool no_move;//self._no_move = False
    //# use this x-axis to compute expectation
        nc::NdArray<double> f_x_axis;// self._f_x_axis = np.arange(self._sax_length)
        float tempo_ub;//self._tempo_ub = 1.3 * self._score_tempo
        float tempo_lb;//self._tempo_lb = 0.7 * self._score_tempo

//    if self._config['perf_mode'] == 0:
//    self._audio_input = audio_io.WaveFileInput(self._config)
//    elif self._config['perf_mode'] == 1:
//    self._audio_input = audio_io.MicrophoneInput(self._config)
//    self._audio_input.connect_to_proc(self._proc)
//    self._pitch_proc = signal_processing.PitchProcessor(self._config)
//    self._onset_proc = signal_processing.OnsetProcessor(self._config)
//    self._msg_sender = udp_pipe.UDPSender()
//    self._live_display = None

public:
    //init
    ScoreFollower();
    void signal_handler(_signal, _frame);
//    void _load_score(midi_path, resolution);
    auto load_score(char* midi_path, int RESOLUTION);
    void proc(a_time, prev_a_time, a_data, a_input: audio_io.AudioInput);

    auto compute_f_i_j_given_d(nc::NdArray<double> time_axis, double d, double score_tempo, double estimated_tempo); //auto 格式？
    auto compute_f_i_given_d(nc::NdArray<double> f_source, nc::NdArray<double> f_i_j_given_d, double cur_pos, int axis_length);
    auto compute_f_v_given_i(nc::NdArray<double> pitch_axis, nc::NdArray<double> onset_axis, double cur_pos,
                             int axis_length, nc::NdArray<double> audio_pitch,
                             nc::NdArray<double> audio_onset, pitch_proc, nc::NdArray<double> w);
    //TODO: check dtype : audio_pitch audio_onset pitch_proc

    double estimate_tempo(double score_tempo, double delta_pos, double delta_time);
    auto normalize(nc::NdArray<double>array);
    double norm_pdf(int x, float mean, int sd);
};




signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

#endif //CLION_SCORE_FOLLOWING_H
