#pragma once
#include "CCrewMember.h"
#include <iostream>
#include <string>

using namespace std;

class CHost : public CCrewMember
{
public:
    enum eHostType {
        eRegular,
        eSuper,
        eCalcelan
    };

private:
    eHostType hostType;

public:
    // Constructors
    CHost(const string& name, eHostType type = eRegular, int airMinutes = 0);
    CHost(const CHost& other);

    // Destructor
    virtual ~CHost();

    // Getters and Setters
    eHostType getHostType() const;
    void setHostType(eHostType type);

    // Virtual method overrides
    virtual void receivePresent() const override;
    virtual void receiveUniform() const override;
    virtual void updateFlightTime(int flightTimeMinutes) override;
    virtual void print() const override;
    virtual void print(ostream& os) const override;

    // Assignment operator
    CHost& operator=(const CHost& other);
};

