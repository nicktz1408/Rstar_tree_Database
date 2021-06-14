

class Rectangle{
    public:
        Point a;
        Point b;
        Rectangle();
        Rectangle(Point x, Point y){
            a = x;
            b = y;
        }
        double getMargin(){
            return 2*(b.x - a.x) + 2*(b.y - a.y);
        }
        double getArea(){
            return (b.x - a.x)*(b.y - a.y);
        }  
};