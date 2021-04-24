#include <string>

using namespace std;

class Entity {
public:
    Entity(string aId, string aLat, string aLng) {
        id = aId;
        lat = aLat;
        lng = aLng;
    }

    string getId() {
        return id;
    }

    string getLat() {
        return lat;
    }

    string getLng() {
        return lng;
    }

private:
    string id;
    string lat;
    string lng;
};
