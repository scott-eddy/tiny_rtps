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
#ifndef TINY_RTPS_PARTICIPANT_H
#define TINY_RTPS_PARTICIPANT_H

#include "rtps_types.h"
#include "reader.h"
#include "writer.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Attributes not dictated by the RTPS specificatin but necessary for the
 * implementation of the protocol
 */
typedef struct ParticipantAttributes_t {
  unsigned int domain_id;
} ParticipantAttributes_t;

/**
 * @brief an RTPS participant
 */
typedef struct Participant_t {
  GUID_t guid;
  ProtocolVersion_t protocolVersion;
  VendorId_t vendorId;
  ParticipantAttributes_t attributes;
  Locator_t* defaultUnicastLocatorList;
  Locator_t* defaultMulticastLocatorList;
  RTPS_Writer_t* writer_list;
  RTPS_Reader_t* reader_list;
} Participant_t;

/**
 * @ brief factory class used in creation of an RTPS Participant_t
 */
#define MAX_NUMBER_PARTICIPANTS 1
#define NO_PARTICIPANTS_CREATED -1
typedef struct ParticipantFactory_t {
  struct ParticipantFactory_t* (*GetInstance)(void);
  Participant_t* (*CreateParticipant)(struct ParticipantFactory_t*,  ParticipantAttributes_t*);
  Participant_t* participant_list[MAX_NUMBER_PARTICIPANTS];
  int number_created_participants;
} ParticipantFactory_t;

ParticipantFactory_t* ParticipantFactoryInit(void);

#ifdef __cplusplus
}
#endif
#endif //TINY_RTPS_PARTICIPANT_H
