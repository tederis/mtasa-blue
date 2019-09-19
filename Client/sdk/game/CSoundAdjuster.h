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
};
