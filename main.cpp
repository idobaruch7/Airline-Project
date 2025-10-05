#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
using namespace std;

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

//const int CM_COUNT = 5;
//const int PLANE_COUNT = 4;
//const int FLIGHT_COUNT = 4;

int main()
{

	CFlightCompany* pDelta = NULL;
	try
	{

		pDelta = new CFlightCompany("Delta.txt", 0);
		cout << "This was in file " << endl;
		pDelta->print(cout);

	}
	catch (const CFlightCompException& e) {
		e.show();
		pDelta = new CFlightCompany("Delta");
	}

	
	
	//Checking some of the exception put try and catch for each section	
	try {
		CPlane p1(-34, "AirBus");
		CCargo c1(45, "Jumbo", -560, 200);
		CCargo c2(45, "Jumbo", 560, -200);
		CFlightInfo f1("London", -23, 120, 5000);
		CFlightInfo f2("LondonVeryLong", 23, 120, 5000);
		CFlightInfo f3("London", 23, -120, 5000);
		CFlightInfo f4("London", 23, 120, -5000);
		CCrewMember* pC1 = pDelta->getCrewMember(-1);
	}
	catch (const CFlightCompException& e) {
		e.show();
	}

	try {
		CCrewMember* pC2 = pDelta->getCrewMember(0);
		(*pC2) += -4;
	}
	catch (const CFlightCompException& e) {
		e.show();
	}

	try {
		CPlane p0 = (*pDelta)[9];
	}
	catch (const CFlightCompException& e) {
		e.show();
	}

	

	//call a static function that get plane or customer from user.

	CPlaneCrewFactory::GetCompanyDataFromUser(*pDelta);


	CFlightInfo Info("Paris", 343, 320, 5000);
	CFlight flight1(Info, &(*pDelta)[0]);
	pDelta->addFlight(flight1);


	CFlight* pF = pDelta->getFlightByNum(343);
	CCrewMember* pCmTemp;
	if (pF != NULL) {
		cout << "flight 343 was found " << endl;
		for (int i = 0; i < pDelta->getCrewCount(); i++) {
			pCmTemp = pDelta->getCrewMember(i);
			*pF + pCmTemp;
		}
	}


	try
	{

		pDelta->saveToFile("Delta.txt");

	}
	catch (const CFlightCompException& e) {
		e.show();
	}


	delete pDelta;

	



	system("pause");
	
return 0;
}