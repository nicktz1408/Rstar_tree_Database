#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "Record.cpp"
#include <string>

#define blockSize 32762

using namespace std;
using namespace rapidxml;

class XMLReader{
    public:
        XMLReader(){
            cout << "XML parser created!"<<endl;
        }
        ~XMLReader(){
            cout << "XML parser destroyed!"<<endl;
        }

        void getData(){
            int j = 1;
            xml_document<> doc;
            xml_node<> *root_node = NULL;
            ifstream theFile("map.osm");
            vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
            buffer.push_back('\0');
        
            doc.parse<0>(&buffer[0]);
        
            root_node = doc.first_node("osm");
            ofstream myfile;
            myfile.open("datafile.dat", ios::out | ios::binary);

            int currSize = 0;

            short int i = 1;
            myfile.write((char *) &i, sizeof(short));
            currSize += 2;
            i++;
            int cnt = 0;
            for (xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling())
            {
                
                if(node && string(node->name()) == "node"){
                    
                    vector<double> latLon(2);
                    latLon[0] = strtod(node->first_attribute("lat")->value(), NULL);
                    latLon[1] = strtod(node->first_attribute("lon")->value(), NULL);
                    long long id = atoll(node->first_attribute("id")->value());
                    Record record(id, latLon);

                    
                    currSize += sizeof(Record);
                    myfile.write((char *) &record, sizeof(Record));
                    
                    if(currSize == blockSize){
                        
                        cout<<"The size of the block is "<<currSize<<endl;
                    
                        currSize = 0;
                        
                        myfile.write((char *) &i, sizeof(short));
                        currSize += 2;
                        i++;
                    }
                   
                    
                }
            }
            cout << "Offset: " << currSize << endl;
            myfile.close();
           
        }
};

class DatafileLoader {
    public:
        DatafileLoader() {
            init();
        }

        void init() {
            XMLReader r;
            r.getData();
        }
};
