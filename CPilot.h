#pragma once
#include "CCrewMember.h"
#include "CAddress.h"
#include <iostream>
#include <string>

using namespace std;

class CPilot : public CCrewMember
{
private:
    bool isCaptain;
    CAddress* address; // Can be nullptr if no address provided

public:
    // Constructors
    CPilot(const string& name, bool captain = false, CAddress* homeAddress = nullptr, int airMinutes = 0);
    CPilot(const CPilot& other);

    // Destructor
    ~CPilot();

    // Getters and Setters
    bool getIsCaptain() const;
    void setIsCaptain(bool captain);
    
    CAddress* getAddress() const;
    void setAddress(CAddress* newAddress);
    bool hasAddress() const;

    // Virtual method overrides
    virtual void receivePresent() const override;
    virtual void receiveUniform() const override;
    virtual void updateFlightTime(int flightTimeMinutes) override;
    virtual bool isEqual(const CCrewMember& other) const override;
    virtual void print() const override;
    virtual void print(ostream& os) const override;

    // Pilot specific methods
    void goToSimulator() const;

    // Assignment operator
    CPilot& operator=(const CPilot& other);

    // Override the += operator from CCrewMember
    CPilot& operator+=(const int flightTimeMinutes);

    // Override the virtual updateTime method
    virtual bool updateTime(int minutes) override;
};

