#include <vector>
using namespace std;

/**
** Class for Points represantation
**/


class Point{
    public:
        vector<double> dim;
        Point(){
            
        }
        Point(vector<double> aDim){
            dim = aDim;
        }
        double getCertainDim(int index){
            return dim[index];
        }
};