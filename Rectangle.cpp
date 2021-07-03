#ifndef RECTANGLE_CPP
#define RECTANGLE_CPP

#define dimensions 2

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

            for(int i = 0; i < dimensions-1; i++) {
                margin += (b.dim[i + 1] - a.dim[i + 1]) * (b.dim[i] - a.dim[i]);
            }

            return margin;
        }
        double getArea(){
            double area = 1.0;

            for(int i = 0; i < dimensions; i++) {
                area *= (b.dim[i] - a.dim[i]);
            }

            return area;
        }  
};
#endif