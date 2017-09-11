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

#ifndef TINY_RTPS_GUID_PREFIX_H
#define TINY_RTPS_GUID_PREFIX_H

#ifdef __cplusplus
extern "C"{
#endif

#include "platform_types.h"

/**
 * @defgroup GUID_Constants Constants related to the RTPS Globally Unique ID
 * Note, these are preprocessor definitions by design, instead of static const,
 * to reduce code usage
 * @{
 */
#define SIZE_GUID_PREFIX 12
#define GUIDPREFIX_UNKNOWN {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#define SIZE_ENTITY_ID_KEY 3
/**
 * @defgroup RTPS_DEFINED_ENTITY_IDS
 * RTPS_EntityId_t values fully predefined by the RTPS Protocol
 * @{
 */
#define ENTITYID_UNKNOWN {{0x00, 0x00, 0x00}, 0x00}
#define ENTITYID_PARTICIPANT {{0x00,0x00,0x01},0xc1}
#define ENTITYID_SEDP_BUILTIN_TOPIC_WRITER {{0x00,0x00,0x02},0xc2}
#define ENTITYID_SEDP_BUILTIN_TOPIC_READER {{0x00,0x00,0x02},0xc7}
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER {{0x00,0x00,0x03},0xc2}
#define ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER {{0x00,0x00,0x03},0xc7}
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER {{0x00,0x00,0x04},0xc2}
#define ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER {{0x00,0x00,0x04},0xc7}
#define ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER {{0x00,0x01,0x00},0xc2}
#define ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER {{0x00,0x01,0x00},0xc7}
#define ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER {{0x00,0x02,0x00},0xc2}
#define ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER {{0x00,0x02,0x00},0xc7}
/** @} */ // end RTPS_DEFINED_ENTITY_IDS

#define GUID_UNKNOWN {GUIDPREFIX_UNKNOWN, ENTITYID_UNKNOWN}

/** @} */ //end GUID_Constants

/**
 * @brief The Globally Unique Identifier (GUID) prefix.  This is conforment
 * to Section 9.3.1 of the [RTPS Wire Protocal Specification](http://www.omg.org/spec/DDSI-RTPS)
 *
 * implementations of the RTPS protocol are free to use any technique they deem
 * appropriate to generate unique values for the guidPrefix as long as they meet
 * the following constraint:
 * guidPrefix[0] = vendorId[0]
 * guidPrefix[1] = vendorId[1]
 * Where vendorId is a value assigned by the Object Management Group
 */
typedef struct RTPS_GuidPrefix_t {
  octet value[SIZE_GUID_PREFIX];
} RTPS_GuidPrefix_t;

/**
 * @brief The unique identifier of an endpoint within a participant.
 */
typedef struct RTPS_EntityId_t {
  octet entityKey[SIZE_ENTITY_ID_KEY];
  octet entityKind;
} RTPS_EntityId_t;

/**
 * @brief The Globally Unique Identifier (GUID) for a given object on the RTPS network.
 */
typedef struct RTPS_GUID_t {
  RTPS_GuidPrefix_t guidPrefix;
  RTPS_EntityId_t entityId;
} RTPS_GUID_t;

void GenerateGuidValue(RTPS_GuidPrefix_t* prefix_to_assign);


#ifdef __cplusplus
}
#endif

#endif //TINY_RTPS_GUID_PREFIX_H
