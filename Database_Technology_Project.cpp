#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "Entity.cpp"


using namespace std;
using namespace rapidxml;



class XMLReader{
    public:
        XMLReader(){
            cout << "XML parser created!";
        }
        ~XMLReader(){
            cout << "XML parser destroyed!";
        }


        void getData(){
            xml_document<> doc;
            xml_node<> * root_node = NULL;
            ifstream theFile("map.osm");
            vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
            buffer.push_back('\0');
        
            doc.parse<0>(&buffer[0]);
        
            root_node = doc.first_node("osm");
            
            for (xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling())
            {
                if(!(string(node->name())).compare("node")){
                    Entity entity(node->first_attribute("id")->value(), node->first_attribute("lat")->value(), node->first_attribute("lon")->value());
                    cout << "\nNode id =   " << node->first_attribute("id")->value();
                    cout << " Lat =   " << node->first_attribute("lat")->value();
                    cout << " Lon =   " << node->first_attribute("lon")->value();
                    cout << endl;
                }
            }
        }




    private:
};





int main(){
    XMLReader r;
    r.getData();
    return 0;
}