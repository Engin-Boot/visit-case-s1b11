#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "ReceiverHeader.h"

using namespace std;

Receiver::Receiver() {}

Receiver::Receiver(int d, int m, int y, float ha) : date(d), month(m), year(y), hourlyAverage(ha) {}

Receiver::Receiver(int dy, int dt, int m, int y, float wa) : day(dy), date(dt), month(m), year(y), weeklyAverage(wa) {}

Receiver::Receiver(int i, int hr, int min, int sec, int dy, int dt, int mon, int yr) : id(i), hour(hr), minute(min), second(sec), day(dy), date(dt), month(mon), year(yr) {}

// read footfall data printed on console by the Sender line by line and store footfall records in vector
vector<Receiver> Receiver::readSenderData()
{
	vector<Receiver> footfallData;
	string footfallRecordString;
	getline(cin, footfallRecordString);
	cout << footfallRecordString << endl; // print column headings
	while (getline(cin, footfallRecordString))
	{
		footfallData = storeFootfallData(footfallRecordString, footfallData);
	}
	return footfallData;
}

// split the footfall record into id, hour, minute, second, day, date, month, year - store into Receiver object and push object into vector
vector<Receiver> Receiver::storeFootfallData(const string& footfallRecordString, vector<Receiver> footfallData)
{
	vector<int> footfallRecord;
	string footfallElement;
	stringstream footfallStream(footfallRecordString);
	while (getline(footfallStream, footfallElement, ','))
	{
		footfallRecord.push_back(stoi(footfallElement));
	}
	
	Receiver receiverObj(footfallRecord[0], footfallRecord[1], footfallRecord[2], footfallRecord[3], footfallRecord[4], footfallRecord[5], footfallRecord[6], footfallRecord[7]);
	footfallData.push_back(receiverObj);
	return footfallData;
}

// calculate average footfalls per hour day wise
vector<Receiver> Receiver::averageFootfallsPerHourDaily(vector<Receiver> footfallData)
{
	vector<Receiver> hourlyAverageDailyData;
	Receiver receiverObj(footfallData[0].date, footfallData[0].month, footfallData[0].year, 0);
	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(receiverObj.date == footfallData[i].date) // if footfallData[i].date is equal to date whose count is being computed
		{
			receiverObj.hourlyAverage += 1;
		}
		else
		{
			receiverObj.hourlyAverage = receiverObj.hourlyAverage / 4; // working hours per day = 4
			hourlyAverageDailyData.push_back(receiverObj);
			receiverObj.date = footfallData[i].date; // set initial values for next date object
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.hourlyAverage = 0;
			i--; // run same iteration again
		}
	}
	receiverObj.hourlyAverage = receiverObj.hourlyAverage / 4; 
	hourlyAverageDailyData.push_back(receiverObj); // store last object
	
	return hourlyAverageDailyData;
}

// display average footfalls per hour day wise on console and write to csv file
void Receiver::displayHourlyAverageDailyData(vector<Receiver> hourlyAverageDailyData)
{
	ofstream fout("test-data/Average Footfalls Hourly.csv");
	cout<<"Date "<<"Month "<<"Year "<<" Hourly Avg"<<endl;
	if(fout.is_open())
	{
		fout << "Date" << "," << "Month" << "," << "Year" << "," << "HourlyAverage" <<"\n";
		for(unsigned int i = 0; i < hourlyAverageDailyData.size(); i++)
		{
			cout<<hourlyAverageDailyData[i].date<<" "<<hourlyAverageDailyData[i].month<<" "<<hourlyAverageDailyData[i].year<<" "<<hourlyAverageDailyData[i].hourlyAverage<<endl;
			fout << hourlyAverageDailyData[i].date << "," << hourlyAverageDailyData[i].month << "," << hourlyAverageDailyData[i].year << "," << hourlyAverageDailyData[i].hourlyAverage <<"\n";
		}
	}
	fout.close();
}

int Receiver::setFlagStatus(int day)
{
	if(day == 1)
		return 0;
	return 1;
}

// calculate average footfalls per day week wise
vector<Receiver> Receiver::averageDailyFootfallsWeekly(vector<Receiver> footfallData)
{
	vector<Receiver> dailyAverageWeeklyData;
	Receiver receiverObj(footfallData[0].day, footfallData[0].date, footfallData[0].month, footfallData[0].year, 0); // start date for week
	int flag = 0;

	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(footfallData[i].day != flag)
		{
			receiverObj.weeklyAverage += 1;
			flag = setFlagStatus(footfallData[i].day); // if footfallData[i] is 1 set flag to 0 (to continue counting for day = 1) else set flag to 0 (to continue counting for day = 2 to 7)
		}
		else
		{
			receiverObj.weeklyAverage = receiverObj.weeklyAverage / 7; // 1 week is day = 1 to 7 (Mon-Sun)
			dailyAverageWeeklyData.push_back(receiverObj);
			receiverObj.day = footfallData[i].day; // set initial values for next week object
			receiverObj.date = footfallData[i].date;
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.weeklyAverage = 0;
			flag = 0;
			i--;	
		}
	}
	receiverObj.weeklyAverage = receiverObj.weeklyAverage / 7;
	dailyAverageWeeklyData.push_back(receiverObj); // store last object
	
	return dailyAverageWeeklyData;
}

