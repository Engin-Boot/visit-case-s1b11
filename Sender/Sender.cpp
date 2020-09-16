#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include<sstream>
#include <algorithm>
#include "SenderHeader.h"

std::vector<std::vector<std::string>> CSVReader::fetchActualFootfallData()
{
    std::fstream file;
    std::vector<std::vector<std::string>> footfallData;
    std::string line = "";
    std::string data = "";
	
    // Iterate through each line and split the content using delimeter
	
    file.open(fileName);
    getline(file,line);
    while (getline(file, line))
    {
        std::stringstream str(line);

        std::vector<std::string> footfallEntry; //one footfall data
        while (getline(str, data, ','))
        {
            // add all the column data of a row to a vector footfallEntry
            footfallEntry.push_back(data);
        }
        footfallData.push_back(footfallEntry);
     }
    file.close();
    return footfallData;
}

bool isnumber(std::string s)
{
    for (unsigned int i = 0; i < s.length(); i++)
	if (isdigit(s[i]) == false)
		return false;

    return true;    
}

std::vector<int> getValidRow(std::vector<std::string>& rowvec)
{
	std::vector<int> validRow;
	for (std::string data : rowvec)
       	{
            	if(isnumber(data)==true)
		validRow.push_back(stoi(data));
        }
	return validRow;
}


std::vector<std::vector<int>> removeInvalidEntries(std::vector<std::vector<std::string>>& actualdata)
{
	std::vector<std::vector<int>> validdata;
	for(std::vector<std::string> vec:actualdata)
	{
		std::vector<int> ValidRow = getValidRow(vec);
	if(ValidRow.size()==8)
		validdata.push_back(ValidRow);
	}
	return validdata;
}

void printValiddata(std::vector<std::vector<int>> &data)
{
    std::cout<<"id,hour,minute,second,day,date,month,year"<<std::endl;
      for (std::vector<int> vec : data)
    {
        for (int rowdata : vec)
        {
            std::cout << rowdata << ",";
        }
        std::cout << std::endl; 
     }
}

bool is_file_exists(std::string filename)
{
	std::ifstream infile(filename);
    return infile.good();	
}

void Sender::fetchValidateandPrintFootfallData(std::string filename)
{	
   if(is_file_exists(filename)==true)
   {
	// Creating an object of CSVfile reader
	CSVReader filereader(filename,",");
        // Get the data from CSV File
        std::vector<std::vector<std::string>> actualdata  = filereader.fetchActualFootfallData();
        std::vector<std::vector<int>> validData  = removeInvalidEntries(actualdata); //removes rows containing empty data or junk values(like character strings) or negative numbers
        // Print the content
        // data is now only non-negative integer because person id, date, time are non negative integers
        int halfofFetchedEntriesfromSensorData = actualdata.size()/2;
        int totalValidEntries = validData.size();
   	if(totalValidEntries < halfofFetchedEntriesfromSensorData)
		std::cout<<"No valid data"<<std::endl;
	else
    		printValiddata(validData);
   }
	else
   {
		std::cout<<"File doesn't exist"<<std::endl;
	  
   }
}

int main()
{
	//"test-data/visitdata2.csv" contains all the data in "test-data/visitdata1.csv" and all the newly added entries are invalid
	// so sender prints the data same as in visitdata1.csv after validating
    Sender::fetchValidateandPrintFootfallData("test-data/visitdata2.csv"); 
    return 0;
}
