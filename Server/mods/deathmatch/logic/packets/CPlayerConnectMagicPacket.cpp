/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CPlayerConnectCompletePacket.cpp
 *  PURPOSE:     Player connect magic packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

CPlayerConnectMagicPacket::CPlayerConnectMagicPacket(CFileValidator* pValidator) : m_pValidator(pValidator)
{
}

bool CPlayerConnectMagicPacket::Write(NetBitStreamInterface& BitStream) const
{
    BitStream.Write(m_pValidator->GetEntriesCount());

    for (auto& entry : m_pValidator->GetEntries())
    {
        BitStream.WriteStr(entry.strFileName);
    }

    return true;
}
