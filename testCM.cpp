//#include "CCrewMember.h"
//#include "CAddress.h"
//#include <iostream>
//#include <cassert>
//
//using namespace std;
//
//// Global test counters
//int totalTests = 0;
//int passedTests = 0;
//
//// Test helper function to check test results
//void assert_test(bool condition, const string& testName) {
//    totalTests++;
//    if (condition) {
//        passedTests++;
//        cout << "[PASS] " << testName << endl;
//    } else {
//        cout << "[FAIL] " << testName << endl;
//    }
//}
//
//// Test basic constructor numbering
//void testBasicConstructorNumbering() {
//    cout << "\n=== Testing Basic Constructor Numbering ===" << endl;
//    
//    CAddress addr1(123, "Main St", "New York");
//    CAddress addr2(456, "Second Ave", "Los Angeles");
//    
//    // Create crew members using different constructors
//    CCrewMember crew1("John Pilot", addr1, 500);
//    CCrewMember crew2("Jane Copilot", addr2, 300);
//    CCrewMember crew3("Bob Attendant", 200);  // Constructor without address
//    
//    // Test that member numbers are assigned and incrementing
//    int member1 = crew1.getMember();
//    int member2 = crew2.getMember();
//    int member3 = crew3.getMember();
//    
//    cout << "Created crew members:" << endl;
//    cout << "  John Pilot (with address): Member #" << member1 << endl;
//    cout << "  Jane Copilot (with address): Member #" << member2 << endl;
//    cout << "  Bob Attendant (no address): Member #" << member3 << endl;
//    
//    assert_test(member1 >= 1000, "First crew member has valid number (>= 1000)");
//    assert_test(member2 == member1 + 1, "Second crew member number increments by 1");
//    assert_test(member3 == member2 + 1, "Third crew member number increments by 1");
//    assert_test(member1 != member2, "Different crew members have different numbers");
//    assert_test(member2 != member3, "Consecutive crew members have different numbers");
//}
//
//// Test sequential numbering across multiple instances
//void testSequentialNumbering() {
//    cout << "\n=== Testing Sequential Numbering ===" << endl;
//    
//    CAddress testAddr(789, "Test St", "Test City");
//    
//    // Create multiple crew members and verify sequential numbering
//    const int numCrewMembers = 5;
//    CCrewMember* crewArray[numCrewMembers];
//    int memberNumbers[numCrewMembers];
//    
//    cout << "Creating " << numCrewMembers << " crew members:" << endl;
//    
//    // Create crew members and store their numbers
//    for (int i = 0; i < numCrewMembers; i++) {
//        string name = "Crew" + to_string(i);
//        crewArray[i] = new CCrewMember(name, testAddr, i * 10);
//        memberNumbers[i] = crewArray[i]->getMember();
//        cout << "  " << name << ": Member #" << memberNumbers[i] << endl;
//    }
//    
//    // Verify sequential numbering
//    for (int i = 1; i < numCrewMembers; i++) {
//        bool isSequential = (memberNumbers[i] == memberNumbers[i-1] + 1);
//        assert_test(isSequential, "Member " + to_string(i) + " has sequential number");
//    }
//    
//    // Verify all numbers are unique
//    bool allUnique = true;
//    for (int i = 0; i < numCrewMembers && allUnique; i++) {
//        for (int j = i + 1; j < numCrewMembers; j++) {
//            if (memberNumbers[i] == memberNumbers[j]) {
//                allUnique = false;
//                break;
//            }
//        }
//    }
//    assert_test(allUnique, "All crew member numbers are unique");
//    
//    // Clean up
//    for (int i = 0; i < numCrewMembers; i++) {
//        delete crewArray[i];
//    }
//}
//
//// Test copy constructor numbering behavior (should preserve same number)
//void testCopyConstructorNumbering() {
//    cout << "\n=== Testing Copy Constructor Numbering ===" << endl;
//    
//    CAddress addr(100, "Copy St", "Clone City");
//    CCrewMember original("Original Crew", addr, 1000);
//    
//    int originalMemberNumber = original.getMember();
//    cout << "Original crew member: Member #" << originalMemberNumber << endl;
//    
//    // Create copy using copy constructor
//    CCrewMember copy(original);
//    int copyMemberNumber = copy.getMember();
//    
//    cout << "Copy of crew member: Member #" << copyMemberNumber << endl;
//    cout << "Copy should have SAME number as original (same person)" << endl;
//    
//    // Copy should have SAME member number (it's the same crew member)
//    assert_test(copyMemberNumber == originalMemberNumber, "Copy has same member number as original");
//    
//    // Verify copy is considered equal to original
//    assert_test(copy.isEqual(original), "Copy is equal to original");
//    assert_test(copy == original, "Copy equals original (operator==)");
//    
//    // Additional test: verify copy doesn't affect sequential numbering for NEW crew members
//    CCrewMember afterCopy("After Copy", addr, 500);
//    int afterCopyNumber = afterCopy.getMember();
//    
//    cout << "New crew member after copy: Member #" << afterCopyNumber << endl;
//    cout << "Should be " << (originalMemberNumber + 1) << " (next sequential)" << endl;
//    
//    // This should be the next sequential number after the original
//    bool correctSequence = (afterCopyNumber == originalMemberNumber + 1);
//    assert_test(correctSequence, "New crew member after copy gets next sequential number");
//}
//
//// Test multiple copies preserve same numbering
//void testMultipleCopiesNumbering() {
//    cout << "\n=== Testing Multiple Copies Numbering ===" << endl;
//    
//    CAddress addr(200, "Multiple St", "Copy Town");
//    CCrewMember original("Original for Multiple Copies", addr, 750);
//    
//    int originalNumber = original.getMember();
//    cout << "Original: Member #" << originalNumber << endl;
//    
//    // Create multiple copies
//    CCrewMember copy1(original);
//    CCrewMember copy2(original);
//    CCrewMember copy3(copy1);  // Copy of a copy
//    
//    int copy1Number = copy1.getMember();
//    int copy2Number = copy2.getMember();
//    int copy3Number = copy3.getMember();
//    
//    cout << "Copy 1: Member #" << copy1Number << endl;
//    cout << "Copy 2: Member #" << copy2Number << endl;
//    cout << "Copy 3 (copy of copy): Member #" << copy3Number << endl;
//    cout << "All copies should have same number: " << originalNumber << endl;
//    
//    // All copies should have same number as original (they represent same crew member)
//    assert_test(copy1Number == originalNumber, "Copy 1 has same number as original");
//    assert_test(copy2Number == originalNumber, "Copy 2 has same number as original");
//    assert_test(copy3Number == originalNumber, "Copy 3 (copy of copy) has same number as original");
//    
//    // All copies should be equal to each other
//    assert_test(copy1 == copy2, "Copy 1 equals Copy 2");
//    assert_test(copy2 == copy3, "Copy 2 equals Copy 3");
//    assert_test(copy1 == original, "Copy 1 equals original");
//}
//
//// Test assignment operator copies member number
//void testAssignmentOperatorNumbering() {
//    cout << "\n=== Testing Assignment Operator Numbering ===" << endl;
//    
//    CAddress addr1(300, "Assignment St", "Operator City");
//    CAddress addr2(400, "Target St", "Destination City");
//    
//    CCrewMember source("Source Crew", addr1, 800);
//    CCrewMember target("Target Crew", addr2, 600);
//    
//    int sourceNumber = source.getMember();
//    int targetNumberBefore = target.getMember();
//    
//    cout << "Before assignment:" << endl;
//    cout << "  Source: Member #" << sourceNumber << endl;
//    cout << "  Target: Member #" << targetNumberBefore << endl;
//    
//    // Perform assignment
//    target = source;
//    
//    int targetNumberAfter = target.getMember();
//    
//    cout << "After assignment (target = source):" << endl;
//    cout << "  Source: Member #" << source.getMember() << " (unchanged)" << endl;
//    cout << "  Target: Member #" << targetNumberAfter << " (copied from source)" << endl;
//    
//    // Assignment should copy the member number (target becomes copy of source)
//    assert_test(targetNumberAfter == sourceNumber, "Assignment copies member number from source");
//    assert_test(targetNumberAfter != targetNumberBefore, "Assignment changes target's member number");
//    assert_test(source.getMember() == sourceNumber, "Assignment doesn't change source member number");
//    assert_test(target == source, "After assignment, target equals source");
//}
//
//// Test numbering with mixed constructor types
//void testMixedConstructorNumbering() {
//    cout << "\n=== Testing Mixed Constructor Types Numbering ===" << endl;
//    
//    CAddress addr(500, "Mixed St", "Constructor City");
//    
//    // Use different constructors in sequence
//    CCrewMember crew1("With Address", addr, 100);
//    CCrewMember crew2("Without Address", 200);
//    CCrewMember crew3("Another With Address", addr, 300);
//    CCrewMember crew4("Another Without Address", 400);
//    
//    int num1 = crew1.getMember();
//    int num2 = crew2.getMember();
//    int num3 = crew3.getMember();
//    int num4 = crew4.getMember();
//    
//    cout << "Mixed constructor types:" << endl;
//    cout << "  With Address: Member #" << num1 << endl;
//    cout << "  Without Address: Member #" << num2 << endl;
//    cout << "  With Address: Member #" << num3 << endl;
//    cout << "  Without Address: Member #" << num4 << endl;
//    cout << "Expected sequence: " << num1 << ", " << (num1+1) << ", " << (num1+2) << ", " << (num1+3) << endl;
//    
//    // All should be sequential regardless of constructor type
//    assert_test(num2 == num1 + 1, "Constructor without address follows sequence");
//    assert_test(num3 == num2 + 1, "Back to constructor with address follows sequence");
//    assert_test(num4 == num3 + 1, "Second constructor without address follows sequence");
//    
//    // Verify all are unique
//    assert_test(num1 != num2 && num2 != num3 && num3 != num4, "All mixed constructor numbers are unique");
//}
//
//// Test member number range and validity
//void testMemberNumberValidRange() {
//    cout << "\n=== Testing Member Number Valid Range ===" << endl;
//    
//    CAddress addr(600, "Range St", "Validity City");
//    CCrewMember crew("Range Test", addr, 150);
//    
//    int memberNumber = crew.getMember();
//    
//    cout << "Range test crew member: Member #" << memberNumber << endl;
//    cout << "Expected: >= 1000 (starting value)" << endl;
//    
//    // Based on the implementation, numbers should start at 1000
//    assert_test(memberNumber >= 1000, "Member number is in valid range (>= 1000)");
//    assert_test(memberNumber < 1000000, "Member number is reasonable (< 1000000)");
//    
//    // Test that member number is positive
//    assert_test(memberNumber > 0, "Member number is positive");
//}
//
//// Test numbering consistency with equality operations
//void testNumberingWithEqualityOperations() {
//    cout << "\n=== Testing Numbering with Equality Operations ===" << endl;
//    
//    CAddress addr(700, "Equality St", "Comparison City");
//    CCrewMember crew1("Equal Test 1", addr, 250);
//    CCrewMember crew2("Equal Test 2", addr, 250);
//    
//    cout << "Two different crew members with same data:" << endl;
//    cout << "  Crew 1: Member #" << crew1.getMember() << endl;
//    cout << "  Crew 2: Member #" << crew2.getMember() << endl;
//    cout << "Should NOT be equal (different people)" << endl;
//    
//    // Different crew members should not be equal (even with same data)
//    bool areEqual = crew1.isEqual(crew2);
//    bool operatorEqual = (crew1 == crew2);
//    
//    assert_test(!areEqual, "Different crew members are not equal (isEqual)");
//    assert_test(!operatorEqual, "Different crew members are not equal (operator==)");
//    
//    // Copy should be equal to original (same crew member)
//    CCrewMember copy(crew1);
//    
//    cout << "Copy of crew 1:" << endl;
//    cout << "  Original: Member #" << crew1.getMember() << endl;
//    cout << "  Copy: Member #" << copy.getMember() << endl;
//    cout << "Should be equal (same person)" << endl;
//    
//    bool copyEqual = crew1.isEqual(copy);
//    bool copyOperatorEqual = (crew1 == copy);
//    
//    assert_test(copyEqual, "Copy is equal to original (isEqual)");
//    assert_test(copyOperatorEqual, "Copy is equal to original (operator==)");
//}
//
//// Test that only constructors increment the counter, not copies
//void testOnlyConstructorsIncrementCounter() {
//    cout << "\n=== Testing Only Constructors Increment Counter ===" << endl;
//    
//    CAddress addr(800, "Counter St", "Increment City");
//    
//    // Create original crew member
//    CCrewMember original("Counter Test", addr, 400);
//    int originalNumber = original.getMember();
//    
//    cout << "Original crew member: Member #" << originalNumber << endl;
//    
//    // Create several copies - these should NOT increment the counter
//    CCrewMember copy1(original);
//    CCrewMember copy2(original);
//    CCrewMember copy3(copy1);
//    
//    cout << "Copies (should NOT increment counter):" << endl;
//    cout << "  Copy 1: Member #" << copy1.getMember() << endl;
//    cout << "  Copy 2: Member #" << copy2.getMember() << endl;
//    cout << "  Copy 3: Member #" << copy3.getMember() << endl;
//    
//    // Now create a NEW crew member - this SHOULD increment
//    CCrewMember newCrew("New Crew", addr, 500);
//    int newCrewNumber = newCrew.getMember();
//    
//    cout << "New crew member (should increment): Member #" << newCrewNumber << endl;
//    cout << "Expected: " << (originalNumber + 1) << " (next after original)" << endl;
//    
//    // The new crew member should have the next sequential number
//    assert_test(newCrewNumber == originalNumber + 1, "New crew member gets next sequential number after copies");
//    
//    // All copies should still have original number
//    assert_test(copy1.getMember() == originalNumber, "Copy 1 maintains original number");
//    assert_test(copy2.getMember() == originalNumber, "Copy 2 maintains original number");
//    assert_test(copy3.getMember() == originalNumber, "Copy 3 maintains original number");
//}
//
//// Main test function
//int main() {
//    cout << "Starting CCrewMember Numbering System Unit Tests..." << endl;
//    cout << "NOTE: Copy constructor should preserve member numbers (same crew member)." << endl;
//    cout << "======================================================================" << endl;
//    
//    testBasicConstructorNumbering();
//    testSequentialNumbering();
//    testCopyConstructorNumbering();
//    testMultipleCopiesNumbering();
//    testAssignmentOperatorNumbering();
//    testMixedConstructorNumbering();
//    testMemberNumberValidRange();
//    testNumberingWithEqualityOperations();
//    testOnlyConstructorsIncrementCounter();
//    
//    cout << "\n=== CCrewMember Numbering System Tests Complete ===" << endl;
//    
//    // Display test results summary
//    cout << "\n=== TEST RESULTS SUMMARY ===" << endl;
//    cout << "Tests Passed: " << passedTests << " / " << totalTests << endl;
//    
//    double successRate = (totalTests > 0) ? (static_cast<double>(passedTests) / totalTests * 100.0) : 0.0;
//    cout << "Success Rate: " << successRate << "%" << endl;
//    
//    if (passedTests == totalTests) {
//        cout << "*** ALL TESTS PASSED! ***" << endl;
//    } else {
//        cout << "*** " << (totalTests - passedTests) << " TEST(S) FAILED ***" << endl;
//    }
//    
//    cout << "\nDesign Notes:" << endl;
//    cout << "- Regular constructors increment the member counter (new crew members)" << endl;
//    cout << "- Copy constructor preserves member number (same crew member)" << endl;
//    cout << "- Assignment operator copies member number (target becomes copy of source)" << endl;
//    cout << "- Member numbers start at 1000 and increment sequentially" << endl;
//    
//    return (passedTests == totalTests) ? 0 : 1;
//}