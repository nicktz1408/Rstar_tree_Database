#include <iostream>
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
        pair<int, Rectangle> rectangles[51];
        Rectangle boundingBox;
        Node(){
            initializeRectVector();
            capacity = 0;
            parentId = -1;
            blockId = -1;
            isLeaf = true;
        }
        Node(Rectangle bounding, bool isLeafNode, vector<pair<int, Rectangle>> rec, int aParentId, int aBlockId, bool shouldInit){
            initializeRectVector();
            isLeaf = isLeafNode;

            setRectangles(rec, shouldInit);

            boundingBox = bounding;
            parentId = aParentId;
            blockId = aBlockId;
        }

        void initializeRectVector() {
            for(int i = 0; i < 51; i++) {
                Point p({ 0, 0 });
                Rectangle rec(p, p);
                rectangles[i] = { 0, rec };
            }
        }

        void setRectangles(vector<pair<int, Rectangle>> &rec, bool shouldInit) {
            for(int i = 0; i < rec.size(); i++) {
                rectangles[i] = rec[i];
            }
            capacity = (shouldInit ? rec.size() : 0);

            for(int i = (int)rec.size(); i < 51; i++) {
                Point p({ 0, 0 });
                Rectangle rec(p, p);
                rectangles[i] = { 0, rec };
            }
        }

        vector<pair<int, Rectangle>> getRectangles() {
            vector<pair<int, Rectangle>> out(51);

            for(int i = 0; i < 51; i++) {
                out[i] = rectangles[i];
            }

            return out;
        }

        void updateBounds(Rectangle aBoundingBox) {
            boundingBox = aBoundingBox;
        }

        void addChild(int blockID, Rectangle rec){
            rectangles[capacity] = { blockID, rec };
            capacity++;
            

        }

        void modifiedNode(){
            ofstream myfile;
            myfile.open ("indexfile.dat", ios::out | ios::binary);

            int blockStart = (blockId - 1) * (int)sizeof(Node);
            myfile.seekp(blockStart, ios::beg);
            myfile.write((char *) this, sizeof(Node));
            myfile.close();
        }
        void updateBoundingBox(Rectangle rec){
            updateBounds(boundingBox);
            modifiedNode();
        }

};
#endif