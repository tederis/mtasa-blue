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

CPlayerConnectMagicPacket::CPlayerConnectMagicPacket(unsigned long ulMagic) : m_ulMagic(ulMagic)
{
}

bool CPlayerConnectMagicPacket::Write(NetBitStreamInterface& BitStream) const
{
    BitStream.Write(m_ulMagic);

    return true;
}
