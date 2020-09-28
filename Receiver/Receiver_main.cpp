#include<iostream>
#include<vector>
#include<string>
#include "ReceiverHeader.h"

using namespace std;

int main()
{
	Receiver receiverObj;
	
	cout << "In receiver main" << endl;
	
	vector<Receiver> footfallData = receiverObj.readSenderData();
	
	if(footfallData.size() != 0) // if sender data is available
	{
		vector<Receiver> averageFootfallsPerHourDailyResult = receiverObj.averageFootfallsPerHourDaily(footfallData);
		receiverObj.displayHourlyAverageDailyData(averageFootfallsPerHourDailyResult);
	
		vector<Receiver> averageDailyFootfallsWeeklyResult = receiverObj.averageDailyFootfallsWeekly(footfallData);
		receiverObj.displayDailyAverageWeeklyData(averageDailyFootfallsWeeklyResult);
	
		vector<Receiver> peakDailyFootfallLastMonthResult = receiverObj.peakDailyFootfallLastMonth(footfallData);
		receiverObj.displayPeakDailyFootfallLastMonth(peakDailyFootfallLastMonthResult);
	}
	else
	{
		cout<<"No data."<<endl;
	}
	
	return 0;
}
