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
            for(int i = 0; i < dimensions; i++) {
                dim[i] = 0.0;
            }
        }
        Point(vector<double> aDim){
            for(int i =0;i<aDim.size();i++){
                dim[i] = aDim[i];
            }
        }
        double getCertainDim(int index){
            return dim[index];
        }

        vector<double> getDim() {
            vector<double> out(dimensions);
            for(int i =0;i<out.size();i++){
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