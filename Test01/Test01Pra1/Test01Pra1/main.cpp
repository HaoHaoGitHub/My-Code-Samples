//
//  main.cpp
//  Test01Pra1
//
//  Created by 陈昊 on 2/21/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

void make_power_matrix(int num_rows, int num_columns, std::vector< std::vector<int> > &matrix){
    matrix.resize(num_rows);
    for (int i = 0; i < num_rows; i++) {
        matrix[i].resize(num_columns);
    }
    int base = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            if (j == 0)
                base = 1;
            else
              base = base * i;
              matrix[i][j] = base;
        }
    }
    int n = matrix[num_rows-1][num_columns-1];
    int width = log10(n) + 1;//**************************************************************************
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            std::cout << std::setw(width+5) << std::right << matrix[i][j];
        }
        std::cout << std::endl;
    }
    
}



int main() {
    std::vector<std::vector<int>> matrix;
    make_power_matrix(5, 7, matrix);
//    int flag = 0;
//    int a = 4096;
//    while (a) {
//        a /= 10;
//        flag++;
//    }
//    int a = log10(4096)+1;
//    std::cout << a << std::endl;
    return 0;
}




