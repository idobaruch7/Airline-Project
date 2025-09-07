#pragma once

#include <iostream>
#include <string>
using namespace std;

class CAddress {
private:
    string city;
    string street;
    int houseNumber;

    bool isValidString(const string& str) const;
    bool isValidHouseNumber(int number) const;

public:
    //Default Constructor Deletion
    CAddress() = delete;

    // Constructor
    CAddress(int houseNumber, const string& street, const string& city = "Tel Aviv");

    // Copy Constructor 
    CAddress(const CAddress& other);

    // Destructor
    ~CAddress();

    // Setters
    void setCity(const string& newCity);
    void setStreet(const string& newStreet);
    void setHouseNumber(int newHouseNumber);

    // Getters
    const string& getCity() const;
    const string& getStreet() const;
    int getHouseNumber() const;

    // Print
    void print() const;

    //isEqual
    bool isEqual(const CAddress& other) const;

    // UpdateAddress
    void updateAddress(const string& newCity, const string& newStreet, int newHouseNumber);


    //Operations
    friend ostream& operator<<(ostream& os, const CAddress& addr); //<<

    friend istream& operator>>(istream& is, CAddress& addr);// >>

    bool operator==(const CAddress& other) const;

    bool operator!=(const CAddress& other)const;

    CAddress& operator=(const CAddress& other);

    string getCurrentAddress() const;





};



