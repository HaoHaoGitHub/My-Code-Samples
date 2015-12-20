//
//  main.cpp
//  test01p12
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#include <iostream>
#include "triangle.h"



int main(int argc, const char * argv[]) {
    
    Triangle t1(9.0,5.0,5.0);
    std::vector<double> vec(3);
    vec[0] = 3.0; vec[1] = 4.0; vec[2] = 5.0;
    Triangle t2(vec);
    
    std::cout << "t1 [initial]     ";
    std::cout << "perimeter=" << t1.getPerimeter() << " area=" << t1.getArea() << "\n";
    std::cout << "t2 [initial]     ";
    std::cout << "perimeter=" << t2.getPerimeter() << " area=" << t2.getArea() << "\n\n";
    
    t1.doubleShortestEdge();
    std::cout << "t1 [after edit]  ";
    std::cout << "perimeter=" << t1.getPerimeter() << " area=" << t1.getArea() << "\n";
    t2.doubleShortestEdge();
    t2.doubleShortestEdge();
    t2.doubleShortestEdge();
    std::cout << "t2 [after edit]  ";
    std::cout << "perimeter=" << t2.getPerimeter() << " area=" << t2.getArea() << "\n";
    
    
    
    
    
    
    
    return 0;
}
