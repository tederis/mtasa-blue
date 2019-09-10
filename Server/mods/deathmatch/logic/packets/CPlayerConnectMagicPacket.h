/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CPlayerConnectCompletePacket.h
 *  PURPOSE:     Player connect magic packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPacket.h"

class CPlayerConnectMagicPacket : public CPacket
{
public:
    CPlayerConnectMagicPacket(unsigned long ulMagic);

    ePacketID     GetPacketID() const { return static_cast<ePacketID>(PACKET_ID_SERVER_JOIN_MAGIC); };
    unsigned long GetFlags() const { return PACKET_HIGH_PRIORITY | PACKET_RELIABLE | PACKET_SEQUENCED; };

    bool Write(NetBitStreamInterface& BitStream) const;

private:
    unsigned long m_ulMagic;
};
