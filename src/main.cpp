#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <limits>
#include "CPlane.h"
#include "CFlightInfo.h"
#include "CCrewMember.h"
#include "CFlight.h"
#include "CFlightCompany.h"
#include "CAddress.h"
#include "CPilot.h"
#include "CCargo.h"
#include "CHost.h"
#include "CFlightCompException.h"
#include "CPlaneCrewFactory.h"

using namespace std;

void showMenu() {
    cout << "\n=============================================\n";
    cout << "         ✈️  AIRLINE MANAGEMENT SYSTEM \n";
    cout << "=============================================\n";
    cout << "[1] View Company Information\n";
    cout << "[2] Add Data (Planes & Crew)\n";
    cout << "[3] Add New Flight\n";
    cout << "[4] Save Data to File\n";
    cout << "[0] Exit\n";
    cout << "=============================================\n";
    cout << "Select an option: ";
}

int main()
{
    CFlightCompany* pDelta = nullptr;

    try {
        pDelta = new CFlightCompany("data/Delta.txt", 0);
        cout << "Successfully loaded company data from file.\n";
    }
    catch (const CFlightCompException& e) {
        cout << "Could not load existing data or file missing. Starting fresh.\n";
        pDelta = new CFlightCompany("Delta Airlines");
    }

    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    pDelta->print(cout);
                    break;
                case 2:
                    CPlaneCrewFactory::GetCompanyDataFromUser(*pDelta);
                    break;
                case 3: {
                    string dest;
                    int flightNum, minutes, km;
                    cout << "Enter destination: ";
                    cin >> dest;
                    cout << "Enter flight number: ";
                    cin >> flightNum;
                    cout << "Enter duration (minutes): ";
                    cin >> minutes;
                    cout << "Enter distance (km): ";
                    cin >> km;
                    
                    CFlightInfo info(dest, flightNum, minutes, km);
                    CFlight flight(info);
                    
                    if (pDelta->addFlight(flight)) {
                        cout << "Flight added successfully!\n";
                    } else {
                        cout << "Failed to add flight.\n";
                    }
                    break;
                }
                case 4:
                    pDelta->saveToFile("data/Delta.txt");
                    break;
                case 0:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (const CFlightCompException& e) {
            e.show();
        }
    } while (choice != 0);

    delete pDelta;
    return 0;
}