// display average footfalls per day week wise on console and write to csv file
void Receiver::displayDailyAverageWeeklyData(vector<Receiver> dailyAverageWeeklyData)
{
	ofstream fout("test-data/Average Footfalls Weekly.csv");
	cout<<"Date "<<"Month "<<"Year "<<" Weekly Avg"<<endl;
	if(fout.is_open())
	{
		fout << "Date" << "," << "Month" << "," << "Year" << "," << "WeeklyAverage" <<"\n";
		for(unsigned int i = 0; i < dailyAverageWeeklyData.size(); i++)
		{
			cout<<dailyAverageWeeklyData[i].date<<" "<<dailyAverageWeeklyData[i].month<<" "<<dailyAverageWeeklyData[i].year<<" "<<dailyAverageWeeklyData[i].weeklyAverage<<endl;
			fout<<dailyAverageWeeklyData[i].date<<","<<dailyAverageWeeklyData[i].month<<","<<dailyAverageWeeklyData[i].year<<","<<dailyAverageWeeklyData[i].weeklyAverage<<"\n";
		}
	}
	fout.close();
}

// calculate peak daily footfall in the last month
vector<Receiver> Receiver::peakDailyFootfallLastMonth(vector<Receiver> footfallData)
{
	vector<Receiver> dailyFootfallLastMonthData;
	vector<Receiver> footfallLastMonthData = getLastMonthFootfallData(footfallData); // get footfall records for last month
	Receiver receiverObj(footfallLastMonthData[0].date, footfallLastMonthData[0].month, footfallLastMonthData[0].year, 0);
	for(unsigned int i = 0; i < footfallLastMonthData.size(); i++)
	{
		if(receiverObj.date == footfallLastMonthData[i].date) // if footfallLastMonthData[i].date is equal to date whose count is being computed
		{
			receiverObj.dailyCount += 1;
		}
		else
		{
			dailyFootfallLastMonthData.push_back(receiverObj);
			receiverObj.date = footfallData[i].date; // set initial values for next date object
			receiverObj.month = footfallData[i].month;
			receiverObj.year = footfallData[i].year;
			receiverObj.dailyCount = 0;
			i--;
		}
	}
	dailyFootfallLastMonthData.push_back(receiverObj); // store last object
	
	vector<Receiver> peakDailyFootfallsLastMonthData = getPeakDailyFootfallsLastMonth(dailyFootfallLastMonthData); // get records for days which had peak footfall counts
	return peakDailyFootfallsLastMonthData;
}

vector<Receiver> Receiver::getLastMonthFootfallData(vector<Receiver> footfallData)
{
	//time_t currentTime = time(0);
	//tm *localTime = localtime(&currentTime);
	//int lastMonth = localTime->tm_mon;
	int lastMonth = 8;
	vector<Receiver> lastMonthFootfallData;
	for(unsigned int i = 0; i < footfallData.size(); i++)
	{
		if(lastMonth == footfallData[i].month)
		{
			lastMonthFootfallData.push_back(footfallData[i]);
		}
	}
	cout<<"size get last "<<lastMonthFootfallData.size()<<endl;
	return lastMonthFootfallData;
}

vector<Receiver> Receiver::getPeakDailyFootfallsLastMonth(vector<Receiver> dailyFootfallLastMonthData)
{
	sort(dailyFootfallLastMonthData.begin(), dailyFootfallLastMonthData.end(), [](const Receiver& firstObj, const Receiver& secondObj) // sort last month daily footfall counts in descending order
	{
    		return firstObj.dailyCount > secondObj.dailyCount;
	});
	vector<Receiver> peakDailyFootfallsLastMonth;
	int peakCount = dailyFootfallLastMonthData[0].dailyCount;
	for(unsigned int i = 0; i < dailyFootfallLastMonthData.size(); i++)
	{
		if(peakCount == dailyFootfallLastMonthData[i].dailyCount) // if dailyFootfallLastMonthData[i].dailyCount is equal to peakCount footfalls
		{
			peakDailyFootfallsLastMonth.push_back(dailyFootfallLastMonthData[i]);
		}
	}
	return peakDailyFootfallsLastMonth;
}

// display peak footfall days on console and write to csv file
void Receiver::displayPeakDailyFootfallLastMonth(vector<Receiver> peakDailyFootfallsLastMonthData)
{
	ofstream fout("test-data/Peak Daily Footfalls Last Month.csv");
	cout<<"Date "<<"Month "<<"Year "<<"Peak Count"<<endl;
	if(fout.is_open())
	{
		fout << "Date" << "," << "Month" << "," << "Year" << "," << "PeakCount" <<"\n";
		for(unsigned int i = 0; i < peakDailyFootfallsLastMonthData.size(); i++)
		{
			cout<<peakDailyFootfallsLastMonthData[i].date<<" "<<peakDailyFootfallsLastMonthData[i].month<<" "<<peakDailyFootfallsLastMonthData[i].year<<" "<<peakDailyFootfallsLastMonthData[i].dailyCount<<endl;
			fout<<peakDailyFootfallsLastMonthData[i].date<<","<<peakDailyFootfallsLastMonthData[i].month<<","<<peakDailyFootfallsLastMonthData[i].year<<","<<peakDailyFootfallsLastMonthData[i].dailyCount<<"\n";
		}
	}
	fout.close();
}


