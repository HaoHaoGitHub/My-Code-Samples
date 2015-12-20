//
//  line.h
//  test01p3
//
//  Created by 陈昊 on 2/22/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#ifndef __test01p3__line__
#define __test01p3__line__

#include <stdio.h>
#include <vector>
#include <string>

class Line {
    
public:
    // Constructors:
    Line(const std::string &Name, int endpoint1x, int endpoint1y, int endpoint2x, int endpoint2y);
    
    // Accessors:
    const std::string& getName() const;
    const float getSlope() const;
    const float getYIntercept() const;
    const int getend1x() const;
    const int getend1y() const;
    const int getend2x() const;
    const int getend2y() const;
    
    // Modifiers
    void setNewSecondPoint(int x, int y);
    
    
    
private:
    std::string Name_;
    int endpoint1x_;
    int endpoint1y_;
    int endpoint2x_;
    int endpoint2y_;
};
bool by_slope(Line &line1, Line &line2);

#endif /* defined(__test01p3__line__) */
