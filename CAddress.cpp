#include "CAddress.h"
#include <iostream>
#include <string>
using namespace std;

// Helper functions
bool CAddress::isValidString(const string& str) const {
    return !str.empty();
}

bool CAddress::isValidHouseNumber(int number) const {
    return number > 0;
}

// Constructor with validation
CAddress::CAddress(int houseNumber, const string& street, const string& city) {
    // Validate and set house number
    this->houseNumber = isValidHouseNumber(houseNumber) ? houseNumber : 1;

    // Validate and set street
    this->street = isValidString(street) ? street : "Unknown Street";

    // Validate and set city
    this->city = isValidString(city) ? city : "Unknown City";
}

// Copy Constructor
CAddress::CAddress(const CAddress& other)
    : houseNumber(other.houseNumber), street(other.street), city(other.city) {
}

// Setters with validation
void CAddress::setCity(const string& newCity) {
    if (isValidString(newCity)) {
        this->city = newCity;
    }
    // If invalid, don't change the city
}

void CAddress::setStreet(const string& newStreet) {
    if (isValidString(newStreet)) {
        this->street = newStreet;
    }
    // If invalid, don't change the street
}

void CAddress::setHouseNumber(int newHouseNumber) {
    if (isValidHouseNumber(newHouseNumber)) {
        this->houseNumber = newHouseNumber;
    }
    // If invalid, don't change the house number
}

// Getters
const string& CAddress::getCity() const {
    return city;
}

const string& CAddress::getStreet() const {
    return street;
}

int CAddress::getHouseNumber() const {
    return houseNumber;
}

bool CAddress::isEqual(const CAddress& other) const {
    return city == other.city && street == other.street && houseNumber == other.houseNumber;
}

// Print
void CAddress::print() const {
    cout << street << " " << houseNumber << ", " << city << endl;
}

//Operations Functions
ostream& operator<<(ostream& os, const CAddress& addr)
{
    os << addr.street << " " << addr.houseNumber << " " << addr.city << endl;
    return os; // allows chaining like cout >> a >> b;;
}

istream& operator>>(istream& is, CAddress& addr)
{

    cout << "Enter house number: ";
    is >> addr.houseNumber;

    cout << "Enter street: ";
    is >> addr.street;

    cout << "Enter city: ";
    is >> addr.city;

    return is; // allows chaining like cin >> a >> b;
}

bool CAddress::operator==(const CAddress& other) const
{
    return isEqual(other);

}

bool CAddress::operator!=(const CAddress& other) const
{
    return !isEqual(other);
}

CAddress& CAddress::operator=(const CAddress& other)
{
    if (this != &other) { // protect against self-assignment
        houseNumber = other.houseNumber;
        street = other.street;
        city = other.city;
    }
    return *this; // allow chaining
}

string CAddress::getCurrentAddress()const
{
    return street + " " + to_string(houseNumber) + " " + city;
}

// UpdateAddress with validation - only update valid data
void CAddress::updateAddress(const string& newCity, const string& newStreet, int newHouseNumber) {
    // Only update valid values
    if (isValidString(newCity)) {
        this->city = newCity;
    }

    if (isValidString(newStreet)) {
        this->street = newStreet;
    }

    if (isValidHouseNumber(newHouseNumber)) {
        this->houseNumber = newHouseNumber;
    }
}

CAddress::~CAddress() {
}


