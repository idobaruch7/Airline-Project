#pragma once
#include <string>
#include <iostream>
#include "CPlane.h"   // ���� ��� ����� ���� ������ ������/����
using namespace std;

class CCargo : public CPlane
{
private:
    int         serialNumber;        // ���� ������
    string      modelName;           // �� ��� (���� "AirBus 403")
    int         seats;               // ���� ������ ����� ����

    float       maxCargoWeightKg;    // ���� ������� ����� [�"�]
    float       maxCargoVolume;    // ��� ������� ����� [�"�]

    float       currCargoWeightKg;   // ���� ����� (����� ���� 0)
    float       currCargoVolume;   // ��� ����� (����� ���� 0)


public:
    //Default Constructor Deletion
    CCargo() = delete;

    // --- ����� / ������ / ��� ---
    CCargo(int seatCount,
        const string& modelName,
        float maxCargoWeightKg,
        float maxCargoVolume,
        float currCargoWeightKg = 0.0f,   // ������
        float currCargoVolume = 0.0f);  // ������

    CCargo(const CCargo& other);


    //Destructor
    ~CCargo();


    // --- ����� ���� ---
    bool load(float weightKg, float volume);

    // --- ����� ---
    float getMaxCargoWeightKg()   const;
    float getMaxCargoVolume()   const;
    float getCurrCargoWeightKg()  const;
    float getCurrCargoVolume()  const;
    float getAvailableWeightKg()  const;
    float getAvailableVolume()  const;

    // --- ���� ---
    void setMaxCargoWeightKg(float kg);
    void setMaxCargoVolume(float m3);
    void setCurrCargoWeightKg(float kg);
    void setCurrCargoVolume(float m3);

    // --- ������ ���� ---
    bool canLoad(float weightKg, float volumeM3) const;
    void print();

};
