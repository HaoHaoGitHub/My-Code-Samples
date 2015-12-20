
#include "polygons.h"
#include "utilities.h"
#include "useful.h"

// Useful member functions that can be applied to any shapes
// --------------------------------------------------------------------------------

bool Polygon::HasAllEqualSides() {
    double length = DistanceBetween(points_[0], points_[points_.size() - 1]);
    for (unsigned int i = 0; i < points_.size() - 1; ++i) {
        double temp_length = DistanceBetween(points_[i], points_[i+1]);
        if (! EqualSides(temp_length, length)) return false;
    }
    return true;
}


bool Polygon::HasAllEqualAngles() {
    // Check the first angle and the final angle:
    double angle_begin = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle_end = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (! EqualAngles(angle_begin, angle_end)) return false;
    for (unsigned int i = 0; i < points_.size() - 2; ++i) {
        if ( ! EqualAngles(Angle(points_[i], points_[i+1], points_[i+2]), angle_begin)) return false;
    }
    return true;
}


bool Polygon::HasARightAngle() {
    // Check the first angle and the final angle:
    double angle_begin = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle_end = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (RightAngle(angle_begin) || RightAngle(angle_end)) return true;
    for(unsigned int i = 0; i < points_.size()-2; i++){
        if (RightAngle(Angle(points_[i], points_[i+1], points_[i+2]))) return true;
    }
    return false;
}

bool Polygon::HasAnObtuseAngle() {
    // Check the first angle and the final angle:
    double angle_begin = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle_end = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (ObtuseAngle(angle_begin)) return true;
    if (ObtuseAngle(angle_end)) return true;
    for(unsigned int i = 0; i < points_.size()-2; i++){
        if (ObtuseAngle(Angle(points_[i], points_[i+1], points_[i+2]))) return true;
    }
    return false;
}


bool Polygon::HasAnAcuteAngle() {
    // Check the first angle and the final angle:
    double angle_begin = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle_end = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (AcuteAngle(angle_begin)) return true;
    if (AcuteAngle(angle_end)) return true;
    for(unsigned int i = 0; i < points_.size()-2; i++){
        if (AcuteAngle(Angle(points_[i], points_[i+1], points_[i+2]))) return true;
    }
    return false;
}


bool Polygon::IsConcave() {
    // Check the first angle and the final angle:
    double angle_begin = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle_end = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (ReflexAngle(angle_begin)) return true;
    if (ReflexAngle(angle_end)) return true;
    for(unsigned int i = 0; i < points_.size()-2; i++){
        if (ReflexAngle(Angle(points_[i], points_[i+1], points_[i+2]))) return true;
    }
    return false;
}

bool Polygon::IsConvex() {
    return (IsConcave() == false);
}


































