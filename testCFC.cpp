#include "CFlightCompany.h"
#include "CCrewMember.h"
#include "CPlane.h"
#include "CFlight.h"
#include "CFlightInfo.h"
#include "CAddress.h"
#include <iostream>
#include <cassert>

using namespace std;

// Global test counters
int totalTests = 0;
int passedTests = 0;

// Test helper function to check test results
void assert_test(bool condition, const string& testName) {
    totalTests++;
    if (condition) {
        passedTests++;
        cout << "[PASS] " << testName << endl;
    } else {
        cout << "[FAIL] " << testName << endl;
    }
}

// Test CFlightCompany constructors
void testCFlightCompanyConstructors() {
    cout << "\n=== Testing CFlightCompany Constructors ===" << endl;
    
    // Test constructor with valid name
    CFlightCompany company1("Delta Airlines");
    assert_test(company1.getName() == "Delta Airlines", "Constructor with valid name");
    
    // Test constructor with empty name (should not set name)
    CFlightCompany company2("");
    assert_test(company2.getName() == "", "Constructor with empty name");
    
    // Test copy constructor
    CFlightCompany company3(company1);
    assert_test(company3.getName() == "Delta Airlines", "Copy constructor - name copied");
}

// Test name setter and getter
void testNameSetterGetter() {
    cout << "\n=== Testing Name Setter and Getter ===" << endl;
    
    CFlightCompany company("Test Company");
    
    // Test valid name change
    company.setName("United Airlines");
    assert_test(company.getName() == "United Airlines", "Set valid name");
    
    // Test empty name (should not change)
    company.setName("");
    assert_test(company.getName() == "United Airlines", "Empty name rejected");
    
    // Test getter returns correct reference
    const string& nameRef = company.getName();
    assert_test(&nameRef == &company.getName(), "Getter returns reference");
}

// Test crew member management
void testCrewMemberManagement() {
    cout << "\n=== Testing Crew Member Management ===" << endl;
    
    CFlightCompany company("Test Airlines");
    
    // Create test addresses and crew members
    CAddress addr1(123, "Main St", "New York");
    CAddress addr2(456, "Second Ave", "Los Angeles");
    CAddress addr3(789, "Third St", "Chicago");
    
    CCrewMember crew1("John Pilot", addr1, 500);
    CCrewMember crew2("Jane Copilot", addr2, 300);
    CCrewMember crew3("Bob Attendant", addr3, 200);
    
    // Test adding first crew member
    bool added1 = company.addCrewMember(crew1);
    assert_test(added1, "First crew member added successfully");
    
    // Test adding second crew member
    bool added2 = company.addCrewMember(crew2);
    assert_test(added2, "Second crew member added successfully");
    
    // Test adding duplicate crew member (should fail)
    bool addedDuplicate = company.addCrewMember(crew1);
    assert_test(!addedDuplicate, "Duplicate crew member rejected");
    
    // Test adding third crew member
    bool added3 = company.addCrewMember(crew3);
    assert_test(added3, "Third crew member added successfully");
}

// Test plane management
void testPlaneManagement() {
    cout << "\n=== Testing Plane Management ===" << endl;
    
    CFlightCompany company("Aviation Corp");
    
    // Create test planes
    CPlane plane1(101, 150, "Boeing737");
    CPlane plane2(102, 200, "Airbus320");
    CPlane plane3(101, 150, "Boeing737"); // Same serial number as plane1
    
    // Test adding first plane
    bool added1 = company.addPlane(plane1);
    assert_test(added1, "First plane added successfully");
    
    // Test adding second plane
    bool added2 = company.addPlane(plane2);
    assert_test(added2, "Second plane added successfully");
    
    // Test adding duplicate plane (same serial number)
    bool addedDuplicate = company.addPlane(plane3);
    assert_test(!addedDuplicate, "Duplicate plane rejected");
    
    // Test getPlane function
    CPlane* retrievedPlane1 = company.getPlane(0);
    assert_test(retrievedPlane1 != nullptr, "getPlane(0) returns valid pointer");
    
    CPlane* retrievedPlane2 = company.getPlane(1);
    assert_test(retrievedPlane2 != nullptr, "getPlane(1) returns valid pointer");
    
    // Test invalid indices
    CPlane* invalidPlane1 = company.getPlane(-1);
    assert_test(invalidPlane1 == nullptr, "getPlane(-1) returns nullptr");
    
    CPlane* invalidPlane2 = company.getPlane(100);
    assert_test(invalidPlane2 == nullptr, "getPlane(100) returns nullptr");
}

