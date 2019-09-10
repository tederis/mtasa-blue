/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CPlayerJoinDataPacket.cpp
 *  PURPOSE:     Player join data packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"

bool CPlayerJoinMagicPacket::Read(NetBitStreamInterface& BitStream)
{
    // Read out the stuff
    if (BitStream.Read(m_ulMagic))
        return true;

    return false;
}
