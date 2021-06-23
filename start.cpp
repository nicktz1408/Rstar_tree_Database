#include "R_tree_structure.cpp"
#include "Database_Technology_Project.cpp"

#include <ctime>
#include <chrono>

using namespace std;

int main() {
    using std::chrono::high_resolution_clock;




//    DatafileLoader dl;
    
    Rtree myTree("datafile.dat");
    
    // vector<double> dimensions1 = {-12.12312, 98.1231231};
    // vector<double> dimensions2 = {-73.2134, 57.23423};
    // Point point1(dimensions1);
    // Point point2(dimensions2);

    
    // Rectangle rectangle(point1, point2);
    // vector<double> dimensions3 = {-10.8978432, 89.7623476};
    // Point point3(dimensions3);

    // auto t1 = high_resolution_clock::now();
    // myTree.rangeQuery(rectangle);
    // auto t2 = high_resolution_clock::now();
    // myTree.knnQuery(point3, 3);
    // auto t3 = high_resolution_clock::now();


    /**
    vector<double> dimensions = {-20.23142342, -67.123123123};
    Point newPoint(dimensions);
    myTree.insert(newPoint, 100);
    cout<<"The insertion completed";
    **/

    return 0;
}