#include "CPlaneCrewFactory.h"
#include "CHost.h"
#include "CPilot.h"
#include "CPlane.h"
#include "CCargo.h"
#include "CAddress.h"
#include <fstream>

using namespace std;

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