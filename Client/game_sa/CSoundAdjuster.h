#pragma once

#include <game/CSoundAdjuster.h>

#define MODEL_AUDIO_AMOUNT 12399

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

class CSoundAdjusterSA : public CSoundAdjuster
{
public:
    CSoundAdjusterSA();

    void Install();

    void SetModelType(unsigned long ulModel, short usType);
    void SetModelDoorSound(unsigned long ulModel, char ucSound);
    void SetModelHornTon(unsigned long ulModel, char ucHornTon);
    void SetModelHornHigh(unsigned long ulModel, float fHornHigh);
    void SetModelEngineOnSound(unsigned long ulModel, short usSound);
    void SetModelEngineOffSound(unsigned long ulModel, short usSound);
};
