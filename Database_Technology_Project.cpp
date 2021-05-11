#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "Entity.cpp"
#include <string>

#define blockSize 32768


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
            ofstream myfile;
            myfile.open ("datafile.txt");

            int currSize = 0;

            int i = 2;
            myfile<<"Block 1"<<endl;
            for (xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling())
            {
                if(!(string(node->name())).compare("node")){
                    vector<string> latLon(2);
                    latLon[0] = string(node->first_attribute("lat")->value());
                    latLon[1] = string(node->first_attribute("lon")->value());
                    string id = string(node->first_attribute("id")->value());
                    Entity entity(id, latLon);
                    cout << "\nNode id =   " << node->first_attribute("id")->value();
                    cout << " Lat =   " << node->first_attribute("lat")->value();
                    cout << " Lon =   " << node->first_attribute("lon")->value();
                    currSize += latLon[0].length();// sizeof(latLon[0]);
                    currSize += latLon[1].length();
                    currSize += id.length();
                    //cout<<"The size of the id is:"<<sizeof(id)<<endl;
                    if(currSize > blockSize){
                        cout<<"The size of the block is "<<currSize<<endl;
                        currSize = 0;
                        currSize += sizeof(latLon[0]);
                        currSize += sizeof(latLon[1]);
                        currSize += sizeof(id);
                        myfile<<"Block "<<i<<endl;
                        i++;
                    }

                    myfile << string(node->first_attribute("id")->value())<< " "<<string(node->first_attribute("lat")->value())<<" "<<string(node->first_attribute("lon")->value())<<endl;
                    
                }
            }
            cout << "The number of records are " <<j<<endl;
        }

    private:
};





int main(){
    XMLReader r;
    r.getData();
    return 0;
}