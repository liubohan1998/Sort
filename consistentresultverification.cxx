#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using namespace std;

int main(int argc, char** argv) {
    // Read input JSON file, save content to jsonObject.
    ifstream jsonStream1(argv[1]);
    nlohmann::json jsonObject_1;
    if (jsonStream1.is_open()) {
        jsonStream1 >> jsonObject_1;
    }

    ifstream jsonStream2(argv[2]);
    nlohmann::json jsonObject_2;
    if (jsonStream2.is_open()) {
        jsonStream2 >> jsonObject_2;
    }

    // def jsonOutput: empty JSON object.
    nlohmann::json jsonOutput = nlohmann::json::object();
    
    int arraySize1 = jsonObject_1["metadata"]["arraySize"];
    int numSamples1 = jsonObject_1["metadata"]["numSamples"];
    
    int arraySize2 = jsonObject_2["metadata"]["arraySize"];
    int numSamples2 = jsonObject_2["metadata"]["numSamples"];
    
    string fileAddress1 = (string)argv[1];
    string fileAddress2 = (string)argv[2];
    
    int numMismatchesSample = 0; // this is how many samples have Mismatches.

    //jsonIterator is a key & value pair in jsonObject.
    for(int i = 1; i <= numSamples1; i++){
        
        int numInverInArray = 0;
        // in order to difference "Sample01, Sample02, ..." and "Sample10".
        string sampleNum1;
        string sampleNum2;
        if(i >= 10){ //"Sample10"
            sampleNum1 = "Sample" +  to_string(i);
            sampleNum2 = "Sample" +  to_string(i);
        }
        else{ //"Sample01, Sample02, ..."
            sampleNum1 = "Sample0" + to_string(i);
            sampleNum2 = "Sample0" + to_string(i);
        }


        for(int j = 0; j < arraySize1; j++){
            //in current value, if the present array int does not equal the one in another file, we output it, and notes that numMismatches+=1.
            if (jsonObject_1[sampleNum1][j] != jsonObject_2[sampleNum2][j]){
                //def outputKey: Key().
                string outputKey = to_string(j);
                //def outputValue: Value(), a user-def array.
                //add content to outputValue.
                nlohmann::json outputValue = nlohmann::json::array();
                outputValue.push_back(jsonObject_1[sampleNum1][j]);
                outputValue.push_back(jsonObject_2[sampleNum2][j]);

                jsonOutput[sampleNum1]["Mismatches"];
                // complete jsonOutput with Key(outputKey) & Value(outputValue).
                jsonOutput[sampleNum1]["Mismatches"][outputKey] = outputValue;
                
                numInverInArray++;
            }
        }
        
        if(numInverInArray > 0){
            numMismatchesSample++;
        }
        
        jsonOutput[sampleNum1][fileAddress1] = jsonObject_1[sampleNum1];
        jsonOutput[sampleNum2][fileAddress2] = jsonObject_2[sampleNum2];

    }

    //complete jsonOutput's metadata.
    jsonOutput["metadata"]["File1"] = jsonObject_1["metadata"];
    jsonOutput["metadata"]["File1"]["name"] = fileAddress1;

    jsonOutput["metadata"]["File2"] = jsonObject_2["metadata"];
    jsonOutput["metadata"]["File2"]["name"] = fileAddress2;

    jsonOutput["metadata"]["samplesWithConflictingResults"] = numMismatchesSample;
    //and output jsonOutput
    cout << jsonOutput.dump(2) << endl;
    return 0;
}

