#include <fstream>
using namespace std;

#include "Rectangle.cpp"
#include "Node.cpp"
#include "Record.cpp"

class IndexfileUtilities {
public:
    int nextId = 1;
    IndexfileUtilities();

    int newBlockID(Rectangle boundingBox, bool isLeafNode, vector<pair<int, Rectangles>> rec){
        fstream myfile;
        myfile.open ("indexfile.dat", ios::in | ios::out | ios::binary | ios::end);
        Node newNode(boundingBox, isLeafNode, rec);
        myfile.write((char *) &newNode, sizeof(Node));
        return nextId++;
    }

    void modifiedBlockId(Node *updateNode, int id){
        fstream myFile;
        myFile.open ("indexfile.dat", ios::in | ios::out | ios::binary);

        int blockStart = (id - 1) * sizeof(Node);
        myFile.seekp(blockStart, ios::beg);
        myFile.write((char *) updateNode, sizeof(Node));
    }

    Node getNodeByBlockId(int id) {
        return getNodeByBlockIdHelper(id);
    }

    Record getRecordFromDatafile(int entityNumber){
        Record output;

        int blockNum = entityNumber >> 27;
        int recordNum = (entityNumber << 5) >> 5;
        ifstream myFile;
        myFile.open("datafile.dat",ios::in | ios::binary );

        int index = (32770 * (blockNum - 1)) + sizeof(Record)*(recordNum-1);
        myFile.seekg(index, myFile.beg);
        myFile.read(output, sizeof(Record));

        myFile.close();
        return output;
    }


    void updateBounds(Node *node, Rectangle newBoundingBox){
        node->boundingBox = newBoundingBox;
        int ndId = node->blockId;
        int prnId = node->parentId;

        if(prnId != NULL){
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
        fstream myFile;
        myFile.open ("indexfile.dat", ios::in | ios::out | ios::binary);

        int blockStart = (id - 1) * sizeof(Node);
        myFile.seekg(blockStart, ios::beg);

        Node node;

        myFile.read ((char*) &node, sizeof (Node));
        myFile.close();

        return node;
    }
};