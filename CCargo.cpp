#include "CCargo.h"
#include <iostream>

using namespace std;

CCargo::CCargo(int seatCount, const string& modelName, float maxCargoWeightKg, float maxCargoVolume, float currCargoWeightKg, float currCargoVolume)
    : CPlane(seatCount, modelName), 
      maxCargoWeightKg(0.0f), maxCargoVolume(0.0f), currCargoWeightKg(0.0f), currCargoVolume(0.0f)
{
    setMaxCargoWeightKg(maxCargoWeightKg);
    setMaxCargoVolume(maxCargoVolume);
    setCurrCargoWeightKg(currCargoWeightKg);
    setCurrCargoVolume(currCargoVolume);
}

CCargo::CCargo(const CCargo& other)
    : CPlane(other),
      maxCargoWeightKg(other.maxCargoWeightKg),
      maxCargoVolume(other.maxCargoVolume),
      currCargoWeightKg(other.currCargoWeightKg),
      currCargoVolume(other.currCargoVolume)
{
}

CCargo::~CCargo()
{
}

bool CCargo::load(float weightKg, float volume)
{
    if (!isValidPositiveFloat(weightKg) || !isValidPositiveFloat(volume)) {
        return false;
    }

    if (!canLoad(weightKg, volume)) {
        return false;
    }

    currCargoWeightKg += weightKg;
    currCargoVolume += volume;
    return true;
}

void CCargo::takeOff(int minutes) const
{
    cout << "Cargo plane " << getSerialNumber()
         << " is taking off for " << minutes << " minutes with "
         << currCargoWeightKg << " kg cargo" << endl;
}

// Getters
float CCargo::getMaxCargoWeightKg() const
{
    return maxCargoWeightKg;
}

float CCargo::getMaxCargoVolume() const
{
    return maxCargoVolume;
}

float CCargo::getCurrCargoWeightKg() const
{
    return currCargoWeightKg;
}

float CCargo::getCurrCargoVolume() const
{
    return currCargoVolume;
}

float CCargo::getAvailableWeightKg() const
{
    return maxCargoWeightKg - currCargoWeightKg;
}

float CCargo::getAvailableVolume() const
{
    return maxCargoVolume - currCargoVolume;
}

// Setters
void CCargo::setMaxCargoWeightKg(float kg)
{
    if (!isValidPositiveFloat(kg)) {
        throw CCompStringException("Invalid max cargo weight: must be non-negative");
    }
    maxCargoWeightKg = kg;
}

void CCargo::setMaxCargoVolume(float m3)
{
    if (!isValidPositiveFloat(m3)) {
        throw CCompStringException("Invalid max cargo volume: must be non-negative");
    }
    maxCargoVolume = m3;
}

void CCargo::setCurrCargoWeightKg(float kg)
{
    if (!isValidPositiveFloat(kg)) {
        throw CCompStringException("Invalid current cargo weight: must be non-negative");
    }
    if (kg > maxCargoWeightKg) {
        throw CCompStringException("Current cargo weight cannot exceed maximum weight");
    }
    currCargoWeightKg = kg;
}

void CCargo::setCurrCargoVolume(float m3)
{
    if (!isValidPositiveFloat(m3)) {
        throw CCompStringException("Invalid current cargo volume: must be non-negative");
    }
    if (m3 > maxCargoVolume) {
        throw CCompStringException("Current cargo volume cannot exceed maximum volume");
    }
    currCargoVolume = m3;
}

bool CCargo::canLoad(float weightKg, float volumeM3) const
{
    return (currCargoWeightKg + weightKg <= maxCargoWeightKg) &&
           (currCargoVolume + volumeM3 <= maxCargoVolume);
}

ostream& operator<<(ostream& os, const CCargo& cargo)
{
    cargo.print(os);
    return os;
}

void CCargo::print(ostream& os) const
{
    os << "Cargo Plane " << getSerialNumber()
       << " degem " << getModelName()
       << " seats " << getSeatCount()
       << " max cargo weight " << maxCargoWeightKg << " kg"
       << " max cargo volume " << maxCargoVolume << " m3"
       << " current cargo weight " << currCargoWeightKg << " kg"
       << " current cargo volume " << currCargoVolume << " m3" << endl;
}