#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using namespace std;

int main(int argc, char** argv) {
    // Read input JSON file, save content to jsonObject.
    ifstream jsonStream(argv[1]);
    nlohmann::json jsonObject;
    if (jsonStream.is_open()) {
        jsonStream >> jsonObject;
    }
    
    // def jsonOutput: empty JSON object.
    nlohmann::json jsonOutput = nlohmann::json::object();
    int arraySize = jsonObject["metadata"]["arraySize"];
    int numSamples = jsonObject["metadata"]["numSamples"];
    int numInverSample = 0; // this is how many samples have Inversions.
    
    //jsonIterator is a key & value pair in jsonObject.
    //i =1, since sampleNum begins with 01.
    for(int i = 1; i <= numSamples; i++){
        int numInverInArray = 0; // this is how many Inversions in one sample.
        // in order to difference "Sample01, Sample02, ..." and "Sample10".
        string sampleNum;
        if(i >= 10){ //"Sample10"
            sampleNum = "Sample" + to_string(i);
        }
        else{ //"Sample01, Sample02, ..."
            sampleNum = "Sample0" + to_string(i);
        }
        for(int j = 0; j < arraySize - 1; j++){
            //in current value, if the present array int > the next one, we output it, and notes that numInver+=1.
            if (jsonObject[sampleNum][j] >= jsonObject[sampleNum][j+1]){
                //def outputKey: Key().
                string outputKey = to_string(j);
                //def outputValue: Value(), a user-def array.
                //add content to outputValue.
                nlohmann::json outputValue = nlohmann::json::array();
                outputValue.push_back(jsonObject[sampleNum][j]);
                outputValue.push_back(jsonObject[sampleNum][j+1]);
                
                jsonOutput[sampleNum]["ConsecutiveInversions"];
                // complete jsonOutput with Key(outputKey) & Value(outputValue).
                jsonOutput[sampleNum]["ConsecutiveInversions"][outputKey] = outputValue;
                
                numInverInArray++;
            }
        }
        // If there are more than 0 Inversions in a sample, so, the number of samplesWithInversions += 1.
        if(numInverInArray > 0){
            numInverSample++;
        }
        jsonOutput[sampleNum]["sample"] = jsonObject[sampleNum];
    }
    
    //complete jsonOutput's metadata.
    jsonOutput["metadata"] = jsonObject["metadata"];
    string fileAddress = (string)"../Examples/" + argv[1];
    jsonOutput["metadata"]["file"] = fileAddress;
    jsonOutput["metadata"]["samplesWithInversions"] = numInverSample;
    //and output jsonOutput
    cout << jsonOutput.dump(2) << endl;
    return 0;
}

