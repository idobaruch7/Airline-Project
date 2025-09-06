#include "CFlight.h"
#include "CFlightInfo.h"
#include "CPlane.h"
#include "CCrewMember.h"
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

// Test CFlight constructors
void testCFlightConstructors() {
    cout << "\n=== Testing CFlight Constructors ===" << endl;
    
    // Test constructor with flight info only
    CFlightInfo info1("Paris", 101, 120, 1000);
    CFlight flight1(info1);
    
    assert_test(flight1.getFlightInfo().getFlightNumber() == 101, "Constructor with info only - flight number");
    assert_test(flight1.getFlightInfo().getDest() == "Paris", "Constructor with info only - destination");
    assert_test(flight1.getPlane() == nullptr, "Constructor with info only - no plane assigned");
    assert_test(flight1.getCrewCount() == 0, "Constructor with info only - no crew");
    assert_test(!flight1.hasPlane(), "Constructor with info only - hasPlane returns false");
    
    // Test constructor with flight info and plane
    CPlane plane1(201, 150, "Boeing737");
    CFlight flight2(info1, &plane1);
    
    assert_test(flight2.getFlightInfo().getFlightNumber() == 101, "Constructor with info and plane - flight number");
    assert_test(flight2.getPlane() != nullptr, "Constructor with info and plane - plane assigned");
    assert_test(flight2.hasPlane(), "Constructor with info and plane - hasPlane returns true");
    assert_test(flight2.getCrewCount() == 0, "Constructor with info and plane - no crew initially");
    
    // Test copy constructor
    CFlight flight3(flight2);
    assert_test(flight3.getFlightInfo().getFlightNumber() == 101, "Copy constructor - flight number");
    assert_test(flight3.getPlane() == flight2.getPlane(), "Copy constructor - same plane pointer");
    assert_test(flight3.getCrewCount() == 0, "Copy constructor - crew count");
}

// Test plane management
void testPlaneManagement() {
    cout << "\n=== Testing Plane Management ===" << endl;
    
    CFlightInfo info("London", 202, 90, 800);
    CFlight flight(info);
    
    // Initially no plane
    assert_test(!flight.hasPlane(), "Initially no plane assigned");
    assert_test(flight.getPlane() == nullptr, "getPlane returns nullptr initially");
    
    // Assign a plane
    CPlane plane1(301, 200, "Airbus320");
    flight.setPlane(&plane1);
    
    assert_test(flight.hasPlane(), "Plane assigned - hasPlane returns true");
    assert_test(flight.getPlane() == &plane1, "getPlane returns correct plane");
    
    // Change plane
    CPlane plane2(302, 180, "Boeing777");
    flight.setPlane(&plane2);
    
    assert_test(flight.getPlane() == &plane2, "Plane changed successfully");
    
    // Remove plane (set to nullptr)
    flight.setPlane(nullptr);
    assert_test(!flight.hasPlane(), "Plane removed - hasPlane returns false");
    assert_test(flight.getPlane() == nullptr, "Plane removed - getPlane returns nullptr");
}

// Test crew management
void testCrewManagement() {
    cout << "\n=== Testing Crew Management ===" << endl;
    
    CFlightInfo info("Rome", 303, 150, 1200);
    CFlight flight(info);
    
    // Create test crew members
    CAddress addr1(10, "Main St", "Tel Aviv");
    CAddress addr2(20, "Second St", "Jerusalem");
    CAddress addr3(30, "Third St", "Haifa");
    
    CCrewMember crew1("John Doe", addr1, 100);
    CCrewMember crew2("Jane Smith", addr2, 200);
    CCrewMember crew3("Bob Johnson", addr3, 150);
    
    // Initially no crew
    assert_test(flight.getCrewCount() == 0, "Initially no crew");
    assert_test(!flight.isCrewFull(), "Initially not crew full");
    assert_test(flight.getCrewMember(0) == nullptr, "getCrewMember returns nullptr for invalid index");
    
    // Add first crew member
    bool added1 = flight.addCrewMember(&crew1);
    assert_test(added1, "First crew member added successfully");
    assert_test(flight.getCrewCount() == 1, "Crew count is 1 after adding first member");
    assert_test(flight.getCrewMember(0) == &crew1, "getCrewMember returns correct crew member");
    
    // Add second crew member
    bool added2 = flight.addCrewMember(&crew2);
    assert_test(added2, "Second crew member added successfully");
    assert_test(flight.getCrewCount() == 2, "Crew count is 2 after adding second member");
    
    // Try to add duplicate crew member (should fail)
    bool added_duplicate = flight.addCrewMember(&crew1);
    assert_test(!added_duplicate, "Duplicate crew member not added");
    assert_test(flight.getCrewCount() == 2, "Crew count unchanged after duplicate attempt");
    
    // Add third crew member
    bool added3 = flight.addCrewMember(&crew3);
    assert_test(added3, "Third crew member added successfully");
    assert_test(flight.getCrewCount() == 3, "Crew count is 3 after adding third member");
    
    // Test crew member removal by reference
    bool removed = flight.removeCrewMember(crew2);
    assert_test(removed, "Crew member removed by reference");
    assert_test(flight.getCrewCount() == 2, "Crew count is 2 after removal");
    
    // Test crew member removal by index
    bool removedByIndex = flight.removeCrewMember(0);
    assert_test(removedByIndex, "Crew member removed by index");
    assert_test(flight.getCrewCount() == 1, "Crew count is 1 after index removal");
    
    // Clear all crew
    flight.clearCrew();
    assert_test(flight.getCrewCount() == 0, "All crew cleared");
    assert_test(flight.getCrewMember(0) == nullptr, "No crew members after clear");
}

