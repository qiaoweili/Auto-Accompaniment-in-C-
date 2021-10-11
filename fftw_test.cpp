//
// Created by 李俏蔚 on 2021/10/11.
//
//TODO: Test fftw3 for 1-dim DFTs of Real Data (real = complex a+0i)
//TODO: Covolution of two Discrete Fourier transforms,fft of point wise product
//https://www.fftw.org/fftw3_doc/One_002dDimensional-DFTs-of-Real-Data.html
//https://www.youtube.com/watch?v=geYbCA137PU
//https://stackoverflow.com/questions/11178080/calculating-convolution-of-two-functions-using-fft-fftw

#include <complex.h>
#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
// 1) allocate memory, time series(real, double; complex), frequency coefficient
// 2) fill array with data
// 3) create a plan


#define REAL 0
#define IMAG 1
//length of the complex arrays
#define N 8

//Compute 1-d FFT
void fft(fftw_complex *in, fftw_complex *out){
    //create a DFT plan
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    //Execute plan
    fftw_execute(plan);
    //cleaning
    fftw_destroy_plan(plan);
    fftw_cleanup();
}


//Compute 1-d inverse FFT
void ifft(fftw_complex *in, fftw_complex *out){
    //create a IDFT plan
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    //Execute plan
    fftw_execute(plan);
    //cleaning
    fftw_destroy_plan(plan);
    fftw_cleanup();
    //scale output to obtain the exact inverse
    for (int i = 0; i < N; ++i) {
        out[i][REAL] /= N;
        out[i][IMAG] /= N;
    }
}



//TODO: multiple inputs for 1-dim fft
//To convolve 2 signals via FFT you generally need to do this:
//Add as many zeroes to every signal as necessary so its length becomes the cumulative length of the original signals - 1 (that's the length of the result of the convolution).
//If your FFT library requires input lengths to be powers of 2, add to every signal as many zeroes as necessary to meet that requirement too.
//Calculate the DFT of signal 1 (via FFT).
//Calculate the DFT of signal 2 (via FFT).
//Multiply the two DFTs element-wise. It should be a complex multiplication, btw.
//Calculate the inverse DFT (via FFT) of the multiplied DFTs.
void multifft(fftw_complex *in1, fftw_complex *in2, fftw_complex *out1, fftw_complex *out2, fftw_complex *result){
//    convolution = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * numNeurons);
    fftw_plan plan1 = fftw_plan_dft_1d(N, in1, out1, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan1);
    fftw_plan plan2 = fftw_plan_dft_1d(N, in2, out2, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan2);
    // convolution in frequency domain
    fftw_complex *convolution_f ;
    convolution_f = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    for(unsigned int i = 0; i < N; ++i)
    {
        convolution_f[i][0] = (out1[i][0] * out2[i][0]
                               - out1[i][1] * out2[i][1]) / N;
        convolution_f[i][1] = (out1[i][0] * out2[i][1]
                               - out1[i][1] * out2[i][0]) /N;
    }
    //IFFT
    fftw_plan iplan = fftw_plan_dft_1d(N, convolution_f, result, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan2);

    fftw_destroy_plan(plan1);
    fftw_destroy_plan(plan2);
    fftw_destroy_plan(iplan);
    fftw_cleanup();
}


//Displays complex numbers in form of a +/- bi
void displayComplex(fftw_complex *y){
    for (int i = 0; i < N; ++i) {
        if (y[i][IMAG]<0){
            cout << y[i][REAL] << "-" << abs(y[i][IMAG]) << "i" << endl;
        } else{
            cout << y[i][REAL] << "+" << abs(y[i][IMAG]) << "i" << endl;
        }
    }
}


//Displays real part of complex numbers
void displayReal(fftw_complex *y){
    for (int i = 0; i < N; ++i) {
        cout << y[i][REAL] << endl;
    }
}


void displayResult(fftw_complex *y){
    for (int i = 0; i < N; ++i) {
        if (y[i][IMAG]<0){
            cout << y[i][REAL] << "-" << abs(y[i][IMAG]) << "i" << endl;
        } else if(y[i][IMAG] == 0){
            cout << y[i][REAL] << endl;
        }else{
            cout << y[i][REAL] << "+" << abs(y[i][IMAG]) << "i" << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    //input array
    fftw_complex x[N];
    //output array
    fftw_complex y[N];
    // fill in the arrays
    for (int i = 0; i < N; ++i) {
        x[i][REAL] = i+1;
        x[i][IMAG] = 0;
    }
    //compute fft of x, store result in y
    fft(x,y);
    //display results of fft
    cout << "compute fft:" << endl;
    displayResult(y);

    //compute ifft of y, store result in x
    ifft(y,x);
    //display results
    cout<< "\ncompute ifft:" << endl;
    displayResult(x);

    //TODO: Test convolution for two input 1-d vectors
    fftw_complex in1[N];
    fftw_complex in2[N];
    for (int i = 0; i < N; ++i) {
        in1[i][REAL] = i+1;
        in2[i][REAL] = i+2;
        in1[i][IMAG] = 0;
        in2[i][IMAG] = 0;
    }
    fftw_complex out1[N];
    fftw_complex out2[N];
    fftw_complex result[N];
    multifft(in1, in2, out1, out2, result);
    cout << "compute 2 vector input fft:" << endl;
    displayResult(result);

    return 0;
}