// Test flight management
void testFlightManagement() {
    cout << "\n=== Testing Flight Management ===" << endl;
    
    CFlightCompany company("Sky Airways");
    
    // Create test flight info and flights
    CFlightInfo flightInfo1("Paris", 501, 120, 1000);
    CFlightInfo flightInfo2("London", 502, 90, 800);
    CFlightInfo flightInfo3("Paris", 501, 120, 1000); // Same flight number as flight1
    
    CFlight flight1(flightInfo1);
    CFlight flight2(flightInfo2);
    CFlight flight3(flightInfo3);
    
    // Test adding first flight
    bool added1 = company.addFlight(flight1);
    assert_test(added1, "First flight added successfully");
    
    // Test adding second flight
    bool added2 = company.addFlight(flight2);
    assert_test(added2, "Second flight added successfully");
    
    // Test adding duplicate flight (same flight number)
    bool addedDuplicate = company.addFlight(flight3);
    assert_test(!addedDuplicate, "Duplicate flight rejected");
}

// Test crew assignment to flights
void testCrewToFlightAssignment() {
    cout << "\n=== Testing Crew to Flight Assignment ===" << endl;
    
    CFlightCompany company("Assignment Airlines");
    
    // Add crew members
    CAddress addr1(100, "Crew St", "Pilot City");
    CAddress addr2(200, "Staff Ave", "Crew Town");
    
    CCrewMember crew1("Captain Smith", addr1, 1000);
    CCrewMember crew2("First Officer Jones", addr2, 800);
    
    company.addCrewMember(crew1);
    company.addCrewMember(crew2);
    
    // Add flights
    CFlightInfo flightInfo1("Tokyo", 601, 600, 8000);
    CFlight flight1(flightInfo1);
    company.addFlight(flight1);
    
    // Test adding crew to flight
    bool assigned1 = company.addCrewToFlight(0, 601); // Employee 0 to flight 601
    assert_test(assigned1, "Crew member 0 assigned to flight 601");
    
    bool assigned2 = company.addCrewToFlight(1, 601); // Employee 1 to flight 601
    assert_test(assigned2, "Crew member 1 assigned to flight 601");
    
    // Test invalid assignments
    bool invalidCrew = company.addCrewToFlight(99, 601); // Invalid crew number
    assert_test(!invalidCrew, "Invalid crew number rejected");
    
    bool invalidFlight = company.addCrewToFlight(0, 999); // Invalid flight number
    assert_test(!invalidFlight, "Invalid flight number rejected");
}

// Test capacity limits
void testCapacityLimits() {
    cout << "\n=== Testing Capacity Limits ===" << endl;
    
    CFlightCompany company("Capacity Test Airlines");
    
    // Test crew capacity (add MAX_CREWS crew members)
    CAddress testAddr(1, "Test St", "Test City");
    
    // Add crew members up to limit
    int crewAdded = 0;
    for (int i = 0; i < MAX_CREWS; i++) {
        string name = "Crew" + to_string(i);
        CCrewMember crew(name, testAddr, i * 10);
        if (company.addCrewMember(crew)) {
            crewAdded++;
        } else {
            break;
        }
    }
    
    assert_test(crewAdded == MAX_CREWS, "All crew members added up to capacity");
    
    // Try to add one more crew member (should fail)
    CCrewMember extraCrew("Extra Crew", testAddr, 999);
    bool extraCrewAdded = company.addCrewMember(extraCrew);
    assert_test(!extraCrewAdded, "Extra crew member rejected when at capacity");
    
    // Test plane capacity
    int planesAdded = 0;
    for (int i = 0; i < MAX_PLANES; i++) {
        CPlane plane(1000 + i, 100 + i, "TestPlane" + to_string(i));
        if (company.addPlane(plane)) {
            planesAdded++;
        } else {
            break;
        }
    }
    
    assert_test(planesAdded == MAX_PLANES, "All planes added up to capacity");
    
    // Try to add one more plane (should fail)
    CPlane extraPlane(9999, 999, "ExtraPlane");
    bool extraPlaneAdded = company.addPlane(extraPlane);
    assert_test(!extraPlaneAdded, "Extra plane rejected when at capacity");
}