// Test crew capacity limits
void testCrewCapacity() {
    cout << "\n=== Testing Crew Capacity Limits ===" << endl;
    
    CFlightInfo info("Tokyo", 404, 600, 8000);
    CFlight flight(info);
    
    CAddress addr(50, "Test St", "Test City");
    
    // Add crew members up to the limit
    for (int i = 0; i < MAX_CREW; i++) {
        string name = "Crew" + to_string(i);
        CCrewMember* crew = new CCrewMember(name, addr, i * 10);
        bool added = flight.addCrewMember(crew);
        assert_test(added, "Crew member " + to_string(i) + " added");
    }
    
    assert_test(flight.getCrewCount() == MAX_CREW, "Maximum crew count reached");
    assert_test(flight.isCrewFull(), "Flight crew is full");
    
    // Try to add one more (should fail)
    CCrewMember extraCrew("Extra Crew", addr, 500);
    bool addedExtra = flight.addCrewMember(&extraCrew);
    assert_test(!addedExtra, "Cannot add crew when at capacity");
    assert_test(flight.getCrewCount() == MAX_CREW, "Crew count unchanged when at capacity");
    
    // Clean up dynamically allocated crew members
    flight.clearCrew();
}

// Test operator+
void testOperatorPlus() {
    cout << "\n=== Testing Operator+ ===" << endl;
    
    CFlightInfo info("Berlin", 505, 180, 1500);
    CFlight originalFlight(info);
    
    CAddress addr(60, "Crew St", "Aviation City");
    CCrewMember crew1("Pilot One", addr, 1000);
    CCrewMember crew2("Copilot Two", addr, 800);
    
    // Test adding crew member with operator+
    CFlight newFlight = originalFlight + &crew1;
    
    assert_test(originalFlight.getCrewCount() == 0, "Original flight unchanged after operator+");
    assert_test(newFlight.getCrewCount() == 1, "New flight has crew member from operator+");
    
    // Test chaining operator+
    CFlight chainedFlight = originalFlight + &crew1 + &crew2;
    assert_test(chainedFlight.getCrewCount() == 2, "Chained operator+ works");
    
    // Test adding duplicate with operator+
    CFlight duplicateFlight = newFlight + &crew1;
    assert_test(duplicateFlight.getCrewCount() == 1, "Duplicate crew not added with operator+");
}

// Test operator==
void testOperatorEquals() {
    cout << "\n=== Testing Operator== ===" << endl;
    
    CFlightInfo info1("Madrid", 606, 120, 1100);
    CFlightInfo info2("Madrid", 606, 120, 1100);
    CFlightInfo info3("Barcelona", 607, 100, 900);
    
    CFlight flight1(info1);
    CFlight flight2(info2);
    CFlight flight3(info3);
    
    // Test flights with same info
    assert_test(flight1 == flight2, "Flights with same info are equal");
    
    // Test flights with different info
    assert_test(!(flight1 == flight3), "Flights with different info are not equal");
    
    // Test with planes
    CPlane plane1(701, 150, "TestPlane1");
    CPlane plane2(701, 150, "TestPlane1");
    CPlane plane3(702, 200, "TestPlane2");
    
    flight1.setPlane(&plane1);
    flight2.setPlane(&plane2);
    
    assert_test(flight1 == flight2, "Flights with same info and equivalent planes are equal");
    
    flight2.setPlane(&plane3);
    assert_test(!(flight1 == flight2), "Flights with different planes are not equal");
    
    // Test with crew
    CAddress addr(70, "Test Ave", "Test Town");
    CCrewMember crew1("Test Pilot", addr, 500);
    CCrewMember crew2("Test Pilot", addr, 500);
    CCrewMember crew3("Different Pilot", addr, 600);
    
    flight1.setPlane(&plane1);
    flight2.setPlane(&plane1);
    
    flight1.addCrewMember(&crew1);
    flight2.addCrewMember(&crew2);
    
    assert_test(flight1 == flight2, "Flights with same crew are equal");
    
    flight2.clearCrew();
    flight2.addCrewMember(&crew3);
    
    assert_test(!(flight1 == flight2), "Flights with different crew are not equal");
}

