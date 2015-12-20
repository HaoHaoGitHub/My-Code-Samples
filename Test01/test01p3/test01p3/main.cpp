//
//  main.cpp
//  test01p3
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include <iostream>
#include "line.h"
#include <iomanip>

void printLines(const std::vector<Line> &lines);

int main() {
    Line a ("A", 0, 0, 2, 2);
    Line b ("B", 5, 5, 1, 5);
    Line c ("C", 2, 1, -2, 3);
    Line d ("D", -1, 4, 4, 4);
    
    std::vector<Line> lines;
    lines.push_back(a);
    lines.push_back(b);
    lines.push_back(c);
    lines.push_back(d);
    
    std::cout << b.getSlope() << "\n";
    
    std::cout << "original data, sorted by slope" << std::endl;
    sort(lines.begin(),lines.end(),by_slope);
    printLines(lines);
    
    
    for (int i = 0; i < lines.size(); i++) {
        lines[i].setNewSecondPoint(3,3);
    }
    std::cout << "after changing second point to (3,3)" << std::endl;
    sort(lines.begin(),lines.end(),by_slope);
    printLines(lines);
    
    
    return 0;
}

void printLines(const std::vector<Line> &lines) {
    for (int i = 0; i < lines.size(); i++) {
        std::cout << "Line " << lines[i].getName()
        << std::fixed << std::setprecision(2)
        << " with slope=" << std::setw(5) << lines[i].getSlope()
        << " and y intercept=" << std::setw(5) << lines[i].getYIntercept()
        << std::endl;
    } }
