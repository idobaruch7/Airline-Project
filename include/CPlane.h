#pragma once
#include <string>
#include <iostream>
#include "CFlightCompException.h"

using namespace std;

class CPlane
{
private:
	int serialNumber;
	int seatCount;
	string modelName;

	static const int MAX_MODEL_NAME_LENGTH = 30;

protected:
	// Helper function
	bool isValidString(const string& str) const;
	bool isValidPositiveInt(int value) const;
	bool isValidPositiveFloat(float value) const;

public:
	//Default Constructor Deletion
	CPlane() = delete;

	// Constructors
	CPlane(int count, const string& name);
	CPlane(const CPlane& other);

	// Setters
	void setModelName(const string& name);
	void setSeatCount(int count);

	// Getters
	int getSerialNumber() const;
	const string& getModelName() const;
	int getSeatCount() const;

	bool isEqual(const CPlane& other) const;
	virtual void print(ostream& os = std::cout) const;

	// Destructor
	virtual ~CPlane();

	//Operations
	friend ostream& operator<<(ostream& os, const CPlane& plane); //<<

	bool operator==(const CPlane& other) const;
	bool operator!=(const CPlane& other) const;
	CPlane& operator++();
	CPlane operator++(int);

	CPlane& operator=(const CPlane& other);

	static int nextSerial;

};