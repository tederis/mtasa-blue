#include "StdInc.h"
#include "gamesa_renderware.h"

VehicleAudioPropertyEntry VehicleAudioProperties[MODEL_AUDIO_AMOUNT];

DWORD CONTINUE_SetupCommonData = 0x5B8FC3;
DWORD FN_SetupCommonData = 0x590D00;

void _declspec(naked) HOOK_SetupCommonData()
{
    _asm
    {
        pushad
    }

    if (pGame)
        pGame->GetSoundAdjuster()->Install();

    _asm
    {
        popad
        call    FN_SetupCommonData
        jmp     CONTINUE_SetupCommonData
    }
}

CSoundAdjusterSA::CSoundAdjusterSA()
{
    // Copy all the default sound properties
    memcpy(&VehicleAudioProperties[0], (void*)0x860AF0, sizeof(VehicleAudioPropertyEntry) * 212);

    // Fill the extra models
    for (int i = 212; i < 12400; ++i)
    {
        memcpy(&VehicleAudioProperties[i], (void*)(0x860AF0 + sizeof(VehicleAudioPropertyEntry)*156), sizeof(VehicleAudioPropertyEntry));
    }

    HookInstall(0x5B8FBE, (DWORD)HOOK_SetupCommonData, 5);
}

void CSoundAdjusterSA::Install()
{
    MemPut<DWORD>((void*)0x4F5C26, (DWORD)VehicleAudioProperties);
    MemPut<DWORD>((void*)0x4F77CD, (DWORD)VehicleAudioProperties);
}

void CSoundAdjusterSA::SetModelType(unsigned long ulModel, short usType)
{
    unsigned long ulIndex = ulModel - 400;
    if (ulIndex >= MODEL_AUDIO_AMOUNT)
        return; 

    VehicleAudioPropertyEntry& entry = VehicleAudioProperties[ulIndex];
    entry.VehicleType = usType;
}

void CSoundAdjusterSA::SetModelDoorSound(unsigned long ulModel, char ucSound)
{
    unsigned long ulIndex = ulModel - 400;
    if (ulIndex >= MODEL_AUDIO_AMOUNT)
        return; 

    VehicleAudioPropertyEntry& entry = VehicleAudioProperties[ulIndex];
    entry.DoorSound = ucSound;
}

void CSoundAdjusterSA::SetModelHornTon(unsigned long ulModel, char ucHornTon)
{
    unsigned long ulIndex = ulModel - 400;
    if (ulIndex >= MODEL_AUDIO_AMOUNT)
        return; 

    VehicleAudioPropertyEntry& entry = VehicleAudioProperties[ulIndex];
    entry.HornTon = ucHornTon;
}

void CSoundAdjusterSA::SetModelHornHigh(unsigned long ulModel, float fHornHigh)
{
    unsigned long ulIndex = ulModel - 400;
    if (ulIndex >= MODEL_AUDIO_AMOUNT)
        return; 

    VehicleAudioPropertyEntry& entry = VehicleAudioProperties[ulIndex];
    entry.HornHigh = fHornHigh;
}

void CSoundAdjusterSA::SetModelEngineOnSound(unsigned long ulModel, short usSound)
{
    unsigned long ulIndex = ulModel - 400;
    if (ulIndex >= MODEL_AUDIO_AMOUNT)
        return; 

    VehicleAudioPropertyEntry& entry = VehicleAudioProperties[ulIndex];
    entry.EngineOnSound = usSound;
}

void CSoundAdjusterSA::SetModelEngineOffSound(unsigned long ulModel, short usSound)
{
    unsigned long ulIndex = ulModel - 400;
    if (ulIndex >= MODEL_AUDIO_AMOUNT)
        return; 

    VehicleAudioPropertyEntry& entry = VehicleAudioProperties[ulIndex];
    entry.EngineOffSound = usSound;
}

void CSoundAdjusterSA::SetModelData(unsigned long ulModel, const VehicleAudioPropertyEntry&& entry)
{
    unsigned long ulIndex = ulModel - 400;
    if (ulIndex >= MODEL_AUDIO_AMOUNT)
        return; 

    VehicleAudioProperties[ulIndex] = std::move(entry);
}

void CSoundAdjusterSA::GetOriginalProperties(std::vector<VehicleAudioPropertyEntry>& entries)
{
    entries.assign(VehicleAudioProperties, VehicleAudioProperties + 212);
}
