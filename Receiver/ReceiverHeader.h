#pragma once
#include <vector>
#include <string>

using namespace std;

class Receiver
{
private:
	int id = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
	int day = 0; // 1 = monday 2 = tuesday... 7 = sunday
	int date;
	int month;
	int year;
	int dailyCount = 0;
	float hourlyAverage = 0;
	float weeklyAverage = 0;
public:
	Receiver();
	Receiver(int, int, int, float);
	Receiver(int, int, int, int, float);
	Receiver(int, int, int, int, int, int, int, int);
	vector<Receiver> readSenderData();
	vector<Receiver> storeFootfallData(const string&, vector<Receiver>);
	vector<Receiver> averageFootfallsPerHourDaily(vector<Receiver>);
	void displayHourlyAverageDailyData(vector<Receiver>);
	vector<Receiver> averageDailyFootfallsWeekly(vector<Receiver>);
	int setFlagStatus(int);
	void displayDailyAverageWeeklyData(vector<Receiver>);
	vector<Receiver> peakDailyFootfallLastMonth(vector<Receiver>);
	vector<Receiver> getLastMonthFootfallData(vector<Receiver>);
	vector<Receiver> getPeakDailyFootfallsLastMonth(vector<Receiver>);
	void displayPeakDailyFootfallLastMonth(vector<Receiver>);
};
