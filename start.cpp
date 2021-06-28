#include "R_tree_structure.cpp"
#include "Database_Technology_Project.cpp"

#include <ctime>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std;

double EuclideanDistance(Point a, Point b){
    double result = 0;
    for(int i=0;i<dimension;i++){
        result += pow(a.dim[i] - b.dim[i], 2);
    }
    return result;
}


long long serialSearchRange(Rectangle rec){
    auto start = std::chrono::high_resolution_clock::now();
    fstream datafile;
    datafile.open("datafile.dat", ios::out | ios:: binary);


    vector<Record> records;
    Record *rec;
    rec = new Record();
    for(long long int posInDisk = 0; posInDisk <= 32770 * 5; ) {
        cout<<"Here"<<endl;
        if(posInDisk % 32770 == 0) { // reached startOfNextBlock
            temp = new short();
            datafile.read((char *) temp, sizeof(short));
            posInDisk += 2;
            continue;
        }
        datafile.read((char *) rec, sizeof(Record));
        records.push_back(*rec);
        posInDisk += sizeof(Record); // 32byte
    }

    Rtree tree;
    vector<Point> results;

    for(int i=0;i<results.size();i++){
        vector<double> coordsVector;
        coordsVector = rec->getCoords();

        Point p(coordsVector);
        
        if(tree.contains(p, rec)){
            results.push_back(p);
        }
    }
    datafile.close();
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

}

long long serialSearchKNN(Point p, int K){
    auto start = std::chrono::high_resolution_clock::now();
    fstream datafile;
    datafile.open("datafile.dat", ios::out | ios:: binary);
    vector<Record> records;
    Record *rec;
    rec = new Record();
    for(long long int posInDisk = 0; posInDisk <= 32770 * 5; ) {
        cout<<"Here"<<endl;
        if(posInDisk % 32770 == 0) { // reached startOfNextBlock
            temp = new short();
            datafile.read((char *) temp, sizeof(short));
            posInDisk += 2;
            continue;
        }
        datafile.read((char *) rec, sizeof(Record));
        records.push_back(*rec);
        posInDisk += sizeof(Record); // 32byte
    }

    Rtree tree;
    vector<Point> results(K);
    vector<double> distances;

    for(int i=0;i<results.size();i++){
        vector<double> coordsVector;
        coordsVector = rec->getCoords();

        Point p(coordsVector);
        
        
    }



    

    datafile.close();
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

}



int main() {
    using std::chrono::high_resolution_clock;
    

	




    DatafileLoader dl;
    
    Rtree myTree("datafile.dat");
    
    vector<double> dimensions1 = {-12.12312, 98.1231231};
    vector<double> dimensions2 = {-73.2134, 57.23423};
    Point point1(dimensions1);
    Point point2(dimensions2);

    
    Rectangle rectangle(point1, point2);
    vector<double> dimensions3 = {-10.8978432, 89.7623476};
    Point point3(dimensions3);

    auto start = std::chrono::high_resolution_clock::now();
    myTree.rangeQuery(rectangle);
    auto middle = std::chrono::high_resolution_clock::now();
    myTree.knnQuery(point3, 3);
    auto finish = std::chrono::high_resolution_clock::now();



    cout<<"The time of the Range Query is: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(middle-start).count()<<endl;
    cout<<"THe time of the K-Nearest-Neighbor is: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-middle).count()<<endl;

    



    return 0;
}