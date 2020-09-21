#include <stdio.h>
#include <string.h>

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
    
    const char *Cassini::Get_Shape_Type() {
        const char *s = new char[25];
        
        if (this->a == 0 && this->c == 0) {
           s = "point of origin";
        }
        if (this->a == 0 && this->c != 0) {
           s = "two points";
        }
        if (this->a != 0 && this->c == 0) {
           s = "circle";
        }
        if (this->a > 0 && this->a < this->c) {
           s = "two separate ovals";
        }
        if (this->a == this->c && this->a != 0 && this->c != 0) {
           s = "lemniscate";
        }
        if (this->c < this->a && this->a <= this->c * sqrt(2)) {
           s = "with inflection points";
        }
        if (this->a >= this->c * sqrt(2) && this->a != 0 && this->c != 0) {
           s = "oval";
        }
        return s;
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
    
    char *Cassini::Get_Equation() {
        const char *s1 = "(x ^ 2 + y ^ 2) ^ 2 - * (x ^ 2 - y ^ 2) = ";
        int l = strlen(s1) + 1;
        char num[20];
        
        snprintf(num, 20, "%.2f", 2 * pow(this->c, 2));
        l += strlen(num);
        snprintf(num, 20, "%.2f", pow(this->a, 4) - pow(this->c, 4));
        l += strlen(num);
        
        char *s = new char[l];
        
        if (this->c == 0) {
           snprintf(s, l, "(x ^ 2 + y ^ 2) ^ 2");
        }
        else {
           snprintf(s, l, "(x ^ 2 + y ^ 2) ^ 2 - %.2f * (x ^ 2 - y ^ 2)", 2 * pow(this->c, 2));
        }
        
        int k = strlen(s);
        
        if (this->a == this->c) {
           snprintf(s + k, l - k, " = 0");
        }
        else {
           snprintf(s + k, l - k, " = %.2f", pow(this->a, 4) - pow(this->c, 4));
        }
        return s;
    }
}
