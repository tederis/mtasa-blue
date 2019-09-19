/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/game/CBuilding.h
 *  PURPOSE:     Building entity interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#pragma pack(push, 1)
struct VehicleAudioPropertyEntry
{
    __int16 VehicleType;		//	1: +  0
    __int16 EngineOnSound;	    //  2: +  2
    __int16 EngineOffSound;	    //  3: +  4
    __int16 field_4;			//  4: +  6
    float field_5;			    //  5: +  8
    float field_6;			    //  6: + 12
    char HornTon;				//  7: + 16
    char field_8[3];			//	8: + 17, zeros
    float HornHigh;			    //  9: + 20
    char DoorSound;			    // 10: + 24
    char field_11[1];			// 11: + 25, zeros
    char RadioNum;			    // 12: + 26
    char RadioType;			    // 13: + 27
    char field_14;			    // 14: + 28
    char field_15[3];			// 15: + 29, zeros
    float field_16;			    // 16: + 32
};
#pragma pack(pop)

class CSoundAdjuster
{
public:
    virtual void Install() = 0;

    virtual void SetModelType(unsigned long ulModel, short usType) = 0;
    virtual void SetModelDoorSound(unsigned long ulModel, char ucSound) = 0;
    virtual void SetModelHornTon(unsigned long ulModel, char ucHornTon) = 0;
    virtual void SetModelHornHigh(unsigned long ulModel, float fHornHigh) = 0;
    virtual void SetModelEngineOnSound(unsigned long ulModel, short usSound) = 0;
    virtual void SetModelEngineOffSound(unsigned long ulModel, short usSound) = 0;

    virtual void SetModelData(unsigned long ulModel, const VehicleAudioPropertyEntry&& entry) = 0;

    virtual void GetOriginalProperties(std::vector<VehicleAudioPropertyEntry>& entries) = 0;
};
