#ifndef NODE_CPP
#define NODE_CPP


#include "Rectangle.cpp"
#include "IndexfileUtilities.cpp"
using namespace std;


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

        void addChild(int blockID){
            rectangles[capacity] = blockID;
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
#endif