#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "Record.cpp"
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
            myfile.open ("datafile.dat", ios::out | ios::binary);

            int currSize = 0;

            short int i = 1;
            myfile.write((char *) &i, sizeof(short));
            i++;
            for (xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling())
            {
                if(!(string(node->name())).compare("node")){
                    vector<double> latLon(2);
                    latLon[0] = strtod(node->first_attribute("lat")->value(), NULL);
                    latLon[1] = strtod(node->first_attribute("lon")->value(), NULL);
                    long long id = atoll(node->first_attribute("id")->value());
                    Record record(id, latLon);
                
                    /**
                    cout << "\nNode id =   " << node->first_attribute("id")->value();
                    cout << " Lat =   " << node->first_attribute("lat")->value();
                    cout << " Lon =   " << node->first_attribute("lon")->value();
                    **/

                    currSize += sizeof(record);
                    
                    if(currSize > blockSize){
                        cout<<"The size of the block is "<<currSize<<endl;
                        currSize = 0;
                        currSize += sizeof(record);
                        
                        myfile.write((char *) &i, sizeof(short));
                        i++;
                    }

                    myfile.write((char *) &record, sizeof(Record));
                    
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