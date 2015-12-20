//
//  line.cpp
//  test01p3
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include "line.h"

Line::Line(const std::string &Name, int endpoint1x, int endpoint1y, int endpoint2x, int endpoint2y){
    Name_ = Name;
    endpoint1x_ = endpoint1x;
    endpoint1y_ = endpoint1y;
    endpoint2x_ = endpoint2x;
    endpoint2y_ = endpoint2y;
}

const int Line::getend1x() const{
    return endpoint1x_;
}
const int Line::getend1y() const{
    return endpoint1y_;
}
const int Line::getend2x() const{
    return endpoint2x_;
}
const int Line::getend2y() const{
    return endpoint2y_;
}



const std::string& Line::getName() const{
    return Name_;
}

const float Line::getSlope() const{
    float d1 = endpoint2y_ - endpoint1y_; // Pay attention !!!!!!!!!!!!!!!!
    float d2 = endpoint2x_ - endpoint1x_;
    return d1/d2;
}

const float Line::getYIntercept() const{
    float result;
    result = endpoint1y_ - endpoint1x_*getSlope();
    return result;
}

void Line::setNewSecondPoint(int x, int y){
    endpoint2x_ = x;
    endpoint2y_ = y;
}

bool by_slope(Line &line1, Line &line2){
    float result1 = line1.getSlope();
    float result2 = line2.getSlope();
    return result1 < result2;
    
}