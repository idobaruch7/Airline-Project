#pragma once
#include <string>

using namespace std;

class CFlightCompany
{
private:
	string companyName;
	
	bool isValidName(const string& name) const;

public:
	CFlightCompany(const string& name);
	CFlightCompany(const CFlightCompany& other);

	void setName(const string& name);
	const string& getName() const;

	void print() const;

	~CFlightCompany();
};