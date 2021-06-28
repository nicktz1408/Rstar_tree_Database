#include <vector>
using namespace std;

/**
** Class for Points represantation
**/
#define dimensions 2


class Point{
    public:
        double dim[dimensions];
        Point(){
            dim[0] = 0.0;
            dim[1] = 0.0;
        }
        Point(vector<double> aDim){
//            dim = aDim;
            for(int i =0;i<aDim.size();i++){
                dim[i] = aDim[i];
            }
        }
        double getCertainDim(int index){
            return dim[index];
        }

        vector<double> getDim() {
            vector<double> out(2);
            for(int i =0;i<coords.size();i++){
                dim[i] = out[i];
            }

            return out;
        }

        void setCoords(vector<double> coords){
            for(int i =0;i<coords.size();i++){
                dim[i] = coords[i];
            }
        }
};