#include "ReceiverHeader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void Receiver::readSenderData()
{
	string footfallRecordString;
	getline(cin, footfallRecordString);
	cout << footfallRecordString << endl;
	while (getline(cin, footfallRecordString))
	{
		cout << footfallRecordString << endl;
		storeFootfallData(footfallRecordString);
	}
}

void Receiver::storeFootfallData(const string& footfallRecordString)
{
	vector<int> footfallRecord;
	string footfallElement;
	stringstream footfallStream(footfallRecordString);
	while (getline(footfallStream, footfallElement, ','))
	{
		footfallRecord.push_back(stoi(footfallElement));
	}
	cout << "Record Pushed" << endl;
	footfallData.push_back(footfallRecord);
}

int main()
{
	Receiver receiverObj;

	cout << "In receiver main" << endl;
	
	receiverObj.readSenderData();

	return 0;
}
