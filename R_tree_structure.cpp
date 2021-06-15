#include <algorithm>
#include <vector>
#include <sstream>
#include <stack>
#include <fstream>
#include <utility>
#include <limits>
#include <cfloat>





#include "Record.cpp"
#include "Node.cpp"
#include "IndexfileUtilities.cpp"

#define M 50
#define m 25
#define dimension 2

using namespace std;



int rootId = 1;

/**
** Struct for Points represantation

struct Point{
    double x;
    double y;
};
**/


struct ABLinformation{
    double minDist;
    double minMaxDist;
    int index;
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
    Record getData() {
        fstream inFile;
        inFile.open ("indexfile.txt");
        string line;
        vector<string> sLine;
        bool found = false;
        while (getline(inFile, line) && !found){
            sLine = simple_tokenizer(line);
            if(stoi(sLine[1]) == numOfBlock){
                found = true;
                int i=0;
                while(i!=numOfLine){
                    getline(inFile, line);
                    i++; 
                }
                sLine = simple_tokenizer(line);
                vector<double> coords;
                for(int i=1;i<sLine.size();i++){
                    coords.push_back(stod(sLine[i]));
                }
                Record en(line[0], coords);
                return en;
            }
        }
        
    }
};

/**
** Class for the Rectangles represantation
**/
/**
class Node{
    int capacity;
    int parentId;
    int blockId;
    bool isLeaf;
    vector<pair<int, Rectangle>> rectangles;
    Rectangle boundingBox;
    Node();
    Node(Rectangle bounding, bool isLeafNode, vector<pair<int, Rectangles>> rec){
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
    void updateBoundingBox(Rectangle rec){
        boundingBox = rec;
        IndexfileUtilities util();
        updateBounds(this, boundingBox);
    }

};
**/
/**
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
**/



/**
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
**/




class Rtree{
    public:

