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


const int CM_COUNT = 5;
const int PLANE_COUNT = 4;
const int FLIGHT_COUNT = 4;

void main()
{
	CFlightCompany Delta("Delta");
	CAddress ad1(34, "DZ");

	CCrewMember* cmArr[CM_COUNT];
	cmArr[0] = new CPilot("Soso", false, &ad1); //name, bcaptain, home add, no min
	cmArr[1] = new CHost("Momo", CHost::eRegular);//name, type
	cmArr[2] = new CHost("Lolo", CHost::eSuper);
	cmArr[3] = new CHost("Popo", CHost::eCalcelan);
	cmArr[4] = new CPilot("Toto", true); //no address and min

	//Check updateTime
	for (int i = 0; i < CM_COUNT; i++)
		(*cmArr[i]) += (60);

	for (int i = 0; i < CM_COUNT; i++)
		cmArr[i]->print(cout);

	cout << endl << "******** Add CrewMember  *********" << endl;
	for (int i = 0; i < CM_COUNT; i++)
	{
		if (!Delta.addCrewMember(*cmArr[i]))
			cout << "Problem adding CrewMember " << i << endl;
	}

	cout << endl << "******** Trying add same CrewMember *********" << endl;
	CHost h1((CHost&)(*cmArr[1])); //creating temp with different pointers.
	CPilot p1((CPilot&)(*cmArr[4]));
	if (!Delta.addCrewMember(h1))
		cout << "Problem adding CrewMember h1" << endl;

	if (!Delta.addCrewMember(p1))
		cout << "Problem adding CrewMember p1" << endl;

	cout << endl << "******** After adding CrewMember *********" << endl;
	Delta.print(cout);

	cout << "********  *********" << endl;

	for (int i = 0; i < CM_COUNT; i++)
		delete cmArr[i];

	CPlane* pArr[PLANE_COUNT];
	pArr[0] = new CPlane(100, "Boing373"); //seats and degem
	pArr[1] = new CPlane(50, "Boing373");
	pArr[2] = new CPlane(1, "Boing3");
	pArr[3] = new CCargo(4, "Lift400", 4000, 5000); //seats, degem, max kg, max volume

	//checking load cargo
	if (!((CCargo*)pArr[3])->load(1000, 1500))
		cout << "error1 loading plane " << (*pArr[3]) << endl;

	if (!((CCargo*)pArr[3])->load(800, 2000))
		cout << "error2 loading plane " << (*pArr[3]) << endl;

	if (!((CCargo*)pArr[3])->load(1800, 1000))
		cout << "error3 loading plane " << (*pArr[3]) << endl;


	if (!((CCargo*)pArr[3])->load(800, 1200))
		cout << "error4 loading plane " << (*pArr[3]) << endl;


	for (int i = 0; i < PLANE_COUNT; i++)
		if (!Delta.addPlane(*pArr[i]))
			cout << "Problem adding " << *pArr[i];

	for (int i = 0; i < PLANE_COUNT; i++)
		if (!Delta.addPlane(*pArr[i]))
			cout << "Problem adding " << *pArr[i];


	cout << "******** After adding Planes *********" << endl;
	Delta.print(cout);
	cout << "********  *********" << endl;

	for (int i = 0; i < PLANE_COUNT; i++)
		delete pArr[i];


	CFlightInfo* fInfoArr[FLIGHT_COUNT];
	//const char* dest,int n,int min, int km
	fInfoArr[0] = new CFlightInfo("Paris", 343, 320, 5000);
	fInfoArr[1] = new CFlightInfo("Rome", 506, 220, 4000);
	fInfoArr[2] = new CFlightInfo("London", 600, 400, 6000);
	fInfoArr[3] = new CFlightInfo("Berlin", 706, 340, 4500);


	CFlight* FArr[FLIGHT_COUNT];
	for (int i = 0; i < FLIGHT_COUNT; i++)
		FArr[i] = new CFlight(*fInfoArr[i], Delta.getPlane(i));

	for (int i = 0; i < FLIGHT_COUNT; i++)
		if (!Delta.addFlight(*FArr[i]))
			cout << "Problem adding flight " << FArr[i]->getFlightInfo();

	for (int i = 0; i < FLIGHT_COUNT; i++)
		if (!Delta.addFlight(*FArr[i]))
			cout << "Problem adding flight " << FArr[i]->getFlightInfo();

	cout << "******** After adding Flights *********" << endl;
	Delta.print(cout);
	cout << "********  *********" << endl;

	for (int i = 0; i < FLIGHT_COUNT; i++) {
		delete fInfoArr[i];
		delete FArr[i];
	}

	CFlight* pF2 = Delta.getFlightByNum(706);

	CCrewMember* pCmTemp;
	if (pF2 != NULL) {
		cout << "flight 706 was found\n" << endl;

		for (int i = 0; i < CM_COUNT / 2; i++) {
			pCmTemp = Delta.getCrewMember(i);
			*pF2 + pCmTemp;
		}

		cout << "******** Take off *********" << endl;
		if (!pF2->takeOff())
			cout << "error in take of flight 706" << endl;

	}
	else
		cout << "flight 706 was not found " << endl;

	pF2 = Delta.getFlightByNum(343);
	if (pF2 != NULL) {
		cout << "flight 343 was found " << endl;
		for (int i = 0; i < CM_COUNT; i++) {
			pCmTemp = Delta.getCrewMember(i);
			*pF2 + pCmTemp;
		}
		cout << "******** Take off *********" << endl;
		if (!pF2->takeOff())
			cout << "error in take of flight 343" << endl;

	}
	else
		cout << "flight 343 was not found " << endl;

	cout << "******** Holiday Gift is now on *********" << endl;
	Delta.crewGetPresent();
	cout << "********  *********" << endl;

	cout << "******** Simulator is on *********" << endl;
	Delta.pilotsToSimulator();
	cout << "********  *********" << endl;

	cout << "******** Uniform to all *********" << endl;
	Delta.crewGetUniform();
	cout << "********  *********" << endl;

	cout << "******** Counting cargo planes *********" << endl;

	cout << "Delta has " << Delta.getCargoCount() << " cargo planes" << endl;

	cout << "******** final flight company print *********" << endl;
	Delta.print(cout);
	cout << "********  *********" << endl;



	system("pause");
}