#include <vector>
#include <utility>
#include <fstream>
using namespace std;

#include "Rectangle.cpp"

#ifndef NODE_CPP
#define NODE_CPP

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

        void updateBounds(Rectangle aBoundingBox) {
            boundingBox = aBoundingBox;
        }

        void addChild(int blockID, Rectangle rec){
            rectangles[capacity] = { blockID, rec };
            capacity++;
        }

        void modifiedNode(){
            fstream myfile;
            myfile.open ("indexfile.dat", ios::in | ios::out | ios::binary);

            int blockStart = (blockId - 1) * sizeof(Node);
            myfile.seekp(blockStart, ios::beg);
            myfile.write((char *) this, sizeof(Node));
        }
        void updateBoundingBox(Rectangle rec){
            updateBounds(boundingBox);
            modifiedNode();
        }

};
#endif