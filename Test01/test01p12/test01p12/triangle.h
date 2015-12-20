//
//  triangle.h
//  test01p12
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#ifndef __test01p12__triangle__
#define __test01p12__triangle__

#include <stdio.h>
#include <vector>

class Triangle{
public:
    // Constructors:
    Triangle(double a, double b, double c);
    Triangle(const std::vector<double> &athree_lengths);
    
    
    // Accessor
    
    const double getPerimeter() const;
    const double getArea() const;
    
    // Modifier
    
    void doubleShortestEdge();
    
private:
    double a_;
    double b_;
    double c_;
};


#endif /* defined(__test01p12__triangle__) */
