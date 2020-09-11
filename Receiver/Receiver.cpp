#include "ReceiverHeader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

Receiver::Receiver() {}

Receiver::Receiver(int d, int m, int y, float ha) : date(d), month(m), year(y), hourlyAverage(ha) {}

Receiver::Receiver(int dy, int dt, int m, int y, float wa) : day(dy), date(dt), month(m), year(y), weeklyAverage(wa) {}

Receiver::Receiver(int i, int hr, int min, int sec, int dy, int dt, int mon, int yr) : id(i), hour(hr), minute(min), second(sec), day(dy), date(dt), month(mon), year(yr) {}

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
	cout << footfallRecord.size() << endl;
	Receiver receiverObj(footfallRecord[0], footfallRecord[1], footfallRecord[2], footfallRecord[3], footfallRecord[4], footfallRecord[5], footfallRecord[6], footfallRecord[7]);
	footfallData.push_back(receiverObj);
}

void Receiver::averageFootfallsPerHourDaily()
{
	/*ofstream fout("test-data/Average Hourly Footfalls Daily.csv", ios::app);
	if(fout.is_open())
	{
		cout << "File created" << endl;
		fout << "11" << ", " << "123" << ", " << "45" <<"\n";
	}
	fout.close();*/
	vector<Receiver> hourlyAverageDailyData;
	Receiver receiverObj(footfallData[0].date, footfallData[0].month, footfallData[0].year, 0);
	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(receiverObj.date == footfallData[i].date)
		{
			receiverObj.hourlyAverage += 1;
		}
		else
		{
			receiverObj.hourlyAverage = receiverObj.hourlyAverage / 4;
			hourlyAverageDailyData.push_back(receiverObj);
			receiverObj.date = footfallData[i].date;
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.hourlyAverage = 0;
			i--;
		}
	}
	receiverObj.hourlyAverage = receiverObj.hourlyAverage / 4;
	hourlyAverageDailyData.push_back(receiverObj);
	
	displayHourlyAverageDailyData(hourlyAverageDailyData);
}

int Receiver::setFlagStatus(int day)
{
	if(day == 1)
		return 0;
	return 1;
}

void Receiver::averageDailyFootfallsWeekly()
{
	vector<Receiver> dailyAverageWeeklyData;
	Receiver receiverObj(footfallData[0].day, footfallData[0].date, footfallData[0].month, footfallData[0].year, 0);
	int flag = 0;

	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(footfallData[i].day != flag)
		{
			receiverObj.weeklyAverage += 1;
			flag = setFlagStatus(footfallData[i].day);
		}
		else
		{
			receiverObj.weeklyAverage = receiverObj.weeklyAverage / 7;
			dailyAverageWeeklyData.push_back(receiverObj);
			receiverObj.day = footfallData[i].day;
			receiverObj.date = footfallData[i].date;
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.weeklyAverage = 0;
			flag = 0;
			i--;	
		}
	}
	receiverObj.weeklyAverage = receiverObj.weeklyAverage / 7;
	dailyAverageWeeklyData.push_back(receiverObj);
	
	displayDailyAverageWeeklyData(dailyAverageWeeklyData);
}


void Receiver::displayHourlyAverageDailyData(vector<Receiver> hourlyAverageDailyData)
{
	cout<<"Date "<<"Month "<<"Year "<<" Hourly Avg"<<endl;
	for(unsigned int i = 0; i < hourlyAverageDailyData.size(); i++)
	{
		cout<<hourlyAverageDailyData[i].date<<" "<<hourlyAverageDailyData[i].month<<" "<<hourlyAverageDailyData[i].year<<" "<<hourlyAverageDailyData[i].hourlyAverage<<endl;
	}
}

void Receiver::displayDailyAverageWeeklyData(vector<Receiver> dailyAverageWeeklyData)
{
	cout<<"Date "<<"Month "<<"Year "<<" Weekly Avg"<<endl;
	for(unsigned int i = 0; i < dailyAverageWeeklyData.size(); i++)
	{
		cout<<dailyAverageWeeklyData[i].date<<" "<<dailyAverageWeeklyData[i].month<<" "<<dailyAverageWeeklyData[i].year<<" "<<dailyAverageWeeklyData[i].weeklyAverage<<endl;
	}
}

void Receiver::peakDailyFootfallLastMonth()
{
	vector<Receiver> dailyFootfallLastMonthData;
	vector<Receiver> footfallLastMonthData = getLastMonthFootfallData();
	Receiver receiverObj(footfallLastMonthData[0].date, footfallLastMonthData[0].month, footfallLastMonthData[0].year, 0);
	for(unsigned int i = 0; i < footfallLastMonthData.size(); i++)
	{
		if(receiverObj.date == footfallLastMonthData[i].date)
		{
			receiverObj.dailyCount += 1;
		}
		else
		{
			dailyFootfallLastMonthData.push_back(receiverObj);
			receiverObj.date = footfallData[i].date;
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.dailyCount = 0;
			i--;
		}
	}
	dailyFootfallLastMonthData.push_back(receiverObj);
	
	vector<Receiver> peakDailyFootfallsLastMonthData = getPeakDailyFootfallsLastMonth(dailyFootfallLastMonthData);
	
	displayPeakDailyFootfallLastMonth(peakDailyFootfallsLastMonthData);
}

vector<Receiver> Receiver::getLastMonthFootfallData()
{
	time_t currentTime = time(0);
	tm *localTime = localtime(&currentTime);
	int lastMonth = localTime->tm_mon;
	vector<Receiver> lastMonthFootfallData;
	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(lastMonth == footfallData[i].month)
		{
			lastMonthFootfallData.push_back(footfallData[i]);
		}
	}
	return lastMonthFootfallData;
}

vector<Receiver> Receiver::getPeakDailyFootfallsLastMonth(vector<Receiver> dailyFootfallLastMonthData)
{
	sort(dailyFootfallLastMonthData.begin(), dailyFootfallLastMonthData.end(), [](const Receiver& firstObj, const Receiver& secondObj)
	{
    		return firstObj.dailyCount > secondObj.dailyCount;
	});
	vector<Receiver> peakDailyFootfallsLastMonth;
	int peakCount = dailyFootfallLastMonthData[0].dailyCount;
	for(unsigned int i = 0; i < dailyFootfallLastMonthData.size(); i++)
	{
		if(peakCount == dailyFootfallLastMonthData[i].dailyCount)
		{
			peakDailyFootfallsLastMonth.push_back(dailyFootfallLastMonthData[i]);
		}
	}
	return peakDailyFootfallsLastMonth;
}

void Receiver::displayPeakDailyFootfallLastMonth(vector<Receiver> peakDailyFootfallsLastMonthData)
{
	cout<<"Date "<<"Month "<<"Year "<<"Peak Count"<<endl;
	for(unsigned int i = 0; i < peakDailyFootfallsLastMonthData.size(); i++)
	{
		cout<<peakDailyFootfallsLastMonthData[i].date<<" "<<peakDailyFootfallsLastMonthData[i].month<<" "<<peakDailyFootfallsLastMonthData[i].year<<" "<<peakDailyFootfallsLastMonthData[i].dailyCount<<endl;
	}
}

int main()
{
	Receiver receiverObj;
	
	cout << "In receiver main" << endl;
	
	receiverObj.readSenderData();
	receiverObj.averageFootfallsPerHourDaily();
	receiverObj.averageDailyFootfallsWeekly();
	receiverObj.peakDailyFootfallLastMonth();
	return 0;
}