        IndexfileUtilities *util;
        Rtree(string filename){
            util = new IndexfileUtilities();




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


        void insert(Point p, int entNum){
            Node *root = util.getNodeByBlockId(rootId);
            vector <Node *> leafNodes(0);
            Node *leaf = getLeafNode(root, p, leafNodes);
            

            for(Node *node : leafNodes) {
                splitNode(node);
            }
        }


    
        Rectangle calculateNewBound(Point p, Rectangle rec){
            Rectangle newRectangle;
            pair<int, int> a, b;

            newRectangle.a.x = min(p.x, rec.a.x);
            newRectangle.b.x = max(p.x, rec.b.x);

            newRectangle.a.y = min(p.y, rec.a.y);
            newRectangle.a.y = max(p.y, rec.b.y);

            return newRectangle;
            
        }




        double calculateOverlap(Rectangle a, Rectangle b){
            double overlap = 0;

            Point firstPoint, secondPoint;
            firstPoint.x = max(a.a.x, b.a.x);
            firstPoint.y = max(a.a.y, b.a.y);

            secondPoint.x = min(a.b.x, b.b.x);
            secondPoint.y = min(a.b.y, b.b.y);
            
            overlap = max(secondPoint.x - firstPoint.x, 0.0) * max(secondPoint.y - firstPoint.y, 0.0);


            return overlap;
        }



    
        Node* findChildHeuristic(Node node, Point p){
            Node childNode = util->getNodeByBlockId(node.rectangles[0].first);
            int minIndexRec = 0;
            if(childNode.isLeaf){
                vector<pair<int, Rectangle>> allRec = node.rectangles;
                double minOverlap = DBL_MAX;
                for(int i=0;i<node.capacity;i++){
                    double sum = 0;
                    Rectangle extendedRec = calculateNewBound(p, allRec[i]);
                    for(int j=0;j<node.capacity;j++){
                        if(i!=j){
                            sum +=  calculateOverlap(extendedRec, allRec[j].second);
                        }
                    }
                    if(sum < minOverlap){
                        minOverlap = sum;
                        minIndexRec = i;
                    }
                    
                }

            }else{
                vector<pair<int, Rectangle>> allRec = node.rectangles;
                double minOverlap = calculateOverlap(allRec);
                for(int i=0;i<node.capacity;i++){
                    double sum = 0;
                    Rectangle extendedRec = calculateNewBound(p, allRec[i]);
                
                    if(calculateOverlap(extendedRec, allRec[i]) < minOverlap){
                        minOverlap = sum;
                        minIndexRec = i;
                    }
                    
                }
            }
            
            Node *nextNode = util.getNodeByBlockId(node.rectangles[minIndexRec].first);
            return nextNode;
        }






        void getLeafNode(Node *node, Point p, vector <Node *> &leafNodes){
            if(node->isLeaf){
                leafNodes.push_back(node);
            }

            bool contains = false;
            
            for(int i=0;i<node->capacity;i++){
                if(contains(p, node->rectangles[i].second)){
                    contains = true;
                    int childId = node->rectangles[i].first;
                    Node currentNode = util->getNodeByBlockId(childId);

                    getLeafNode(currentNode, p, leafNodes);
                }
            }

            if(!contains) {
                Node *chosenChild = findChildHeuristic(node, p);
                getLeafNode(chosenChild, p, leafNodes);
            }
        }


          void splitNode(Node *aNode){
            if(aNode->capacity == M+1) {
                pair<vector<pair<int, Rectangle>>, vector<pair<int ,Rectangle>>> a = splitHeuristic(aNode);
                vector<pair<int, Rectangle>> fir = a.first;
                vector<pair<int, Rectangle>> sec = a.second;


                aNode->rectangles = fir;
                aNode->modifiedNode();

                
                int otherNodeId = util->newBlockID(constructBig(sec),aNode->isLeaf, sec);
                Node *otherNode = util->getNodeByBlockId(otherNodeId);

                int parentId = aNode->parentId;
                if(parentId == -1){
                    rootId = util->newBlockID(constructBig(sec),aNode->isLeaf, sec);
                    Node *rootNode = util->getNodeByBlockId(rootId);
                    rootNode->addChild(aNode->blockId);
                    rootNode->addChild(otherNodeId);
                    rootNode->modifiedNode();
                }else{
                    Node *parentNode = util->getNodeByBlockId(parentId);
                    parentNode->addChild(otherNodeId);
                    parentNode->modifiedNode();
                    splitNode(parentNode);
                }
            } 
        }


        Rectangle constructBig(vector <pair<int, Rectangle>> groupOfRectangles){
            Rectangle out = groupOfRectangles[0].second;
            for(int i=1;i<groupOfRectangles.size();i++){
                out = calculateNewBound(groupOfRectangles[i].second.a, out);
                out = calculateNewBound(groupOfRectangles[i].second.b, out);
            }
            return out;
        }

        double marginHeuristic(vector <pair<int, Rectangle>> g1, vector<pair<int, Rectangle>> g2){
            double margin1, margin2;

            margin1 = constructBig(g1).getMargin();
            margin2 = constructBig(g2).getMargin();

            return margin1 + margin2;
        }

        double areaHeuristic(vector <pair<int, Rectangle>> g1, vector<pair<int ,Rectangle>> g2){
            double area1, area2;

            area1 = constructBig(g1).getArea();
            area2 = constructBig(g2).getArea();

            return area1 + area2;
        }


        pair<vector<pair< int, Rectangle>>, vector<pair<int ,Reactangle>>> ChooseSplitIndex(vector<pair<int, Rectangle>> recs, int axis){
            sort(recs.begin(), recs.end(), [](pair<int, Rectangle> &lhs, pair<int, Rectangle> &rhs)
                {
                    if(axis==0){
                        if(lhs.second.a.x == rhs.second.a.x){
                            return lhs.second.b.x < rhs.second.b.x;
                        }
                        return lhs.second.a.x < rhs.second.a.x;
                    }
                    if(axis==1){
                        if(lhs.second.a.y == rhs.second.a.y){
                            return lhs.second.b.y < rhs.second.b.y;
                        }
                        return lhs.second.a.y < rhs.second.a.y;
                    }
                });
                vector<pair<int, Rectangle>> minGroup1, minGroup2;
                double minCost = DBL_MAX;
                int k = 1;
                while(m-1+k < M){
                    vector<pair<int, Rectangle>> group1, group2;
                    int i;
                    for(i=0;i<m-1+k;i++){
                        group1.push_back(recs[i]);
                    }
                    for(;i<recs.size();i++){
                        group2.push_back(recs[i]);
                    }
                    int currCost = areaHeuristic(group1, group2);
        
                    if(currCost < minCost){
                        minCost = currCost;
                        minGroup1 = group1;
                        minGroup2 = group2;
                    }
                }
            pair<vector<pair<int,Rectangle>>, vector<pair<int,Rectangle>>> out;
            out.first = minGroup1;
            out.second = minGroup2;
            return out;
        }



        int ChooseSplitAxis(vector<pair<int, Rectangle>> recs){
            int minAxis;
            double minCost = DBL_MAX;
            for(int axis = 0;axis < dimension; axis++){
                sort(recs.begin(), recs.end(), [](pair<int, Rectangle> &lhs, pair<int, Rectangle> &rhs)
                {
                    if(axis==0){
                        if(lhs.second.a.x == rhs.second.a.x){
                            return lhs.second.b.x < rhs.second.b.x;
                        }
                        return lhs.second.a.x < rhs.second.a.x;
                    }
                    if(axis==1){
                        if(lhs.second.a.y == rhs.second.a.y){
                            return lhs.second.b.y < rhs.second.b.y;
                        }
                        return lhs.second.a.y < rhs.second.a.y;
                    }
                });
                
                double totalCost = 0;
                int k = 1;
                while(m-1+k < M){
                    vector<pair<int, Rectangle>> group1, group2;
                    int i;
                    for(i=0;i<m-1+k;i++){
                        group1.push_back(recs[i]);
                    }
                    for(;i<recs.size();i++){
                        group2.push_back(recs[i]);
                    }
                    totalCost += marginHeuristic(group1, group2);
                    
                }
                
                if(currCost < minCost){
                    minCost = currCost;
                    minAxis = axis;
                }
            }
            return minAxis;
        }
        



        pair<vector<pair<int, Rectangle>>, vector<pair<int, Rectangle>>> splitHeuristic(Node *node) {
            int axis = ChooseSplitAxis(node->rectangles);
            return ChooseSplitIndex(node->rectangles, axis);

        }



        void rangeQueryUtility(int blockId, Rectangle range, vector <Record> &data){
            IndexfileUtilities util();
            Node *node = util.getNodeByBlockId(blockId);

            if(node->isLeaf){
                vector<pair<int, Rectangle>> indexData = node->rectangles;

                for(pair<int, Rectangle> entity : indexData) {
                    Record record = util.getRecordFromDatafile(entity.first);
                    
                    Point currPoint = new Point(record.getCoords()[0], record.getCoords[1]);

                    if(contains(currPoint, range)) {
                        data.push_back(record);
                    }
                }
            }

            for(int i=0;i<node->capacity;i++){
                pair<int, Rectangle> currChildBlock = node->rectangles[i];

                if(overlap(range, currChildBlock.second)){
                    rangeQueryUtility(currChildBlock.first, range, data);
                }
            }
        }



        
        vector<Record> rangeQuery(Rectangle range){
            vector<Record> answer;
            rangeQueryUtility(rootId, range, answer);
            return answer;
        }

        vector<struct ABLinformation> combine(vector<struct ABLinformation> &a, vector<struct ABLinformation> &b){
            vector<struct ABLinformation> merged;
            for(int i=0;i<a.size(), i++;){
                merged.push_back(a[i]);
                merged.push_back(b[i]);
            }
            sort(merged.begin(), merged.end()[](struct ABLinformation &lhs, struct ABLinformation &rhs)
            {
                 return lhs.minMaxDist < rhs.minMaxDist;
            });
            merged.resize(a.size());
            return merged;
        }


        vector<ABLinformation> knnQueryUtility(int blockId, Point point, int K){
            IndexfileUtilities util();
            Node *node = util.getNodeByBlockId(blockId);


            if(node->isLeaf){
                double nearestDist = DBL_MAX;
                vector<pair<double, Rectangle>> output;

                for(int i=0;i<node->capacity;i++){
                    double dist = MinMaxDistance(node->rectangles[i].second, point);
                    
                    output.push_back({ dist, node->rectangles[i].second });
                }
                sort(output.begin(), output.end());
                output.resize(K);
                return output;
            }else{
                vector<struct ABLinformation> ablInfo = getABLinformation(node, point);
                vector<struct ABLinformation> ablFiltered;
                double cutoff = ablInfo[0].minMaxDist;
                copy_if (ablInfo.begin(), ablInfo.end(), back_inserter(ablFiltered), [](struct ABLinformation abl){return abl.minDistance <= cutoff;} );

                vector<struct ABLinformation> answer;
                for(int i=0;i<ablFiltered.size();i++){
                    vector<struct ABLinformation> currPq = dfs(ablFiltered[i], node->rectangles[ablFiltered[i].index].first);
                    answer = combine(answer, currPq);
                    int maxFromAll = answer[K-1].getMin;
                    vector<struct ABLinformation> tempAnswer;
                    copy_if (answer.begin(), answer.end(), back_inserter(tempAnswer), [](struct ABLinformation abl){return abl.minDistance <= maxFromAll;} );
                    answer = tempAnswer;
                    
                }
                return answer;

            }

            
        }

        vector<struct ABLinformation> getABLinformation(Node *node, Point point){
            vector<struct ABLinformation> output;
            for(int i=0;i<node->capacity;i++){
                struct abl{MinDistance(node->rectangles[i], point), MinMaxDistance(node->rectangles[i], point), i};
                /**
                abl.minDist = MinDistance(node->rectangles[i], point);
                abl.minMaxDist = MinMaxDistance(node->rectangles[i], point);
                abl.index = i;
                **/
                output.push_back(abl);
            }
            sort(output.begin(), output.end(),[](struct ABLinformation &lhs, struct ABLinformation &rhs)
            {
                 return lhs.minMaxDist < rhs.minMaxDist;
            });
            return ouput;
        }

    


        
        vector<pair<double, Rectangle>> knnQuery(Rectangle point, int K){
            return knnQueryUtility(rootId, point.a,  K);
        }

        //In this function we check if two rectangles overlapping
        bool overlap(Rectangle rec1, Rectangle rec2){
            return (max(rec1.a.x, rec2.a.x) <= min(rec1.b.x, rec2.b.x) && max(rec1.a.y, rec2.a.y) <= min(rec1.b.y, rec2.b.y));
        }


        //In this function we check if a point contains in a rectangle
        bool contains(Point point, Rectangle rec){
            return ((point.x >= rec.a.x && point.x <= rec.b.x) && (point.y >= rec.a.y && point.y <= rec.b.y));
        }




    private:
        Node *root;
        


        
        double MinDistance(Rectangle rec, Point point){
            double totalDistance = 0;
            for(int i=0;i<point.dim.size();i++){
                int from = rec.a.dim[i];
                int to = rec.b.dim[i];
                int curr = point.dim[i];

                if(curr < from){
                    totalDistance += pow(from - curr, 2);
                }else if(curr > to){
                    totalDistance += pow(to - curr, 2);
                }
            }
            return totalDistance;
        }

        double MinMaxDistance(Rectangle rec, Point point){
            double minDistance = 0;
            for(int i=0;i<point.dim.size();i++){
                double currDistance = 0;
                double from = rec.a.dim[i];
                double to = rec.b.dim[i];
                double curr = point.dim[i];

                currDistance += min(pow(from - curr, 2), pow(to - curr, 2));

                for(int j=0;j<point.dim.size();j++){
                    if(i!=j){
                        from = rec.a.dim[j];
                        to = rec.b.dim[j];
                        curr = point.dim[j];
                        currDistance += max(pow(from - curr, 2), pow(to - curr, 2));
                    }
                    
                }



                minDistance = min(minDistance, currDistance);
            }
            return minDistance;
        }


};


int main(){
    return 0;
}