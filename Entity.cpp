class Entity {
public:
    Entity(long long aId, double aLat, double aLng) {
        id = aId;
        lat = aLat;
        lng = aLng;
    }

    int getId() {
        return id;
    }

    double getLat() {
        return lat;
    }

    double getLng() {
        return lng;
    }

private:
    int id;
    double lat;
    double lng;
};
