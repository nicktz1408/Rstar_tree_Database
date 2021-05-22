#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>
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

vector<string> simple_tokenizer(string s)
{
    vector <string> splitString;
    stringstream ss(s);
    string word;
    while (ss >> word) {
        splitString.push_back(word);
    }
    return splitString;
}

struct Index{
    int numOfBlock;
    int numOfLine;
    Entity getData() {
        ofstream inFile;
        inFile.open ("indexfile.txt");
        string line;
        vector<string> sLine;
        bool found = false;
        while (getline(inFile, line) && !found){
            sLine = simple_tokenizer(line);
            if(atoi(sLine[1]) == numOfBlock){
                found = true;
                int i=0;
                while(i!=numOfLine){
                    getline(inFile, line);
                    i++; 
                }
                sLine = simple_tokenizer(line);
                vector<sring> coords;
                for(int i=1;i<sLine.size();i++){
                    coords.push_back(sLine[i]);
                }
                Entity en(line[0], coords);

            }
        }
        return en;
    }
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

    Node(Point a , Point b) {
        Rectangle boundingBox(a, b);
        rectangles = vector <int>(M);
    }

    vector<int> rectangles;
    Rectangle boundingBox;
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
        Rtree(vector <Record> data){
            Node *root = NULL;

            for(Entity ent : data) {
                insert(ent);
            }
        }


        void insert(Record newRecord){
            Node *currentNode = root;
            Point p((double) newRecord.getLan(), (double) newRecord.getLon());
            NodeLeaf *leaf = getLeafNode(currentNode, p);
            vector <NodeLeaf *> leafNodes(0);

            for(NodeLeaf *node : leafNodes) {
                splitNode(node);
            }
        }

        void getLeafNode(Node *node, Point p, vector <NodeLeaf *> &leafNodes){
            if(typeof(node) == NodeLeaf){
                leafNodes.push(node);
            }

            bool contains = false;
            
            for(int i=0;i<node.size();i++){
                if(contains(p, node->boundingBoxes[i])){
                    contains = true;
                    currentNode = node->boundingBoxes[i]->childNode;

                    getLeafNode(currentNode, p, leafNodes);
                }
            }

            if(!contains) {
                Node *chosenChild = findChildHeuristic(node, p);
                getLeafNode(chosenChild);
            }
        }


        void splitNode(Node *aNode){
            if(aNode->boundingBoxes.size() == M) {
                Node *parent = aNode->getParent();
                Node *otherNode = new Node();

                splitHeuristic(aNode, otherNode);

                parent->boundingBoxes.push_back(otherNode);
                splitNode(parent);
            }
        }



    




        Node *findChildHeuristic(Node *parentNode, Point p) {
            return parentNode->boundingBoxes[0]->childNode;
        }

        void splitHeuristic(Node *node, Node *otherNode) {

        }

        void rangeQueryUtility(Node *node, Rectangle range, vector <Entity> &data){
            if(typeof(node) == NodeLeaf){
                vector <Index> indexData = node->arr;

                for(Index index : indexData) {
                    Entity entity = index.getData();
                    Point currPoint = new Point(entity.getCoords()[0], entity.getCoords[1]);

                    if(contains(currPoint, range)) {
                        data.push_back(entity);
                    }
                }
            }
            for(int i=0;i<M;i++){
                if(overlap(range, node->boundingBoxes[i])){
                    currentNode = node->boundingBoxes[i]->childNode;

                    rangeQueryUtility(currentNode, range, data);
                }
            }
        }


        vector<Entity> rangeQuery(Rectangle range){
            vector<Entity> answer;
            for(int i=0;i<M;i++){
                
            }

        }
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