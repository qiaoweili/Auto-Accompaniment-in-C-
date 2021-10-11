//
// Created by 李俏蔚 on 2021/9/7.
//
#include <iostream>
#include <boost/filesystem.hpp>
#include "NumCpp.hpp"
#include "numcppExtend.h"
using namespace std;
int main(){
//    for (int i = 0; i < 5; i++) {
//        std::cout << i << "\n"<< std::endl;
//    }

//    nc::NdArray<int> a0 = { {1, 2}, {3, 4} };
//    auto a13 = nc::ones<int>(3, 4);
//    for(auto& value : a0){
//        cout<< value<< "";
//    }
//    for(auto& value : a13){
//        cout << value << "";
//    }
//    double n = 2048;
//    cout << n/44100 << endl;
//    auto npfull =  nc::ones<double>(3);
//    npfull=2;
//    for (auto& value : npfull) {
//        cout << value << endl;
//    }
    auto x = nc::arange<double>(6);
//    true_divide(x , 2);
//    for(auto& value : x){
//        value = value / 2;
//    }
//    for (auto& value : x) {
//        cout << value << endl;
//    }
    auto s = nc::sum(x)(0,0);
//    int ss = s(0,0);
    cout << s << endl;


    return 0;

}