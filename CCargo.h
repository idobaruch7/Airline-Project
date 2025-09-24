#pragma once
#include <string>
#include <iostream>
#include "CPlane.h"   // מניח שיש מחלקת בסיס למטוסי נוסעים/מטען
using namespace std;

class CCargo : public CPlane
{
private:

    float       maxCargoWeightKg;    // משקל מקסימלי למטען [ק"ג]
    float       maxCargoVolume;    // נפח מקסימלי למטען [מ"ק]

    float       currCargoWeightKg;   // משקל נוכחי (ברירת מחדל 0)
    float       currCargoVolume;   // נפח נוכחי (ברירת מחדל 0)


public:
    //Default Constructor Deletion
    CCargo() = delete;

    // --- בנאים / העתקות / הרס ---
    CCargo(int seatCount,
        const string& modelName,
        float maxCargoWeightKg,
        float maxCargoVolume,
        float currCargoWeightKg = 0.0f,   // דיפולט
        float currCargoVolume = 0.0f);  // דיפולט

    CCargo(const CCargo& other);


    //Destructor
    ~CCargo();


    // --- טעינת מטען ---
    bool load(float weightKg, float volume);

    void takeOff(int minutes) const;

    // --- גטרים ---
    float getMaxCargoWeightKg()   const;
    float getMaxCargoVolume()   const;
    float getCurrCargoWeightKg()  const;
    float getCurrCargoVolume()  const;
    float getAvailableWeightKg()  const;
    float getAvailableVolume()  const;

    // --- סטים ---
    void setMaxCargoWeightKg(float kg);
    void setMaxCargoVolume(float m3);
    void setCurrCargoWeightKg(float kg);
    void setCurrCargoVolume(float m3);

    // --- בדיקות ועזר ---
    bool canLoad(float weightKg, float volumeM3) const;

    // --- אופרטורים ---
    friend ostream& operator<<(ostream& os, const CCargo& cargo);

    // Override the virtual print method
    virtual void print(ostream& os = cout) const override;
};