// Test copy constructor with data
void testCopyConstructorWithData() {
    cout << "\n=== Testing Copy Constructor with Data ===" << endl;
    
    CFlightCompany original("Original Airlines");
    
    // Add some data to original
    CAddress addr(50, "Copy St", "Clone City");
    CCrewMember crew("Copy Crew", addr, 100);
    original.addCrewMember(crew);
    
    CPlane plane(201, 180, "CopyPlane");
    original.addPlane(plane);
    
    CFlightInfo flightInfo("Copy Dest", 701, 150, 1200);
    CFlight flight(flightInfo);
    original.addFlight(flight);
    
    // Create copy
    CFlightCompany copy(original);
    
    // Test that copy has same name
    assert_test(copy.getName() == original.getName(), "Copy has same company name");
    
    // Test that copy can access planes
    CPlane* originalPlane = original.getPlane(0);
    CPlane* copiedPlane = copy.getPlane(0);
    
    assert_test(originalPlane != nullptr && copiedPlane != nullptr, "Both original and copy have planes");
    assert_test(originalPlane != copiedPlane, "Copy has different plane instance (deep copy)");
    
    if (originalPlane && copiedPlane) {
        assert_test(originalPlane->isEqual(*copiedPlane), "Copied plane is equal to original");
    }
}

// Test edge cases
void testEdgeCases() {
    cout << "\n=== Testing Edge Cases ===" << endl;
    
    CFlightCompany company("Edge Case Airlines");
    
    // Test getPlane with no planes added
    CPlane* noPlane = company.getPlane(0);
    assert_test(noPlane == nullptr, "getPlane returns nullptr when no planes exist");
    
    // Test crew assignment with no crew or flights
    bool noAssignment = company.addCrewToFlight(0, 100);
    assert_test(!noAssignment, "Crew assignment fails when no crew or flights exist");
    
    // Test very long company name
    string longName(1000, 'A');
    company.setName(longName);
    assert_test(company.getName() == longName, "Very long name accepted");
}

// Test print functionality
void testPrintFunctionality() {
    cout << "\n=== Testing Print Functionality ===" << endl;
    
    CFlightCompany company("Print Test Airlines");
    
    cout << "Testing print output:" << endl;
    company.print();
    
    assert_test(true, "Print function executed without errors");
}

// Main test function
int main() {
    cout << "Starting CFlightCompany Unit Tests..." << endl;
    
    testCFlightCompanyConstructors();
    testNameSetterGetter();
    testCrewMemberManagement();
    testPlaneManagement();
    testFlightManagement();
    testCrewToFlightAssignment();
    testCapacityLimits();
    testCopyConstructorWithData();
    testEdgeCases();
    testPrintFunctionality();
    
    cout << "\n=== CFlightCompany Unit Tests Complete ===" << endl;
    
    // Display test results summary
    cout << "\n=== TEST RESULTS SUMMARY ===" << endl;
    cout << "Tests Passed: " << passedTests << " / " << totalTests << endl;
    
    double successRate = (totalTests > 0) ? (static_cast<double>(passedTests) / totalTests * 100.0) : 0.0;
    cout << "Success Rate: " << successRate << "%" << endl;
    
    if (passedTests == totalTests) {
        cout << "*** ALL TESTS PASSED! ***" << endl;
    } else {
        cout << "*** " << (totalTests - passedTests) << " TEST(S) FAILED ***" << endl;
    }
    
    return (passedTests == totalTests) ? 0 : 1;
}