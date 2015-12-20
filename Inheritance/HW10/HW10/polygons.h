#include <iostream>
#include <string>
#include <vector>
#include "useful.h"
#include "utilities.h"
using namespace std;

class Polygon {
public:
    
    Polygon(const std::string &name, const std::vector<Point> &points): name_(name), points_(points) {
        if (! IS_A_Polygon(points)) throw 1;
    }
    virtual string getName() const { return name_; }
    // Member functions:
    //---------------------------------------------------
    virtual bool HasAllEqualSides();
    virtual bool HasAllEqualAngles();
    virtual bool HasARightAngle();
    virtual bool HasAnObtuseAngle();
    virtual bool HasAnAcuteAngle();
    virtual bool IsConvex();
    virtual bool IsConcave();
    //---------------------------------------------------
    virtual ~Polygon(){}
protected:
    std::string name_;
    std::vector<Point> points_;
    
};


// ----------------------------------------------------------------
// Triangles
// ----------------------------------------------------------------

class Triangle : public Polygon {
public:
    Triangle(const std::string &name, const std::vector<Point> &points): Polygon(name, points) {
        if (points.size() != 3) throw 1;
    }
    // Avoid unnecessary codes
    virtual bool HasAnAcuteAngle() { return true;  }
    virtual bool IsConvex() { return true; }
    virtual bool IsConcave() { return false; }
};

class RightTriangle : virtual public Triangle {
public:
    RightTriangle(const std::string &name, const std::vector<Point> &points) : Triangle(name, points) {
        if (points.size() != 3) throw 1;
        if ( ! Is_a_RightTriangle(points) ) throw 1;
    }
    virtual bool HasAllEqualSides() { return false; }
    virtual bool HasAllEqualAngles() { return false; }
    virtual bool HasARightAngle() { return true; }
    virtual bool HasAnObtuseAngle() { return false; }
    
};



class IsoscelesTriangle : virtual public Triangle {
public:
    IsoscelesTriangle(const std::string &name, const std::vector<Point> &points) : Triangle(name, points) {
        if (points.size() != 3) throw 1;
        if (! Is_a_IsoscelesTriangle(points)) throw 1;
    }
};


class ObtuseTriangle : virtual public Triangle {
public:
    ObtuseTriangle(const std::string & name, const std::vector<Point> & points) : Triangle(name, points){
        if (points.size()!= 3) throw 1;
        if (! Is_A_ObtuseTriangle(points)) throw 1;
    }
    virtual bool HasAllEqualSides() { return false; }
    virtual bool HasAllEqualAngles() { return false; }
    virtual bool HasARightAngle(){return false;}
    virtual bool HasAnObtuseAngle() { return true; }
};


class IsoscelesRightTriangle : public RightTriangle, public IsoscelesTriangle {
public:
    IsoscelesRightTriangle(const std::string & name, const std::vector<Point> & points) : Triangle(name, points),
    RightTriangle(name, points), IsoscelesTriangle(name, points) {
       if (points.size() != 3) throw 1;
        // If it is has no right angle and it is not a Isosceles Triangle, then it can't be
        // Isosceles Right Triangle.
        if (! Is_a_RightTriangle(points) || ! Is_a_IsoscelesTriangle(points)) throw 1;
    }
};



class IsoscelesObtuseTriangle : public IsoscelesTriangle, public ObtuseTriangle {
public:
    IsoscelesObtuseTriangle(const std::string & name, const std::vector<Point> & points) : Triangle(name, points),
    IsoscelesTriangle(name, points), ObtuseTriangle(name, points) {
        if (points.size() != 3) throw 1;
        if (!Is_a_IsoscelesTriangle(points) || ! Is_A_ObtuseTriangle(points)) throw 1;
    }
};


