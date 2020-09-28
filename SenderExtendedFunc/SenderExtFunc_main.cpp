#include<iostream>
#include<vector>
#include<string>

#include "SenderExtHeader.h"

int main()
{
    	std::string filename = "test-data/visitdata2.csv";
	std::string manuallog = "test-data/manuallog2.csv";
	Sender::fetchValidateReconcileandPrintFootfallData(filename,manuallog);
    return 0;
}
