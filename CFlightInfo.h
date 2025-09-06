#pragma once
#include <string>

using namespace std;

class CFlightInfo
{
private:
	int flightNumber;
	string destination;
	int flightTimeMinutes;
	int distanceKM;
	
	// Helper functions
	bool isValidString(const string& str) const;
	bool isValidPositiveInt(int value) const;

public:
	CFlightInfo(const string& dest, int number, int timeMinutes, int distance);
	CFlightInfo(const CFlightInfo& other);

	void setFlightNumber(int number);
	void setDest(const string& dest);
	void setFlightTimeMinutes(int timeMinutes);
	void setDistanceKM(int distance);

	int getFlightNumber() const;
	const string& getDest() const;
	int getFlightTimeMinutes() const;
	int getDistanceKM() const;

	bool isEqual(const CFlightInfo& other) const;
	void print() const;

	~CFlightInfo();
};