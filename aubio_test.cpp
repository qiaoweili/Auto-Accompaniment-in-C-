//
// Created by 李俏蔚 on 2021/10/11.
//First, define a few variables and allocate some memory

#include <aubio/aubio.h>
#include <string>
#include "global_config.h"
using namespace std;
#define PATH "resource/audio3.wav"
uint_t samplerate = 0;
uint_t hop_size = 256;
uint_t n_frames = 0, read = 0;
char_t *source_path = "resource/audio3.wav";
aubio_source_t* s = new_aubio_source(source_path, samplerate, hop_size);
fvec_t *vec = new_fvec(hop_size);

//for the processing loop:
do {
aubio_source_do(s, vec, &read);
fvec_print (vec);
n_frames += read;
} while ( read == hop_size );

