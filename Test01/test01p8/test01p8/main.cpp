//
//  main.cpp
//  test01p8
//
//  Created by 陈昊 on 2/21/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

// 注意！！这个代码好好学习老师的代码！！！

#include <iostream>
void find_min_and_max(double *data, int n, double &min, double &max);

int main(int argc, const char * argv[]) {
    int n = 5;
    double *data = new double[n];
    for (unsigned int i = 0; i < n; i++) {
        std::cout << "Please enter: ";
        std::cin >> data[i];
    }
    for (unsigned int i = 0; i < n; i++) {
        if (data[i] < 0) {
            data[i] = - data[i];
        }
    
    }
    double min, max;
    find_min_and_max(data, n, min , max);
    std::cout << "absolute values: ";
    unsigned int i;
    for (i = 0; i < n; i++) {std::cout << data[i] << " ";  }
    std::cout << std::endl;
    std::cout << "min: " << min << std::endl;
    std::cout << "max: " << max << std::endl;
    delete [] data;
    data = NULL;
    return 0;
}


void find_min_and_max(double *data, int n, double &min, double &max){
    for (unsigned int i = 0; i < n; i++) {
        max = data[0];
        if (data[i] > max) {
            max = data[i];
        }
    }
    for (unsigned int i = 0; i < n; i++) {
        min = data[0];
        if (data[i] < min) {
            min = data[i];
        }
    }
}