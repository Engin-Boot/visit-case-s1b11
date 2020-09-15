#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../catch.hpp"
#include "../SenderExtendedFunc/SenderExtHeader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//visitdataout1.txt is an empty file to which sender writes the data which is also printed to console AND this file is cleared once the workflow ends
TEST_CASE("when sender reads sensor data with all valid entries and manual data then it reconciles the sensor data, inserts the missed entries, writes to the txt file and prints the same to the console") 
{
     std::string filename = "test-data/visitdata1.csv";
     std::string manuallog = "test-data/manuallog2.csv";
     Sender::fetchValidateReconcileandPrintFootfallData(filename,manuallog);    
     std::ifstream fin1("OutputSenderTestData/reconciletest2.txt"); //testing file
     std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
     fin1.close();
     std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
     std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
     fin2.close();
    REQUIRE(testData == obtainedData);    
}

TEST_CASE("when sender reads both sensor  data with some invalid entries and manual data then it validates, reconciles the sensor data, inserts the missed entries, writes to the txt file and prints the same to the console") 
{
     std::string filename = "test-data/visitdata2.csv";
     std::string manuallog = "test-data/manuallog2.csv";
     Sender::fetchValidateReconcileandPrintFootfallData(filename,manuallog);    
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
     std::string filename = "test-data/invalidvisitdata1.csv";
     std::string manuallog = "test-data/manuallog2.csv";
     Sender::fetchValidateReconcileandPrintFootfallData(filename,manuallog);
    std::ifstream fin1("OutputSenderTestData/reconciletest2.txt"); //testing file
    std::string testData((std::istreambuf_iterator<char>(fin1)), std::istreambuf_iterator<char>());
    fin1.close();
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(testData == obtainedData);    
}

TEST_CASE("when sender reads non-existing sensor and existing manual data files then it prints file doesn't exist to the console") 
{
    std::string filename = "abc.csv";
     std::string manuallog = "test-data/manuallog2.csv";
     Sender::fetchValidateReconcileandPrintFootfallData(filename,manuallog);
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(obtainedData == "file doesn't exist");    
}

TEST_CASE("when sender reads existing sensor and non-existing manual data files then it prints file doesn't exist to the console") 
{
    std::string filename = "test-data/visitdata1.csv";
     std::string manuallog = "abc.csv";
     Sender::fetchValidateReconcileandPrintFootfallData(filename,manuallog);
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(obtainedData == "file doesn't exist");    
}

TEST_CASE("when sender reads non-existing sensor and manual data files then it prints file doesn't exist to the console") 
{
    std::string filename = "abc.csv";
     std::string manuallog = "test-data/xyz.csv";
     Sender::fetchValidateReconcileandPrintFootfallData(filename,manuallog);
    std::ifstream fin2("OutputSenderTestData/visitdataout1.txt"); // sender writes to  this
    std::string obtainedData((std::istreambuf_iterator<char>(fin2)), std::istreambuf_iterator<char>());
    fin2.close();
    REQUIRE(obtainedData == "file doesn't exist");    
}
