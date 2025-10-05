#include "CPlaneCrewFactory.h"
#include "CHost.h"
#include "CPilot.h"
#include "CPlane.h"
#include "CCargo.h"
#include "CAddress.h"
#include <fstream>
#include "CFlightCompany.h"

using namespace std;

// Gets company data (planes and crew members) from user input
void CPlaneCrewFactory::GetCompanyDataFromUser(CFlightCompany& comp)
{
	int numPlanes, numCrew;

	// Get planes from user
	cout << "How many planes do you want to add? ";
	cin >> numPlanes;

	for (int i = 0; i < numPlanes; i++) {
		cout << "\n--- Adding Plane " << (i + 1) << " ---" << endl;
		CPlane* plane = GetPlaneFromUser();
		if (plane) {
			if (!comp.addPlane(*plane)) {
				cout << "Failed to add plane (may already exist or company is full)" << endl;
			}
			delete plane; // addPlane creates its own copy
		}
	}

	// Get crew members from user
	cout << "\nHow many crew members do you want to add? ";
	cin >> numCrew;

	for (int i = 0; i < numCrew; i++) {
		cout << "\n--- Adding Crew Member " << (i + 1) << " ---" << endl;
		CCrewMember* crew = GetCrewFromUser();
		if (crew) {
			if (!comp.addCrewMember(*crew)) {
				cout << "Failed to add crew member (may already exist or company is full)" << endl;
			}
			delete crew; // addCrewMember creates its own copy
		}
	}

	cout << "\nFinished adding data to company!" << endl;
}



// Reads and creates a crew member from file based on type
CCrewMember* CPlaneCrewFactory::GetCrewMemberFromFile(ifstream& inFile)
{
	int type;
	inFile >> type;

	// Read common crew member data
	string name;
	int minutes;
	inFile >> name >> minutes;

	// Create appropriate crew member based on type
	if (type == eHost) {
		// Host format: type name minutes hostType
		int hostType;
		inFile >> hostType;
		return new CHost(name, static_cast<CHost::eHostType>(hostType), minutes);
	}
	else if (type == ePilot) {
		// Pilot format: type name minutes hasAddress [houseNum street city] isCaptain
		int hasAddress;
		inFile >> hasAddress;

		CAddress* address = nullptr;
		if (hasAddress == 1) {
			int houseNum;
			string street, city;
			inFile >> houseNum >> street >> city;
			address = new CAddress(houseNum, street, city);
		}

		int isCaptain;
		inFile >> isCaptain;
		return new CPilot(name, isCaptain == 1, address, minutes);
	}

	return nullptr;
}

// Reads and creates a plane from file based on type
CPlane* CPlaneCrewFactory::GetPlaneFromFile(ifstream& inFile)
{
	int type;
	inFile >> type;

	if (type == eRegular) {
		// Regular plane format: type lastSerial id modelName seats
		int lastSerial, id, seats;
		string modelName;
		inFile >> lastSerial >> id >> modelName >> seats;

		// Create regular plane
		return new CPlane(seats, modelName);
	}
	else if (type == eCargo) {
		// Cargo plane format: type id modelName seats
		// Followed by: maxVolume maxKG currVolume currKG
		int id, seats;
		string modelName;
		inFile >> id >> modelName >> seats;

		float maxVolume, maxKG, currVolume, currKG;
		inFile >> maxVolume >> maxKG >> currVolume >> currKG;

		// Create cargo plane
		return new CCargo(seats, modelName, maxKG, maxVolume, currKG, currVolume);
	}

	return nullptr;
}

// Gets a plane from user input based on selected type
CPlane* CPlaneCrewFactory::GetPlaneFromUser()
{
	int type;
	cout << "Select plane type (0 - Regular, 1 - Cargo): ";
	cin >> type;

	// Get common plane data
	string modelName;
	int seats;
	cout << "Enter model name: ";
	cin >> modelName;
	cout << "Enter seat count: ";
	cin >> seats;

	if (type == eRegular) {
		// Create regular plane
		return new CPlane(seats, modelName);
	}
	else if (type == eCargo) {
		// Get cargo-specific data
		float maxWeight, maxVolume, currWeight, currVolume;
		cout << "Enter max cargo weight (kg): ";
		cin >> maxWeight;
		cout << "Enter max cargo volume (m3): ";
		cin >> maxVolume;
		cout << "Enter current cargo weight (kg): ";
		cin >> currWeight;
		cout << "Enter current cargo volume (m3): ";
		cin >> currVolume;

		return new CCargo(seats, modelName, maxWeight, maxVolume, currWeight, currVolume);
	}

	cout << "Invalid plane type!" << endl;
	return nullptr;
}

// Gets a crew member from user input based on selected type
CCrewMember* CPlaneCrewFactory::GetCrewFromUser()
{
	int type;
	cout << "Select crew type (0 - Host, 1 - Pilot): ";
	cin >> type;

	// Get common crew member data
	string name;
	int minutes;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter air minutes: ";
	cin >> minutes;

	if (type == eHost) {
		// Get host-specific data
		int hostType;
		cout << "Select host type (0 - Regular, 1 - Super, 2 - Calcelan): ";
		cin >> hostType;

		return new CHost(name, static_cast<CHost::eHostType>(hostType), minutes);
	}
	else if (type == ePilot) {
		// Get pilot-specific data
		int hasAddress;
		cout << "Does pilot have an address? (0 - No, 1 - Yes): ";
		cin >> hasAddress;

		CAddress* address = nullptr;
		if (hasAddress == 1) {
			int houseNum;
			string street, city;
			cout << "Enter house number: ";
			cin >> houseNum;
			cout << "Enter street name: ";
			cin >> street;
			cout << "Enter city name: ";
			cin >> city;
			address = new CAddress(houseNum, street, city);
		}

		int isCaptain;
		cout << "Is pilot a captain? (0 - No, 1 - Yes): ";
		cin >> isCaptain;

		return new CPilot(name, isCaptain == 1, address, minutes);
	}

	cout << "Invalid crew type!" << endl;
	return nullptr;
}

PlaneType CPlaneCrewFactory::GetPlaneType(const CPlane* pPlane)
{
	if (pPlane == nullptr)
		return eRegular;

	// Check if it's a cargo plane using dynamic_cast
	if (dynamic_cast<const CCargo*>(pPlane) != nullptr)
		return eCargo;

	return eRegular;
}

// Determines the runtime type of a crew member (Host or Pilot)
CrewType CPlaneCrewFactory::GetCrewType(const CCrewMember* pCrew)
{
	if (pCrew == nullptr)
		return eHost;

	// Check if it's a pilot using dynamic_cast
	if (dynamic_cast<const CPilot*>(pCrew) != nullptr)
		return ePilot;

	return eHost;
}