#include <utility>
using namespace std;

#include "Rectangle.cpp"
#include "IndexFileUtilities.cpp"

class Node{
public:
    int capacity;
    int parentId;
    int blockId;
    bool isLeaf;
    vector<pair<int, Rectangle>> rectangles;
    Rectangle boundingBox;
    Node();
    Node(Rectangle bounding, bool isLeafNode, vector<pair<int, Rectangle>> rec){
        isLeaf = isLeafNode;
        rectangles = rec;
        boundingBox = bounding;
    }

    void addChild(int blockId){
        rectangles[capacity] = blockId;
        capacity++;
    }

    void modifiedNode(){
        IndexfileUtilities util();
        util.modifiedBlockId(*this, blockId);
    }
    void updateBoundingBox(Rectangle rec){
        boundingBox = rec;
        IndexfileUtilities util();
        updateBounds(this, boundingBox);
    }

};
