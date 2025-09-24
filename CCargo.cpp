#include "CCargo.h"
#include <iostream>
#include <string>

using namespace std;

//Constructor
CCargo::CCargo(int seatCount,
    const string& modelName,
    float maxCargoWeightKg,
    float maxCargoVolume,
    float currCargoWeightKg,
    float currCargoVolume)
    : CPlane(seatCount, modelName),       
    maxCargoWeightKg(max(0.0f, maxCargoWeightKg)),
    maxCargoVolume(max(0.0f, maxCargoVolume)),
    currCargoWeightKg(max(0.0f, currCargoWeightKg)),
    currCargoVolume(max(0.0f, currCargoVolume))
{
    setMaxCargoWeightKg(maxCargoWeightKg);
    setMaxCargoVolume(maxCargoVolume);
    setCurrCargoVolume(currCargoVolume);
    setCurrCargoWeightKg(currCargoWeightKg);
}

//Copy Constructor
CCargo::CCargo(const CCargo& other)
    : CPlane(other),   // מפעיל את copy constructor של CPlane
    maxCargoWeightKg(other.maxCargoWeightKg),
    maxCargoVolume(other.maxCargoVolume),
    currCargoWeightKg(other.currCargoWeightKg),
    currCargoVolume(other.currCargoVolume)
{
}



//Setters
void CCargo::setMaxCargoWeightKg(float kg)
{
    if (isValidPositiveFloat(kg))
        maxCargoWeightKg = kg;
}

void CCargo::setMaxCargoVolume(float m3)
{
    if (isValidPositiveFloat(m3))
        maxCargoVolume = m3;
}

void CCargo::setCurrCargoWeightKg(float kg)
{
    if (isValidPositiveFloat(kg))
        currCargoWeightKg = kg;
}

void CCargo::setCurrCargoVolume(float m3)
{
    if (isValidPositiveFloat(m3))
        currCargoVolume = m3;
}

//Getters

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

//HelperFunction for load
bool CCargo::canLoad(float weightKg, float volume) const
{
    if (weightKg < 0.0f || volume < 0.0f)
        return false;

    if (currCargoWeightKg + weightKg > maxCargoWeightKg)
        return false;

    if (currCargoVolume + volume > maxCargoVolume)
        return false;

    return true;
}

bool CCargo::load(float weightKg, float volume)
{
    if (!canLoad(weightKg, volume))
        return false;

    currCargoWeightKg += weightKg;
    currCargoVolume += volume;
    return true;
}

//Takeoff
void CCargo::takeOff(int minutes) const
{
    std::cout << "Need to add " << minutes << " to my log book" << std::endl;
}


void CCargo::print(ostream& os) const
{
    os << "Plane " << getSerialNumber()
       << " degem " << getModelName()
       << " seats " << getSeatCount() << endl
       << "Cargo M_vol " << maxCargoVolume
       << " M_Kg " << maxCargoWeightKg
       << " C_vol " << currCargoVolume
       << " C_Kg " << currCargoWeightKg
       << endl;
}

//destructor
CCargo::~CCargo() {

}