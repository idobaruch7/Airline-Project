#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
using namespace std;

#include "CPlane.h"
#include "CFlight.h"
#include "CFlightCompany.h"


#include <iostream>
#include "CAddress.h"

void main()
{
	cout << endl << "Checking Address" << endl;
	CAddress a(0, NULL, NULL);
	cin >> a;
	cout << a;

	cout << endl << "Checking CFlightCompany" << endl;

	CFlightCompany* pDelta = new CFlightCompany("Delta");
	cout << endl << "First company" << endl;
	pDelta->Print(cout);


	CCrewMember* pCmArr[3];

	pCmArr[0] = new CCrewMember("Momo", 125);
	pCmArr[1] = new CCrewMember("Gogo");
	pCmArr[2] = new CCrewMember("Jojo", 60);

	if (!((*pCmArr[1]) += 200))
		cout << "error update minutes" << endl;

	for (int i = 0; i < 3; i++)
		if (!pDelta->AddCrewMember(*pCmArr[i]))
			cout << "Problem adding crew member " << i + 1 << endl;

	cout << "******** try adding CrewMembers again *********" << endl;
	//Create another array that is equal to the first array
	CCrewMember* crewsDup[3];
	for (int i = 0; i < 3; i++)
		crewsDup[i] = new CCrewMember(*pCmArr[i]);

	for (int i = 0; i < 3; i++) {
		if (!pDelta->AddCrewMember(*pCmArr[i]))
			cout << "Problem adding crew member " << i + 1 << endl;
	}

	for (int i = 0; i < 3; i++)
		delete crewsDup[i];

	for (int i = 0; i < 3; i++)
		delete pCmArr[i];

	cout << "******** After adding Crew member *********" << endl;
	pDelta->Print(cout);


	CPlane* pPlaneArr[2];
	pPlaneArr[0] = new CPlane(100, "Boing373");  //seats,degem
	pPlaneArr[1] = new CPlane(10, "Boing3");

	cout << "Before adding seats" << endl;
	cout << *pPlaneArr[1];

	//Adding seats
	(*pPlaneArr[1])++;
	++(*pPlaneArr[1]);

	cout << "After adding seats" << endl;
	cout << *pPlaneArr[1];

	for (int i = 0; i < 2; i++)
		if (!pDelta->AddPlane(*pPlaneArr[i]))
			cout << "Problem adding plane " << i + 1 << endl;

	for (int i = 0; i < 2; i++)
		delete pPlaneArr[i];

	cout << "******** After adding Planes *********" << endl;
	pDelta->Print(cout);

	CFlightInfo fInfo1("Paris", 343, 320, 5000);
	CFlightInfo fInfo2("Rome", 506, 220, 4000);

	cout << fInfo1;
	cout << fInfo2;

	if (fInfo1 != fInfo2)
		cout << "FlightInfo not equal" << endl;
	else
		cout << "FlightInfo equal" << endl;

	cout << "Flight time is: " << (int)fInfo1;

	CFlight* FArr[2];
	FArr[0] = new CFlight(fInfo1);
	FArr[1] = new CFlight(fInfo2, pDelta->GetPlane(1));

	cout << "Before seting plane" << endl;
	cout << *FArr[0];
	FArr[0]->SetPlane(pDelta->GetPlane(0));

	cout << "After seting plane " << endl;
	cout << *FArr[0];

	for (int i = 0; i < 2; i++)
		if (!pDelta->AddFlight(*FArr[i]))
			cout << "Problem adding flight " << i + 1 << endl;

	for (int i = 0; i < 2; i++)
		delete FArr[i];

	cout << "******** After adding Flights *********" << endl;
	pDelta->Print(cout);


	pDelta->AddCrewToFlight(fInfo1.GetFNum(), CCrewMember::START_ID);
	pDelta->AddCrewToFlight(fInfo1.GetFNum(), CCrewMember::START_ID + 1);
	pDelta->AddCrewToFlight(fInfo1.GetFNum(), CCrewMember::START_ID + 2);

	cout << "******** After adding Crew to Flight *********" << endl;
	pDelta->Print(cout);


	delete pDelta;

	system("pause");
}

