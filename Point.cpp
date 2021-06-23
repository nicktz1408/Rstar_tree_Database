#include <vector>
using namespace std;

/**
** Class for Points represantation
**/


class Point{
    public:
        double dim[2];
        Point(){
            
        }
        Point(vector<double> aDim){
//            dim = aDim;
            dim[0] = aDim[0];
            dim[1] = aDim[1];
        }
        double getCertainDim(int index){
            return dim[index];
        }
};