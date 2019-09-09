#include "StdInc.h"

#include "gamesa_renderware.h"

DWORD CONTINUE_CVehicleModelInfo_Ctor = 0x4C75E9;

// Initialises CVehicleModelInfo::m_apDirtMaterials at CVehicleModelInfo constructor
void _declspec(naked) HOOK_FixConstructor()
{
    static void* modelInfoPtr;

    _asm
        {
        mov     modelInfoPtr, ecx
        pushad
        }

    MemSetFast((char*)(modelInfoPtr) + 0x230, 0, 16 * 4);

    _asm
    {
        popad
        jmp     CONTINUE_CVehicleModelInfo_Ctor
    }
}

DWORD CONTINUE_LoadingScreenLoadingFile = 0x5B9258;

void _declspec(naked) HOOK_LoadingScreenLoadingFile()
{
    _asm
    {
        pushad
    }

    if (pGame) pGame->GetVehicleAdjuster()->ApplyReflection();

    _asm
    {
        popad
        jmp     CONTINUE_LoadingScreenLoadingFile
    }
}

DWORD FN_AddVehicleModel = 0x4C6770;
DWORD CONTINUE_AddVehicleModel = 0x5B6FD6;

void _declspec(naked) HOOK_AddVehicleModel()
{
    static DWORD dwAddVehicleModel = 0;

    _asm
    {
        mov dwAddVehicleModel, ecx
        pushad
    }

    if (pGame) pGame->GetVehicleAdjuster()->AddVehicleModel(dwAddVehicleModel);

    _asm
    {
        popad
        call    FN_AddVehicleModel
        jmp     CONTINUE_AddVehicleModel
    }
}

CVehicleAdjuster::CVehicleAdjuster()
{
    // Well, R* forgot to initialize CVehicleModelInfo::m_apDirtMaterials and this directly affects the adjuster
    // since it needs proper constructors. It wasn't noticeable before because the .data seg is initialized with 0's
    // Not doing this fix, the game will crash whenever a vehicle gets rendered
    HookInstall(0x4C75E4, (DWORD)HOOK_FixConstructor, 5);
    HookInstall(0x5B9253, (DWORD)HOOK_LoadingScreenLoadingFile, 5);
    HookInstall(0x5B6FD1, (DWORD)HOOK_AddVehicleModel, 5);

    store.m_nCount = 0;
    store.m_pData = new DummyVehicleModel[500];

    MemPut<DWORD>((void*)0x4C64ED, (DWORD)&store.m_nCount);
    MemPut<DWORD>((void*)0x4C6508, (DWORD)&store.m_nCount);
    MemPut<DWORD>((void*)0x4C6604, (DWORD)&store.m_nCount);
    MemPut<DWORD>((void*)0x4C6771, (DWORD)&store.m_nCount);
    MemPut<DWORD>((void*)0x4C6786, (DWORD)&store.m_nCount);
    MemPut<DWORD>((void*)0x4C6853, (DWORD)&store.m_nCount);

    MemPut<DWORD>((void*)0x4C64F8, (DWORD)store.m_pData);
    MemPut<DWORD>((void*)0x4C6780, (DWORD)store.m_pData);
}

void CVehicleAdjuster::ApplyReflection()
{
    MemPutFast<DWORD>((void*)VAR_DefaultVehicleStore, VAR_DefaultVehicleCapacity);
    MemCpyFast((void*)(VAR_DefaultVehicleStore + 4), store.m_pData, VAR_DefaultVehicleCapacity * Size_CVehicleModelInfo_SA);
}

void CVehicleAdjuster::AddVehicleModel(DWORD dwModel)
{
    m_Models.emplace(dwModel);
}
