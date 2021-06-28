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

vector <Record> getAllRecords() {
    fstream datafile;
    datafile.open("datafile.dat", ios::out | ios:: binary);
    vector<Record> records;
    Record *rec;
    rec = new Record();

    short *temp;

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

    datafile.close();

    return records;
}

long long serialSearchRange(Rectangle rec){
    auto start = std::chrono::high_resolution_clock::now();
    vector <Record> records = getAllRecords();

    Rtree tree;
    vector<Point> results;

    for(int i=0;i<results.size();i++){
        Point p(records[i].getCoords());
        
        if(tree.contains(p, rec)){
            results.push_back(p);
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
}

long long serialSearchKNN(Point p, int K){
    auto start = std::chrono::high_resolution_clock::now();
    vector <Record> records = getAllRecords();

    sort(records.begin(), records.end(), [p] (Record &lhs, Record &rhs) {
        Point p1(lhs.getCoords()), p2(rhs.getCoords());

        return EuclideanDistance(p1, p) < EuclideanDistance(p2, p);
    });

    records.resize(K);

    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
}

void analyzeData() {
    vector <Record> records = getAllRecords();

    cout << "Total # of records: " << records.size() << endl;

    double minLat = -210.0, maxLat = 210.0, sumLat = 0.0;
    double minLng = -210.0, maxLng = 210.0, sumLng = 0.0;

    for(int i = 0; i < records.size(); i++) {
        minLat = min(minLat, records[i].getCoords()[0]);
        minLng = min(minLng, records[i].getCoords()[1]);

        maxLat = max(maxLat, records[i].getCoords()[0]);
        maxLng = max(maxLng, records[i].getCoords()[1]);

        sumLat += records[i].getCoords()[0];
        sumLng += records[i].getCoords()[1];
    }

    cout << "Lat: " << minLat << " " << maxLat << " " << sumLat / records.size() << endl;
    cout << "Lng: " << minLng << " " << maxLng << " " << sumLng / records.size() << endl;
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

    // (5, 10) (5, 10)
    // (4, 9) (6, 11)
    // (2, 7) (8, 13)

    auto start = std::chrono::high_resolution_clock::now();
    myTree.rangeQuery(rectangle);
    auto middle = std::chrono::high_resolution_clock::now();
    myTree.knnQuery(point3, 3);
    auto finish = std::chrono::high_resolution_clock::now();

    for(int k = 1; k <= 50; k++) {
        auto start = std::chrono::high_resolution_clock::now();
        myTree.knnQuery(point3, k);
        auto finish = std::chrono::high_resolution_clock::now();

        long long serialTime = serialSearchKNN(point3, k);
    }





    cout<<"The time of the Range Query is: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(middle-start).count()<<endl;
    cout<<"THe time of the K-Nearest-Neighbor is: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-middle).count()<<endl;

    



    return 0;
}