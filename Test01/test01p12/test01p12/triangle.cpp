//
//  triangle.cpp
//  test01p12
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include "triangle.h"
#include <cmath>
#include "assert.h"

Triangle::Triangle(double a, double b, double c) {
    a_ = a;
    b_ = b;
    c_ = c;
}


Triangle::Triangle(const std::vector<double> &athree_lengths){
    assert (athree_lengths.size() == 3);
    a_ = athree_lengths[0];
    b_ = athree_lengths[1];
    c_ = athree_lengths[2];
}

const double Triangle::getPerimeter() const{
    return a_ + b_ + c_;
}


const double Triangle::getArea() const{
    double s = getPerimeter()/2.0;// 这里注意！！！！！！！！！！！！！！！！！！！！！！！！！
    return sqrt(s*(s-a_)*(s-b_)*(s-c_));
}

void Triangle::doubleShortestEdge(){
    if (a_ <= b_ && a_ <= c_) {
        a_ *= 2;
    }else if (b_ <= a_ && b_ <= c_)
        b_ *=2;
    else {
    assert(c_ <= a_ && c_ <= b_);
     c_ *= 2;
    }
}
















