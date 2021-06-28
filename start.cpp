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
    ifstream datafile;
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

    double minLat = 210.0, maxLat = -210.0, sumLat = 0.0;
    double minLng = 210.0, maxLng = -210.0, sumLng = 0.0;

    for(int i = 0; i < records.size(); i++) {
        minLat = min(minLat, records[i].getCoords()[0]);
        minLng = min(minLng, records[i].getCoords()[1]);

        maxLat = max(maxLat, records[i].getCoords()[0]);
        maxLng = max(maxLng, records[i].getCoords()[1]);

        sumLat += records[i].getCoords()[0];
        sumLng += records[i].getCoords()[1];
    }
    cout << "Sum Lat: " << sumLat << endl;
    cout << "Sum Lng: " << sumLng << endl;
    cout << "Lat: " << minLat << " " << maxLat << " " << sumLat / records.size() << endl;
    cout << "Lng: " << minLng << " " << maxLng << " " << sumLng / records.size() << endl;
}
void printData(){
    vector <Record> records = getAllRecords();
    for(int i=0;i<records.size(); i++){
        cout << records[i].getCoords()[0]<<" "<< records[i].getCoords()[1]<<endl;
    }
}

int main() {
    using std::chrono::high_resolution_clock;

    DatafileLoader dl;
    
    Rtree myTree("datafile.dat");
    
    vector<double> dimensions1 = {40.7062, -74.0105};
    Point point1(dimensions1);
    Point point2(dimensions1);
    Point point3(dimensions1);

    
    vector<double> dimensions3 = {-10.8978432, 89.7623476};
    Point point3(dimensions3);


    

    for(int k = 1; k <= 50; k++) {
        auto start = std::chrono::high_resolution_clock::now();
        myTree.knnQuery(point3, k);
        auto finish = std::chrono::high_resolution_clock::now();

        long long serialTime = serialSearchKNN(point3, k);
        cout << k <<" "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count()<<" "<<serialTime<<endl;
    }





    for(int k = 1; k <= 50; k++) {
        vector<double> newCoords1 = {point1.getCoords()[0] - (40.7062 - 40.4335)*k / 50, point1.getCoords()[1] - (-74.0105 - (-74.0799))*k / 50};
        vector<double> newCoords2 = {point1.getCoords()[0] + (40.7766 - 40.7062)*k / 50, point1.getCoords()[1] - (-73.9613 - (-74.0105))*k / 50};

        point2.setCoords(newCoords1);
        point3.setCoords(newCoords2);
        Rectangle rectangle(point2, point3);
        auto start = std::chrono::high_resolution_clock::now();
        myTree.rangeQuery(rectangle);
        auto finish = std::chrono::high_resolution_clock::now();

        long long serialTime = serialSearchRange(rectangle);
        //cout << k <<" "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count()<<" "<<serialTime<<endl;
        

    }
    




    // cout<<"The time of the Range Query is: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(middle-start).count()<<endl;
    // cout<<"THe time of the K-Nearest-Neighbor is: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-middle).count()<<endl;

    



    return 0;
}