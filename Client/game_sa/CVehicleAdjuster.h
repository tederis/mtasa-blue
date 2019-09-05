#pragma once

#define VAR_DefaultVehicleStore 0xB1F650 // Vehicle models storage
#define VAR_DefaultVehicleCapacity 212 // Default capacity

#define Addr_CVehicleModelInfoCtor 0x4C75E0 // CVehicleModelInfo contructor
#define Size_CVehicleModelInfo_SA 0x308 // CVehicleModelInfo structure size

#include <sstream>

class DummyVehicleModel
{
public:
    char data[Size_CVehicleModelInfo_SA];

    DummyVehicleModel()
    { 
        static_assert(sizeof(DummyVehicleModel) == Size_CVehicleModelInfo_SA, "Wrong sizeof");
        ((void(__fastcall*)(void*))(Addr_CVehicleModelInfoCtor))(this);
    }

    ~DummyVehicleModel()
    { 
        
    }
};

class CVehicleAdjuster
{
public:
    CVehicleAdjuster();

    void ApplyReflection();

    void AddVehicleModel(DWORD dwModel);

    bool IsModelExists(DWORD dwModel) 
    { 
        return m_Models.find(dwModel) != m_Models.end();
    }

private:
    struct Store
    {
        int                m_nCount{};
        DummyVehicleModel* m_pData;
    };

    Store store;

    std::set<DWORD> m_Models;
};
