#include <stdio.h>

#include "Cassini.h"

namespace Prog2 {
    Cassini::Cassini() {
        this->a = 0;
        this->c = 0;
    }
    
    Cassini::Cassini(double a, double c) {
        if (a >= 0) {
           this->a = a;
        }
        else {
           this->a = 0;
        }
        if (c >= 0) {
           this->c = c;
        }
        else {
           this->c = 0;
        }
    }
    
    bool Cassini::Set_Distance(double a) {
        if (a < 0) {
           return false;
        }
        this->a = a;
        return true;
    }
    
    double Cassini::Get_Distance() {
        return this->a;
    }
    
    bool Cassini::Set_Focal_Parameter(double c) {
        if (c < 0) {
           return false;
        }
        this->c = c;
        return true;
    }
    
    double Cassini::Get_Focal_Parameter() {
        return this->c;
    }
    
    double Cassini::Get_Center_Distance(double t) {
        t = 2 * t * M_PI / 180;
        if ((pow(this->c, 4) * pow(cos(t), 2) + pow(this->a, 4) - pow(this->c, 4)) >= 0) {
           return fabs(pow(this->c, 2) * cos(t) + sqrt(pow(this->c, 4) * pow(cos(t), 2) + pow(this->a, 4) - pow(this->c, 4)));
        }
        else {
           return -1;
        }
    }
    
    std::string Cassini::Get_Shape_Type() {    
        if (this->a == 0 && this->c == 0) {
           return "point of origin";
        }
        if (this->a == 0 && this->c != 0) {
           return "two points";
        }
        if (this->a != 0 && this->c == 0) {
           return "circle";
        }
        if (this->a > 0 && this->a < this->c) {
           return "two separate ovals";
        }
        if (this->a == this->c && this->a != 0 && this->c != 0) {
           return "lemniscate";
        }
        if (this->c < this->a && this->a <= this->c * sqrt(2)) {
           return "with inflection points";
        }
        if (this->a >= this->c * sqrt(2) && this->a != 0 && this->c != 0) {
           return "oval";
        }
        return "";
    }
    
    double Cassini::Get_Curvature_Radius(double t) {
        t = 2 * t * M_PI / 180;
        if ((pow(this->c, 4) * pow(cos(t), 2) + pow(this->a, 4) - pow(this->c, 4)) >= 0) {
           double r = fabs(pow(this->c, 2) * cos(t) + sqrt(pow(this->c, 4) * pow(cos(t), 2) + pow(this->a, 4) - pow(this->c, 4)));
           if (r > 0) {
              return pow(this->a, 2) * r / (pow(r, 2) + cos(t) * pow(this->c, 2));
           }
           else {
              return -2;
           }
        }
        else {
           return -1;
        }
    }
    
    double Cassini::Get_Inflection_Points_Polar_Radius() {  
        return pow(((pow(this->a, 4) - pow(this->c, 4)) / 3), 0.25);
    }
    
    double Cassini::Get_Inflection_Points_Polar_Angle() {
        return acos((-1) * sqrt((pow((this->a / this->c), 4) - 1) / 3)) * 180 / (2 * M_PI);
    }
    
    std::string Cassini::Get_Equation() {
        if (this->a == 0 && this->c == 0) {
           return "(x ^ 2 + y ^ 2) ^ 2 = 0";
        }
        else {
           std::stringstream ss;
           if (this->a == 0) {
              ss << "(x ^ 2 + y ^ 2) ^ 2 - " << 2 * pow(this->c, 2) << " (x ^ 2 - y ^ 2) = " << (-1) * pow(this->c, 4);
           }
           else if (this->c == 0) {
              ss << "(x ^ 2 + y ^ 2) ^ 2 = " << pow(this->a, 4);
           }
           else {
              ss << "(x ^ 2 + y ^ 2) ^ 2 - " << 2 * pow(this->c, 2) << " * (x ^ 2 - y ^ 2) = " << pow(this->a, 4) - pow(this->c, 4);
           }
           return ss.str();
        }
    }
}