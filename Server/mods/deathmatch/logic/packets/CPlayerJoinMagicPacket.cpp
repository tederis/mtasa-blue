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
    if (BitStream.Read(m_uiCount) != true)
        return false;

    m_Hashes.clear();
    m_Hashes.reserve(m_uiCount);

    for (int i = 0; i < m_uiCount; ++i)
    {
        SString strHash;
        if (BitStream.ReadStr(strHash) != true)
            return false;

        m_Hashes.emplace_back(std::move(strHash));
    }

    return true;
}
