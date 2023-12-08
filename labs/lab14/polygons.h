#ifndef POLYGONS_H
#define POLYGONS_H

#include <string>
#include <vector>
#include "utilities.h"  // Assuming this file contains necessary utility functions

class Polygon {
public:
    Polygon(const std::string& name, const std::vector<Point>& vertices) {
        // throw int if vertices.size() == 0 otherwise set vertices
        if (vertices.size() == 0) {
            throw 1;
        } else {
            this->vertices = vertices;
            this->name = name;
        }
    }

    const std::string& getName() const {
        return name;
    }
    virtual ~Polygon() {}

    const bool HasAllEqualSides() const {
        // check if all sides are equal
        for (int i = 0; i < vertices.size() - 1; i++) {
            if (!EqualSides(DistanceBetween(vertices[i], vertices[i+1]), DistanceBetween(vertices[i+1], vertices[i+2]))) {
                return false;
            }
        }
        return true;
    }

protected:
    std::vector<Point> vertices;
    std::string name;
};

class Triangle : public Polygon {
public:
    Triangle(const std::string& name, const std::vector<Point>& vertices) : Polygon(name, vertices) {
        // trhow int if vertices.size() != 3 otherwise set vertices
        if (vertices.size() != 3) {
            throw 1;
        }
    }
};

class Quadrilateral : public Polygon {
public:
    Quadrilateral(const std::string& name, const std::vector<Point>& vertices) : Polygon(name, vertices) {
        // throw int if vertices.size() != 4 otherwise set vertices
        if (vertices.size() != 4) {
            throw 1;
        }
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(const std::string& name, const std::vector<Point>& vertices) : Triangle(name, vertices) {
        // throw int if ver otherwise set vertices
        double side1 = DistanceBetween(vertices[0], vertices[1]);
        double side2 = DistanceBetween(vertices[1], vertices[2]);
        double side3 = DistanceBetween(vertices[2], vertices[0]);
        // two sides equal 3rd side doesnt matter
        if (EqualSides(side1, side2)) {

        }
        else if (EqualSides(side2, side3)) {
            
        }
        else if (EqualSides(side3, side1)) {
            
        }
        else {
            throw 1;
        }
    }
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle(const std::string& name, const std::vector<Point>& vertices) : IsoscelesTriangle(name, vertices) {
        // throw int if vertices.size() != 3 otherwise set vertices
        double side1 = DistanceBetween(vertices[0], vertices[1]);
        double side2 = DistanceBetween(vertices[1], vertices[2]);
        double side3 = DistanceBetween(vertices[2], vertices[0]);
        // check all sides are equal
        if (EqualSides(side1, side2) && EqualSides(side2, side3) && EqualSides(side3, side1)) {
            
        } else {
            throw 1;
        }     
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(const std::string& name, const std::vector<Point>& vertices) : Quadrilateral(name, vertices) {
        // throw int if vertices.size() != 4 otherwise set vertices
        double side1 = DistanceBetween(vertices[0], vertices[1]);
        double side2 = DistanceBetween(vertices[1], vertices[2]);
        double side3 = DistanceBetween(vertices[2], vertices[3]);
        double side4 = DistanceBetween(vertices[3], vertices[0]);

        // check 90 degree angles
        double angle1 = Angle(vertices[0], vertices[1], vertices[2]);
        double angle2 = Angle(vertices[1], vertices[2], vertices[3]);
        double angle3 = Angle(vertices[2], vertices[3], vertices[0]);
        double angle4 = Angle(vertices[3], vertices[0], vertices[1]);

        if (!EqualSides(side1, side3) && !EqualSides(side2, side4) && !RightAngle(angle1) && !RightAngle(angle2) && !RightAngle(angle3) && !RightAngle(angle4)) {
            throw 1;
        }
    }
};

class Square : public Rectangle {
public:
    Square(const std::string& name, const std::vector<Point>& vertices) : Rectangle(name, vertices) {
        // throw int if vertices.size() != 4 otherwise set vertices
        double side1 = DistanceBetween(vertices[0], vertices[1]);
        double side2 = DistanceBetween(vertices[1], vertices[2]);
        double side3 = DistanceBetween(vertices[2], vertices[3]);
        double side4 = DistanceBetween(vertices[3], vertices[0]);

        if (!EqualSides(side1, side2) && !EqualSides(side2, side3) && !EqualSides(side3, side4) && !EqualSides(side4, side1)) {
            throw 1;
        }
    }
};

#endif // POLYGONS_H
