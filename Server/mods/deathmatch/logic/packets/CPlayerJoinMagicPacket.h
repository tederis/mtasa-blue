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

    unsigned long GetMagic() { return m_ulMagic; }

private:
    unsigned long m_ulMagic;
};
