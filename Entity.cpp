#include <string>
#include <vector>

using namespace std;

class Entity {
public:
    Entity(string aId, vector <string> aCoords) {
        id = aId;
        coords = aCoords;
    }

    string getId() {
        return id;
    }

    vector<string> getCoords() {
        return coords;
    }

    

private:
    string id;
    vector <string> coords;
};
