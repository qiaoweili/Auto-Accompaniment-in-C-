//
// Created by 李俏蔚 on 2021/10/7.
//

#include "numcppExtend.h"

void true_divide(nc::NdArray<double> arr, double d){
    for(auto& value : arr){
        value = value / d;
    }
    return 0;
}
