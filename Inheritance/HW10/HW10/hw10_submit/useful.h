//
//  useful.h
//  HW10
//
//  Created by 陈昊 on 5/6/15.
//  Copyright (c) 2015 陈昊. All rights reserved.
//

#ifndef HW10_useful_h
#define HW10_useful_h

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include "utilities.h"
/* This header file contains the utility functions for distinguishing different shapes */

// epsilon values used in comparing the edge lengths & angles between
// edges note that these values are dependent on the precision of
// the coordinates and the overall scale of the objects
#define DISTANCE_EPSILON 0.0001
#define ANGLE_EPSILON 0.1

inline bool IS_A_Polygon (const std::vector<Point> &points) {
    if (points.size() < 3) return false;
    for (unsigned int i = 0; i < points.size() - 2; ++i) {
        if (EqualAngles(Angle(points[i], points[i+1], points[i+2]), 180.0) ||
                        EqualAngles(Angle(points[i], points[i+1], points[i+2]), 0.0)) return false;
    }
    // Check the first one point and final one point:
    double angle1 = Angle(points[points.size() - 1], points[0], points[1]);
    double angle2 = Angle(points[points.size() - 2], points[points.size() - 1], points[0]);
    if (EqualAngles(angle1, 180.0) || EqualAngles(angle1, 0.0)) return false;
    if (EqualAngles(angle2, 180.0) || EqualAngles(angle2, 0.0)) return false;
    // return true if all the above condition meet
    return true;
}
inline bool Is_a_RightTriangle(const std::vector<Point> &points) {
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[0]);
    double angle3 = Angle(points[2], points[0], points[1]);
    if (RightAngle(angle1) || RightAngle(angle2) || RightAngle(angle3)) return true;
    else return false;
}


inline bool Is_a_IsoscelesTriangle (const std::vector<Point> &points) {
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[0]);
    double angle3 = Angle(points[2], points[0], points[1]);
    if ( EqualAngles(angle1, angle2) || EqualAngles(angle2, angle3) || EqualAngles(angle1, angle3))
        return true;
    return false;
}
// =====================================================================
inline bool Is_A_ObtuseTriangle(const std::vector<Point> &points) {
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[0]);
    double angle3 = Angle(points[2], points[0], points[1]);
    if (ObtuseAngle(angle1) || ObtuseAngle(angle2) || ObtuseAngle(angle3)) return true;
    else return false;
}

inline bool Is_A_EquilateralTriangle(const std::vector<Point> &points) {
    double length1 = DistanceBetween(points[0], points[1]);
    double length2 = DistanceBetween(points[1], points[2]);
    double length3= DistanceBetween(points[2], points[0]);
    if (EqualSides(length1, length2) && EqualSides(length2, length3) && EqualSides(length1, length2)) return true;
    else return false;
}


// ==============================================================
inline bool Is_A_Trapezoid(const std::vector<Point> &points) {
    Vector s1(points[0],points[1]);
    Vector s2(points[1],points[2]);
    Vector s3(points[2],points[3]);
    Vector s4(points[3],points[0]);
    if (Parallel(s1, s3) || Parallel(s2, s4)) return true;
    else return false;
}


inline bool Is_A_IsoscelesTrapezoid(const std::vector<Point> &points) {
    Vector s1(points[0],points[1]);
    Vector s2(points[1],points[2]);
    Vector s3(points[2],points[3]);
    Vector s4(points[3],points[0]);
    // If two of the unneighbored sides are paralled, then the other should be equal length
    if (Parallel(s1, s3)) {
        if (EqualAngles(Angle(points[3], points[0], points[1]), Angle(points[0], points[1], points[2]))) return true;
        else return false;
    } else if (Parallel(s2, s4)) {
        if (EqualAngles(Angle(points[0], points[1], points[2]), Angle(points[1], points[2], points[3]))) return true;
        else return false;
    }
    return false;
}

inline bool Is_A_Parallelogram(const std::vector<Point> &points) {
    Vector s1(points[0],points[1]);
    Vector s2(points[1],points[2]);
    Vector s3(points[2],points[3]);
    Vector s4(points[3],points[0]);
    if (Parallel(s1, s3) && Parallel(s2, s4)) return true;
    else return false;
}

inline bool Is_A_Rectangle(const std::vector<Point> &points) {
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[3]);
    double angle3 = Angle(points[2], points[3], points[0]);
    double angle4 = Angle(points[3], points[0], points[1]);
    if (RightAngle(angle1) && RightAngle(angle2) && RightAngle(angle3)
        && RightAngle(angle4)) return true;
    return false;
}

inline bool Is_Concave_Shape(const std::vector<Point> &points) {
    // Check the first angle and the final angle:
    double angle_begin = Angle(points[points.size() - 1], points[0], points[1]);
    double angle_end = Angle(points[points.size() - 2], points[points.size() - 1], points[0]);
    if (ReflexAngle(angle_begin)) return true;
    if (ReflexAngle(angle_end)) return true;
    for(unsigned int i = 0; i < points.size()-2; i++){
        if (ReflexAngle(Angle(points[i], points[i+1], points[i+2]))) return true;
    }
    return false;
}

inline bool Is_A_Kite(const std::vector<Point> &points) {
    // first judge wheather it is convex:
    if (Is_Concave_Shape(points)) return false;
    // This following code is based on the factor that the shape is not concave:
    Vector s1(points[0],points[1]);
    Vector s2(points[1],points[2]);
    Vector s3(points[2],points[3]);
    Vector s4(points[3],points[0]);
    if (s1.Length() == s2.Length()){
        if (s3.Length() == s4.Length()) return true;
        else return false;
    }
    else{assert(s1.Length() != s2.Length());
        if (s2.Length() == s3.Length() && s4.Length() == s1.Length()) return true;
        else return false;
        
    }
    
    return false;
}

inline bool Is_A_Rhombus(const std::vector<Point> &points) {
    double length = DistanceBetween(points[0], points[points.size() - 1]);
    for (unsigned int i = 0; i < points.size() - 1; ++i) {
        double temp_length = DistanceBetween(points[i], points[i+1]);
        if (! EqualSides(temp_length, length)) return false;
    }
    return true;
}


inline bool Is_A_Arrow(const std::vector<Point> &points) {
    // first judge wheather it is convex:
    if (! Is_Concave_Shape(points)) return false;
    // This following code is based on the factor that the shape is concave:
    Vector s1(points[0],points[1]);
    Vector s2(points[1],points[2]);
    Vector s3(points[2],points[3]);
    Vector s4(points[3],points[0]);
    if (EqualSides(s1.Length(), s2.Length())) {
        if (EqualSides(s3.Length(), s4.Length())) return true;
        else return false;
    } else if (EqualSides(s2.Length(), s3.Length())) {
        if (EqualSides(s1.Length(), s4.Length())) return true;
        else return false;
    } else if (EqualSides(s3.Length(), s4.Length())) {
        if (EqualSides(s1.Length(), s2.Length())) return true;
        else return false;
    } else if (EqualSides(s4.Length(), s1.Length())) {
        if (EqualSides(s2.Length(), s3.Length())) return true;
        else return false;
    }
    
    return false;
}






#endif
