/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CPlayerJoinDataPacket.h
 *  PURPOSE:     Player join data packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPacket.h"
#include "../../Config.h"

class CPlayerJoinMagicPacket : public CPacket
{
public:
    virtual bool  RequiresSourcePlayer() const { return false; }
    ePacketID     GetPacketID() const { return static_cast<ePacketID>(PACKET_ID_PLAYER_JOINMAGIC); };
    unsigned long GetFlags() const { return PACKET_HIGH_PRIORITY | PACKET_RELIABLE | PACKET_SEQUENCED; };

    bool Read(NetBitStreamInterface& BitStream);

    unsigned int GetCount() const { return m_uiCount; }
    const std::vector<SString>& GetHashes() const { return m_Hashes; }

private:
    unsigned int m_uiCount;
    std::vector<SString> m_Hashes;
};
