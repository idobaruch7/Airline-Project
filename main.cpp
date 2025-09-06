#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>

#include "CPlane.h"
#include "CFlightInfo.h"
#include "CFlightCompany.h"
#include "CAddress.h"
#include "CCrewMember.h"

using namespace std;

int main()
{
	cout << endl << "Checking CFlightCompany" << endl;
	CFlightCompany* pDelta = new CFlightCompany("Delta");
	cout << endl << "First company" << endl;
	pDelta->print();
	pDelta->setName("AA");
	cout << endl << "After change name" << endl;
	pDelta->print();
	CFlightCompany* pComp2 = new CFlightCompany(*pDelta);
	cout << endl << "two companies has the same name" << endl;
	pComp2->print();
	delete pDelta;
	delete pComp2;

	 cout << endl << "Checking CCrewMember " << endl;
	 CAddress b2(34, "Jafa", "Jerusalem");
	 CCrewMember* pCm1 = new CCrewMember("Momo", b2, 125);
	 cout << endl << "first Crew Member" << endl;
	 pCm1->print();
	 CAddress b3(34, "Jafa", "Jerusalem");
	 CCrewMember* pCm2 = new CCrewMember("Gogo", b3);
	 cout << endl << "second Crew Member" << endl;
	 pCm2->print();
	 if (!pCm2->updateMinutes(-14))
	 	cout << "error update minutes" << endl;
	 if (!pCm2->updateMinutes(200))
	 	cout << "error update minutes" << endl;
	 { //dont remove!
	 	cout << endl << "two same crewmembers" << endl;
	 	CCrewMember temp(*pCm1);
	 	temp.print();
	 	if (temp.isEqual(*pCm1))
	 		cout << "*****  EQUALS *****" << endl;
	 	else
	 		cout << "*****  NOT EQUALS *****" << endl;
	 	cout << "*****  Checking Address *****" << endl;
	 	CAddress a(23, "Alenbi");
	 	CAddress b(34, "Jafa", "Jerusalem");
	 	a.print();
	 	b.print();
	 	b.updateAddress("Haifa", "KG", 55);
	 	b.print();
	 }
	 {// don't remove !
	 	CCrewMember temp = *pCm2;
	 	temp.print();
	 	if (temp.isEqual(*pCm1))
	 		cout << "*****  EQUALS *****" << endl;
	 	else
	 		cout << "*****  NOT EQUALS *****" << endl;
	 }
	 delete pCm1;
	 delete pCm2;

	cout << endl << "Checking CFlightInfo" << endl;
	CFlightInfo fInfo1("Paris", 343, 320, 5000);
	CFlightInfo fInfo2("Rome", 506, 220, 4000);
	fInfo1.print();
	fInfo2.print();
	fInfo2.setDest("London");
	cout << "Info after change destination" << endl;
	fInfo2.print();

	cout << endl << "Checking CPlane" << endl;
	CPlane p1(101, 200, "Jumbo");
	CPlane p2(p1);
	CPlane p3 = p1;
	p1.print();
	p2.print();
	p3.print();
	if (p1.isEqual(p2))
		cout << "*****  EQUALS *****" << endl;
	else
		cout << "*****  NOT EQUALS *****" << endl;

	system("pause");
	return 0;
}