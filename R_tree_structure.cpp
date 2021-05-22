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

class Node{
    int capacity;
    int blockId;
    bool isLeaf;
    vector<int> rectangles;
    Rectangle boundingBox;
    Node();
    Node(Rectangle bounding, bool isLeafNode, vector<int> rec){
        isLeaf = isLeafNode;
        rectangles = rec;
        boundingBox = bounding;
    }

    void addChild(int blockID){
        rectangles[capacity] = blockIDl;
        capacity++;
    }

    void modifiedNode(){
        IndexfileUtilities util();
        util.modifiedBlockId(*this, blockId);
    }
};
/**
class Node: BaseNode{

    Node(Point a, Point b) {
        Rectangle boundingBox(a, b);
        rectangles = vector <int>(M);
    }

    vector<int> rectangles;
    Rectangle boundingBox;
};



class NodeLeaf: BaseNode{
    NodeLeaf(Point a, Point b) {
        entities = vector <int>(M);
        Rectangle boundingBox(a, b);
    }

    vector <int> entities;
    Rectangle boundingBox;
};
**/

class IndexfileUtilities {
public:
    int nextId = 1;
    IndexfileUtilities();

    int newBlockID(Rectangle boundingBox, bool isLeafNode, vector<int> rec){
        fstream myfile;
        myfile.open ("indexfile.dat", ios::in | ios::out | ios::binary | ios::end);
        Node newNode(boundingBox, isLeafNode, rec);
        myfile.write((char *) &newNode, sizeof(Node));
        return nextId++;
    }

    void modifiedBlockId(Node aNode, int id){
        fstream myfile;
        myfile.open ("indexfile.dat", ios::in | ios::out | ios::binary);
        int blockStart = (id - 1) * sizeof(Node);
        myFile.seekp(blockStart, ios::beg);
        myfile.write((char *) &newNode, sizeof(Node));
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

private:
    Node getNodeByBlockIdHelper(int id) {
        fstream myfile;
        myfile.open ("indexfile.dat", ios::in | ios::out | ios::binary);
        int blockStart = (id - 1) * sizeof(Node);
        myFile.seekg(blockStart, ios::beg);
        
        Node node();

        myFile.read ((char*) &node, sizeof (Node));
        myFile.close();
        return node;
    }
};




class Rtree{
    public:
        Rtree(string filename){
            Node *root = NULL;
            fstream readFile;
            readFile.open(filename, ios::out |ios::binary);

            int currSizeInFile = 0;
            bool blockEnds = true;

            while(currSizeInBlock <= 32768) {
                if(blockEnds) {
                    currSizeInFile += 2;
                    blockEnds = false;
                }

                readFile.seekg(currSizeInFile);

                Record rec;
                readFile.read(&rec, sizeof(Record));

                double lan = rec.getLan();
                double lng = rec.getLong();
                Point p(lan, lng);
                int blockId = (currSizeInFile - 1) / 32770 + 1;
                int line = (currSizeInFile % 32770 - 2) / sizeof(Record) + 1;
                int entityNumber = getEntityNumber(blockId, line);

                insert(p, entityNumber);
                

                currSizeInFile += sizeof(Record);

                if(currSizeInBlock % 32770 == 0) {
                    blockEnds = true;
                }
            }

            for(Record rec : data) {
                insert(rec);
            }
        }

        int getEntityNumber(int blockId, int line) {
            int entityNumber = 0;
            entityNumber |= (blockId << 27);
            entityNumber |= line;

            return entityNumber;
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


arr

        void splitHeuristic(Node *node, Node *otherNode) {

        }

        void rangeQueryUtility(Node *node, Rectangle range, vector <Record> &data){
            IndexfileUtilities util();

            if(node->isLeaf){
                vector <int> indexData = node->rectangles;

                for(int entityNumber : indexData) {
                    Record record = util.getRecordFromDatafile(entityNumber);
                    
                    Point currPoint = new Point(record.getCoords()[0], record.getCoords[1]);

                    if(contains(currPoint, range)) {
                        data.push_back(record);
                    }
                }
            }

            for(int i=0;i<node->capacity;i++){
                int currChildBlockId = node->rectangles[i];

                Node *child = util.getNodeByBlockId();

                if(overlap(range, child->boundingBox)){
                    rangeQueryUtility(child, range, data);
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