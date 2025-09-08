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

	//Default Constructor Deletion
	CFlightInfo() = delete;

	//Constructor
	CFlightInfo(const string& dest, int number, int timeMinutes, int distance);
	CFlightInfo(const CFlightInfo& other);

	//Functions
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

	//Operations
	friend ostream& operator<<(ostream& os, const CFlightInfo& flightInfo); //<<

	bool operator==(const CFlightInfo& other) const;
	bool operator!=(const CFlightInfo& other) const;

	CFlightInfo& operator=(const CFlightInfo& other);

	operator int() const;

	~CFlightInfo();
};