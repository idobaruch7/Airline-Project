#pragma once
#include <string>

using namespace std;

class CPlane
{
private:
	int serialNumber;
	int seatCount;
	string modelName;

	// Helper function
	bool isValidString(const string& str) const;
	bool isValidPositiveInt(int value) const;

public:
	// Constructors
	CPlane(int number, int count, const string& name);
	CPlane(const CPlane& other);

	// Setters
	void setSerialNumber(int number);
	void setModelName(const string& name);
	void setSeatCount(int count);

	// Getters
	int getSerialNumber() const;
	const string& getModelName() const;
	int getSeatCount() const;

	bool isEqual(const CPlane& other) const;
	void print() const;

	// Destructor
	~CPlane();
};