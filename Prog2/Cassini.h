#pragma once

#include <math.h>

namespace Prog2 {
    class Cassini {
    private:
        double a;
        double c;
    public:
        Cassini();
        Cassini(double a, double c);
        bool Set_Distance(double a);
        double Get_Distance();
        bool Set_Focal_Parameter(double c);
        double Get_Focal_Parameter();
        double Get_Center_Distance(double t);
        const char *Get_Shape_Type();
        double Get_Curvature_Radius(double t);
        double Get_Inflection_Points_Polar_Radius();
        double Get_Inflection_Points_Polar_Angle();
        char *Get_Equation();
    };
}