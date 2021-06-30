class Node;

#include <fstream>
#include <utility>
using namespace std;

#include "Rectangle.cpp"
#include "Node.cpp"
#include "Record.cpp"

#ifndef INDEXFILEUTILITIES_CPP
#define INDEXFILEUTILITIES_CPP

class IndexfileUtilities {
public:
    int nextId;
    IndexfileUtilities(){
        nextId = 1;
    }

    int newBlockIdWithEmptyNode(Rectangle &boundingBox, bool isLeafNode) {
        vector<pair<int, Rectangle>> rec(50);
        return newBlockID(boundingBox, isLeafNode, rec, false);
    }

    int newBlockID(Rectangle &boundingBox, bool isLeafNode, vector<pair<int, Rectangle>> &rec, bool shouldInit){
        Node newNode(boundingBox, isLeafNode, rec, -1, nextId, shouldInit);
        newNode.modifiedNode();

        return nextId++;
    }

    void modifiedBlockId(Node aNode, int id){
        fstream myfile;
        myfile.open ("indexfile.dat", ios::out | ios::binary);
        int blockStart = (id - 1) * (int)sizeof(Node);
        myfile.seekp(blockStart, ios::beg);
        myfile.write((char *) &aNode, sizeof(Node));
        myfile.close();
    }

    Node getNodeByBlockId(int id) {
        return getNodeByBlockIdHelper(id);
    }

    Record getRecordFromDatafile(int entityNumber){
       Record output;

       int blockNum = entityNumber >> 27;
       int recordNum = (entityNumber << 5) >> 5;
       ifstream myFile;
       myFile.open("datafile.dat",ios::out | ios::binary );

       int index = (32770 * (blockNum - 1)) + sizeof(Record)*(recordNum-1);
       myFile.seekg(index, myFile.beg);
       myFile.read((char *)&output, sizeof(Record));

       myFile.close();
       return output;
    }


    void updateBounds(Node *node, Rectangle newBoundingBox){
        node->boundingBox = newBoundingBox;
        int ndId = node->blockId;
        int prnId = node->parentId;

        if(prnId != 0){
            Node parentNode = this->getNodeByBlockId(prnId);
            for(int i=0;i<parentNode.capacity;i++){
                if(parentNode.rectangles[i].first == ndId){
                    parentNode.rectangles[i].second = newBoundingBox;
                    modifiedBlockId(parentNode, prnId);

                }
            }

        }
    }

private:
    Node getNodeByBlockIdHelper(int id) {
        ifstream myFile;
        
        myFile.open ("indexfile.dat", ios::out | ios::binary);
        int blockStart = (id - 1) * (int)sizeof(Node);
        myFile.seekg(blockStart, ios::beg);
        
        Node *node;
        node = new Node();


        myFile.read ((char*) node, sizeof (Node));

        myFile.close();
        return *node;
    }
};

#endif