class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle(const std::string & name, const std::vector<Point> & points) :Triangle(name, points), IsoscelesTriangle(name, points) {
        if (points.size() !=3) throw 1;
        if (! Is_A_EquilateralTriangle(points)) throw 1;
    }
    virtual bool HasAllEqualSides() { return true; }
    // This is true for Triangles
    virtual bool HasAllEqualAngles() { return true; }
    virtual bool HasARightAngle() { return false; }
    virtual bool AnObtuseAngle() { return false; }
    
};



// ----------------------------------------------------------------
// Quadrilateral
// ----------------------------------------------------------------

class Quadrilateral : public Polygon {
public:
    Quadrilateral(const std::string & name, const std::vector<Point> & points) : Polygon(name, points) {
        if (points.size() != 4) throw 1;
    }
};

class Trapezoid : virtual public Quadrilateral {
public:
    Trapezoid(const std::string & name, const std::vector<Point> & points) : Quadrilateral(name, points) {
        if (points.size() != 4) throw 1;
        if (!Is_A_Trapezoid(points)) throw 1;
    }
    virtual bool IsConvex() { return true;}
    virtual bool IsConcave() { return false;}
};

class IsoscelesTrapezoid : virtual public Trapezoid {
public:
    IsoscelesTrapezoid(const std::string & name, const std::vector<Point> & points) : Quadrilateral(name, points),
    Trapezoid(name, points) {
        if (points.size() != 4) throw 1;
        if (!Is_A_IsoscelesTrapezoid(points)) throw 1;
    }
};


class Parallelogram : virtual public Trapezoid {
public:
    Parallelogram(const std::string & name, const std::vector<Point> & points) : Quadrilateral(name, points),
    Trapezoid(name, points) {
        if (points.size() != 4) throw 1;
        if (!Is_A_Parallelogram(points)) throw 1;
    }
};

class Rectangle : public IsoscelesTrapezoid, virtual public Parallelogram {
public:
    Rectangle(const std::string & name, const std::vector<Point> & points) :
    Quadrilateral(name, points), Trapezoid(name, points), IsoscelesTrapezoid(name, points),
    Parallelogram(name, points) {
        if (points.size() != 4) throw 1;
        if (!Is_A_Rectangle(points)) throw 1;
    }
    virtual bool HasAllEqualAngles() { return true; }
    virtual bool HasARightAngle() { return true; }
    virtual bool HasAnObtuseAngle(){ return false; }
    virtual bool HasAnAcuteAngle(){ return false; }
};


class Kite : virtual public Quadrilateral {
public:
    Kite(const std::string &name, const std::vector<Point> &points) : Quadrilateral(name, points) {
        if (points.size() != 4) throw 1;
        if (!Is_A_Kite(points)) throw 1;
    }

};

class Rhombus : virtual public Parallelogram, public Kite {
public:
    Rhombus(const std::string &name, const std::vector<Point> &points) :
      Quadrilateral(name, points), Trapezoid(name, points), Parallelogram(name, points), Kite(name,points)
    {
        if (points.size() != 4) throw 1;
        if (! Is_A_Rhombus(points)) throw 1;
        
    }
    virtual bool HasAllEqualSides() { return true; }
    virtual bool IsConvex(){return true;}
    virtual bool IsConcave(){return false;}
};


class Square : public Rectangle, public Rhombus {
public:
    Square(const std::string &name, const std::vector<Point> &points)
    : Quadrilateral(name, points), Trapezoid(name,points), Parallelogram(name, points), Rectangle(name, points)
    , Rhombus(name, points) {
        if (points.size() != 4) throw 1;
        if (! Is_A_Rhombus(points)) throw 1;
        if (! Is_A_Rectangle(points)) throw 1;
    }
};

class Arrow : public Quadrilateral {
public:
    Arrow(const std::string &name, const std::vector<Point> &points)
    : Quadrilateral(name, points) {
        if (points.size() != 4) throw 1;
//        if (IsConvex()) throw 1;
//        if (!Is_A_Kite(points)) throw 1;
        if (! Is_A_Arrow(points)) throw 1;
    }
    virtual bool IsConvex(){return false;}
    virtual bool IsConcave(){return true;}
};
































