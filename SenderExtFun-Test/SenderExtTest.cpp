#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../catch.hpp"
#include "../SenderExtendedFunc/SenderExtHeader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

TEST_CASE("when sender reads both sensor and manual data then it reconciles the sensor data, inserts the missed entries, writes to the txt file and prints the same to the console") 
{
     Sender::fetchValidateReconcileandPrintFootfallData("test-data/visitdata2.csv","test-data/manuallog2.csv");
     
    std::ifstream fin1("OutputSenderTestData/reconciletest2.txt"); //testing file
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(testData == obtainedData);    
}

TEST_CASE("when sender reads both sensor and manual data and sensor data has more invalid entries then it takes only manual data assuming that sensor is malfunctioning, writes to the txt file and prints the same to the console") 
{
     Sender::fetchValidateReconcileandPrintFootfallData("test-data/invalidvisitdata1.csv","test-data/manuallog2.csv");
     
    std::ifstream fin1("OutputSenderTestData/reconciletest2.txt"); //testing file
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(testData == obtainedData);    
}

TEST_CASE("when sender reads both sensor and manual data and either of them are not existing files then it file doesn't exist to the console") 
{
     Sender::fetchValidateReconcileandPrintFootfallData("abc.csv","test-data/xyz.csv");
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(obtainedData == "file doesn't exist");    
}
