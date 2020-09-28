#include<iostream>
#include<string>
#include "SenderHeader.h"

int main()
{
	//"test-data/visitdata2.csv" contains all the data in "test-data/visitdata1.csv" and all the newly added entries are invalid
	// so sender prints the data same as in visitdata1.csv after validating
    Sender::fetchValidateandPrintFootfallData("test-data/visitdata2.csv"); 
    return 0;
}
