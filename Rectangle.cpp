#ifndef RECTANGLE_CPP
#define RECTANGLE_CPP

#include "Point.cpp"

class Rectangle{
    public:
        Point a;
        Point b;
        Rectangle(){
            
        }
        Rectangle(Point x, Point y){
            a = x;
            b = y;
        }
        double getMargin(){
            double margin = 0.0;

            for(int i = 0; i < 1/*a.dim.size() - 1*/; i++) {
                margin += (b.dim[i + 1] - a.dim[i + 1]) * (b.dim[i] - a.dim[i]);
            }

            return margin;
        }
        double getArea(){
            double area = 1.0;

            for(int i = 0; i < 2/*a.dim.size()*/; i++) {
                area *= (b.dim[i] - a.dim[i]);
            }

            return area;
        }  
};
#endif