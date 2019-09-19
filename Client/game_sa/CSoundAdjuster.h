#pragma once

#include <game/CSoundAdjuster.h>

#define MODEL_AUDIO_AMOUNT 12399

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

    void SetModelData(unsigned long ulModel, const VehicleAudioPropertyEntry&& entry);

    void GetOriginalProperties(std::vector<VehicleAudioPropertyEntry>& entries);
};
