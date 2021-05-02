#include <algorithm>
#include <vector>
#include "Entity.cpp"

using namespace std;

/**
** Struct for Points represantation
**/
struct Point{
    int x;
    int y;
};

/**
** Class for the Rectangles represantation
**/
class Rectangle{
    public:
        Point a;
        Point b;
        Rectangle();
        Rectangle(Point x, Point y){
            a = x;
            b = y;
        }
        
};


class Rtree{
    public:
        Rtree();
        void insert(Entity newRecord);
        vector<Entity> rangeQuery(double range);
        vector<Entity> knnQuery(int neighbors);




    private:
        //In this function we check if two rectangles overlapping
        bool overlap(Rectangle m, Rectangle n){
            return (max(m.a.x,n.a.x) <= min(m.b.x,n.b.x) && max(m.a.y,n.a.y) <= min(m.b.y,n.b.y));
        }


        //In this function we check if a point contains in a rectangle
        bool contains(Point m, Rectangle n){
            return ((m.x >= n.a.x && m.x <= n.b.x) && (m.y >= n.a.y && m.y <= n.b.y));
        }

};


int main(){
    return 0;
}