// Test assignment operator
void testAssignmentOperator() {
    cout << "\n=== Testing Assignment Operator ===" << endl;
    
    CFlightInfo info("Vienna", 808, 90, 700);
    CFlight originalFlight(info);
    
    CPlane plane(801, 120, "TestPlane");
    originalFlight.setPlane(&plane);
    
    CAddress addr(80, "Assignment St", "Copy City");
    CCrewMember crew("Assignment Crew", addr, 300);
    originalFlight.addCrewMember(&crew);
    
    // Test assignment
    CFlightInfo emptyInfo("Empty", 0, 0, 0);
    CFlight assignedFlight(emptyInfo);
    
    assignedFlight = originalFlight;
    
    assert_test(assignedFlight == originalFlight, "Assigned flight equals original");
    assert_test(assignedFlight.getCrewCount() == 1, "Assigned flight has correct crew count");
    assert_test(assignedFlight.getPlane() == &plane, "Assigned flight has correct plane");
    
    // Test self-assignment
    assignedFlight = assignedFlight;
    assert_test(assignedFlight == originalFlight, "Self-assignment works correctly");
}

// Test output operator
void testOutputOperator() {
    cout << "\n=== Testing Output Operator<< ===" << endl;
    
    CFlightInfo info("Amsterdam", 909, 110, 850);
    CFlight flight(info);
    
    cout << "Flight without plane: " << flight << endl;
    
    CPlane plane(901, 140, "OutputTestPlane");
    flight.setPlane(&plane);
    
    cout << "Flight with plane: " << flight << endl;
    
    CAddress addr(90, "Output St", "Display City");
    CCrewMember crew1("Output Crew 1", addr, 400);
    CCrewMember crew2("Output Crew 2", addr, 350);
    
    flight.addCrewMember(&crew1);
    flight.addCrewMember(&crew2);
    
    cout << "Flight with plane and crew: " << flight << endl;
    
    assert_test(true, "Output operator executed without errors");
}

// Test edge cases and error conditions
void testEdgeCases() {
    cout << "\n=== Testing Edge Cases ===" << endl;
    
    CFlightInfo info("EdgeCase", 999, 60, 500);
    CFlight flight(info);
    
    // Test null crew member addition
    bool addedNull = flight.addCrewMember(nullptr);
    assert_test(!addedNull, "Cannot add null crew member");
    
    // Test invalid crew member access
    CCrewMember* invalidCrew = flight.getCrewMember(-1);
    assert_test(invalidCrew == nullptr, "Invalid negative index returns nullptr");
    
    invalidCrew = flight.getCrewMember(100);
    assert_test(invalidCrew == nullptr, "Invalid large index returns nullptr");
    
    // Test removal of non-existent crew member
    CAddress addr(99, "Edge St", "Case City");
    CCrewMember nonExistentCrew("Non Existent", addr, 0);
    bool removedNonExistent = flight.removeCrewMember(nonExistentCrew);
    assert_test(!removedNonExistent, "Cannot remove non-existent crew member");
    
    // Test removal by invalid index
    bool removedInvalidIndex = flight.removeCrewMember(-1);
    assert_test(!removedInvalidIndex, "Cannot remove crew by invalid index");
}

// Main test function
int main() {
    cout << "Starting CFlight Unit Tests..." << endl;
    
    testCFlightConstructors();
    testPlaneManagement();
    testCrewManagement();
    testCrewCapacity();
    testOperatorPlus();
    testOperatorEquals();
    testAssignmentOperator();
    testOutputOperator();
    testEdgeCases();
    
    cout << "\n=== CFlight Unit Tests Complete ===" << endl;
    
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