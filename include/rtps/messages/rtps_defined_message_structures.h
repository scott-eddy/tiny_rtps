/******************************************************************************
 *   Copyright (C) 2017 Edward Scott. All rights reserved.
 *   Authors: Edward Scott <eddy.scott88@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Tiny RTPS nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************/
 #ifndef TINY_RTPS_MESSAGE_STRUCTURES
 #define TINY_RTPS_MESSAGE_STRUCTURES

 #ifdef __cplusplus
 extern "C"{
 #endif

#include "guid.h"
#include "platform_types.h"

#define SIZE_RTPS_HEADER_PREFIX 4
/**
 * @ brief the header for an RTPS message.  This is included in all messages.
 *
 * The byte layout of the message as defined Platform specific model of the
 * standard is:
 * Header:
 * 0...2...........8...............16.............24...............32
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |       'R'     |      'T'      |      'P'      |      'S'      |
 * +---------------+---------------+---------------+---------------+
 * |    ProtocolVersion version    |       VendorId vendorId       |
 * +---------------+---------------+---------------+---------------+
 * |                                                               |
 * +                                                               +
 * |                        GuidPrefix guidPrefix                  |
 * +                                                               +
 * |                                                               |
 * +---------------+---------------+---------------+---------------+
 */
 typedef struct RTPS_Header_t {
   octet prefix[SIZE_RTPS_HEADER_PREFIX]; //Always 'R','T','P','S'
   ProtocolVersion_t version;
   VendorId_t vendorId;
   GuidPrefix_t guidPrefix;
 } RTPS_Header_t;

/**
 * @breif Enumeration of submessage kind used in  the SubmessageID field of
 * the SubmessageHeader_t type
 *
 * Submessages with ID's 0x80 to 0xff (inclusive) are vendor-specific; they will
 * not be defined by future versions of the protocol. Their interpretation is
 * dependent on the vendorId that is current when the Submessage is encountered.
 *
 * TODO: Eddy 8/2017, this is stored in the CDR representation as octet
 */
enum SubmessageKind {
  PAD = 0x01, /* Pad */
  ACKNACK = 0x06, /* AckNack */
  HEARTBEAT = 0x07, /* Heartbeat */
  GAP = 0x08, /* Gap */
  INFO_TS = 0x09, /* InfoTimestamp */
  INFO_SRC = 0x0c, /* InfoSource */
  INFO_REPLY_IP4 = 0x0d, /* InfoReplyIp4 */
  INFO_DST = 0x0e, /* InfoDestination */
  INFO_REPLY = 0x0f, /* InfoReply */
  NACK_FRAG = 0x12, /* NackFrag */
  HEARTBEAT_FRAG = 0x13, /* HeartbeatFrag */
  DATA = 0x15, /* Data */
  DATA_FRAG = 0x16, /* DataFrag */
};

/**
 * @brief Leading structure of all Submessages
 *
 * The submessageLength is defined as the number of octets from the start of the
 * contents of the Submessage to the start of the next Submessage header, which
 * is stored in the field octetsToNextHeader
 *
 * The PSM maps the EndiannessFlag flag into the least-significant bit (LSB) of
 * the flags. This bit is therefore always present in all Submessages and
 * represents the endianness used to encode the information in the Submessage.
 * The EndiannessFlag is represented with the literal ‘E’. E=0 means big-endian,
 * E=1 means little-endian. The value of the EndiannessFlag can be obtained Via:
 * E = SubmessageHeader.flags & 0x01
 * Other bits in the flags have interpretations that depend on the type of Submessage.
 */
typedef struct SubmessageHeader_t {
  octet submessageId;
  octet flags;
  uint16_t octetsToNextHeader;
} SubmessageHeader_t;

/**
 * @brief TODO Eddy 8/2017 meaningfull doxy comment
 */
typedef struct AckNack_Submessage_t {
  SubmessageHeader_t header;
  EntityId_t readerId;
  EntityId_t writerId;
  SequenceNumberSet_t readerSNState; // TODO Eddy 8/2017, This uses a sequence but we use a fixed size, how do we handle this?
  Count_t count;
} AckNack_Submessage_t;


 #ifdef __cplusplus
 }
 #endif
#endif //TINY_RTPS_MESSAGE_STRUCTURES
