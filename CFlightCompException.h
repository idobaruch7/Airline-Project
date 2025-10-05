#pragma once
#include <string>
#include <iostream>

using namespace std;

// Abstract base exception class
class CFlightCompException
{
public:
    virtual ~CFlightCompException() = default;
    virtual void show() const = 0;
};

// String-related exception
class CCompStringException : public CFlightCompException
{
private:
    string errorMessage;

public:
    CCompStringException(const string& message) : errorMessage(message) {}
    
    virtual void show() const override
    {
        cout << "String Exception: " << errorMessage << endl;
    }
};

// Limit/boundary exception
class CCompLimitException : public CFlightCompException
{
private:
    int maxLimit;
    string context;

public:
    CCompLimitException(int limit, const string& contextMsg = "")
        : maxLimit(limit), context(contextMsg) {}
    
    virtual void show() const override
    {
        cout << "Limit Exception: Maximum allowed is " << maxLimit;
        if (!context.empty()) {
            cout << " (" << context << ")";
        }
        cout << endl;
    }
};

// File-related exception
class CCompFileException : public CFlightCompException
{
private:
    string filename;

public:
    CCompFileException(const string& fname) : filename(fname) {}
    
    virtual void show() const override
    {
        cout << "File Exception: Problem with file '" << filename << "'" << endl;
    }
};