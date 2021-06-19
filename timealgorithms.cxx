#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "json.hpp"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

using namespace std;

//Time measurement class.
class Time{
private:
        chrono::high_resolution_clock::time_point start, end;
public:
    void Reset(){
        start = chrono::high_resolution_clock::now();
    }
    double Current(){
        auto end = chrono::high_resolution_clock::now();
        double elapsed_us = chrono::duration<double, micro>(end - start).count();
        return elapsed_us;
    }
};

int main(int argc, char** argv) {
    // Reading file, store contents to jsonObject.
    ifstream jsonStream(argv[1]);
    nlohmann::json jsonObject;
    if (jsonStream.is_open()) {
        jsonStream >> jsonObject;
    }
    
    //printing the title of CSV output.
    cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << endl;
    // Get arraySize & numSamples from "metadata" for iterating.
    int arraySize = jsonObject["metadata"]["arraySize"];
    int numSamples = jsonObject["metadata"]["numSamples"];
    // Fistly transfer value_array to value_vector,
    // Since Functions only receive vector as parameter.
    for(int i = 1; i <= numSamples; i++){
        
        vector<int> valueVector;
        vector<int> valueVector2;
        vector<int> valueVector3;
        
        string sampleNum;
        // Again creat sampleNum...differece"01"&"10".
        if(i >= 10){
            sampleNum = "Sample" + to_string(i);
        }
        else{
            sampleNum = "Sample0" + to_string(i);
        }
        // The inner for-loop is just for convert array to vector.
        for(int j = 0; j < arraySize; j++){
            valueVector.push_back(jsonObject[sampleNum][j]);
        }
        for(int j = 0; j < arraySize; j++){
            valueVector2.push_back(jsonObject[sampleNum][j]);
        }
        for(int j = 0; j < arraySize; j++){
            valueVector3.push_back(jsonObject[sampleNum][j]);
        }
        
        Time ct;
        
        int InsertionSortCompares = 0;
        int InsertionSortMemaccess = 0;
        ct.Reset();
        InsertionSort(&valueVector, InsertionSortCompares, InsertionSortMemaccess);
        double InsertionSortTime = ct.Current();
        
        int MergeSortCompares = 0;
        int MergeSortMemaccess = 0;
        ct.Reset();
        MergeSort(&valueVector2, MergeSortCompares, MergeSortMemaccess);
        double MergeSortTime = ct.Current();
        
        int QuickSortCompares = 0;
        int QuickSortMemaccess = 0;
        ct.Reset();
        QuickSort(&valueVector3, QuickSortCompares, QuickSortMemaccess);
        double QuickSortTime = ct.Current();
        
        cout << sampleNum << "," << InsertionSortTime << "," << InsertionSortCompares << "," << InsertionSortMemaccess << "," << MergeSortTime << "," << MergeSortCompares << "," << MergeSortMemaccess << "," << QuickSortTime << "," << QuickSortCompares << "," << QuickSortMemaccess << endl;
    }
    return 0;
}
