#include <algorithm>
#include <vector>
#include "Entity.cpp"



#define M 50
#define m 25

using namespace std;

/**
** Struct for Points represantation
**/
struct Point{
    double x;
    double y;
};

struct Index{
    int numOfBlock;
    int numOfLine;
}

/**
** Class for the Rectangles represantation
**/
class Rectangle{
    public:
        Point a;
        Point b;
        BaseNode *childNode;
        Rectangle();
        Rectangle(Point x, Point y){
            a = x;
            b = y;
        }
        
};

class BaseNode{
    BaseNode();
}

class Node: BaseNode{
    Node() {
        boundingBoxes = vector <Rectangle *>(M);
    }
    vector<Rectangle *> boundingBoxes;
}
class NodeLeaf: BaseNode{
    NodeLeaf() {
        arr = vector <Index>(M);
        points = (Point *) malloc(M*sizeof(Point));
    }

    vector<Index> arr;
    Point *points;
}


class Rtree{
    public:
        Rtree(){
            Node *root = NULL;
        }


        void insert(Entity newRecord){
            Node *currentNode = root;
            Point p((double) newRecord.getLan(), (double) newRecord.getLon());
            insertUtility(currentNode, p);
        }

        NodeLeaf *insertUtility(Node *node, Point p){
            for(int i=0;i<node.size();i++){
                if(contains(p, node->boundingBoxes[i])){
                    currentNode = node->boundingBoxes[i]->childNode;
                    i = 0;
                }
            }
        }


        vector<Entity> rangeQuery(double range);
        vector<Entity> knnQuery(int neighbors);




    private:
        Node *root;
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