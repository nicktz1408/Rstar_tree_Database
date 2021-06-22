#include <vector>

using namespace std;

#ifndef RECORD_CPP
#define RECORD_CPP

class Record{
public:
    
    Record(){
        
    }

    Record(long long aId, vector <double> aCoords) {
        id = aId;
        coords[0] = aCoords[0];
        coords[1] = aCoords[1];
    }

    long long getId() {
        return id;
    }

    vector<double> getCoords() {

        return {coords[0], coords[1]};
    }


private:
    long long id;
    double coords[2];

    
};
#endif