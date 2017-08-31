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


#include "participant.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief The static particpant factory object. This is accessed via the call to RTPS_ParticipantFactory_GetInstance()
 */
static ParticipantFactory_t* participant_factory_singleton = NULL;

/**
 * TODO good docs
 * @brief
 * @param guid_prefix_value
 */
void AssignTinyVendorId(octet* guid_prefix_value){
  VendorId_t tiny_rtps_id = {VENDORID_TINY_RTPS};
  memcpy(guid_prefix_value, &tiny_rtps_id, sizeof(tiny_rtps_id));
}

/**
 * @brief TODO good docs
 */
Participant_t* CreateParticipant(ParticipantFactory_t* factory, ParticipantAttributes_t* attributes){
  if(factory->number_created_participants < MAX_NUMBER_PARTICIPANTS){
    Participant_t* participant = malloc(sizeof(Participant_t));
    memset(participant, 0, sizeof(*participant));
    AssignTinyVendorId(participant->guid.guidPrefix.value);
    participant->guid.entityId = (EntityId_t) ENTITYID_PARTICIPANT;
    participant->protocolVersion = (ProtocolVersion_t)PROTOCOLVERSION;

    factory->number_created_participants++;
    factory->participant_list[factory->number_created_participants] = participant;
    return participant;
  } else {
    // TODO how to error
    return NULL;
  }

}

ParticipantFactory_t* ParticipantFactory_GetInstance(void){
  if(participant_factory_singleton == NULL) {
    participant_factory_singleton = malloc(sizeof(ParticipantFactory_t)); //TODO dont malloc here, instead abstract
    participant_factory_singleton->CreateParticipant = &CreateParticipant;
    participant_factory_singleton->number_created_participants = NO_PARTICIPANTS_CREATED;
    for(int i = 0; i < MAX_NUMBER_PARTICIPANTS; ++i) {
      participant_factory_singleton->participant_list[i] = NULL;
    }
  }
  return participant_factory_singleton;
}



/**
 * @brief TODO good docs
 * @return
 */
RTPS_ReturnCode_t ParticipantFactory_Finalize() {
  RTPS_ReturnCode_t ret = RTPS_RETCODE_ERROR;
  if (participant_factory_singleton == NULL) {
    ret = RTPS_RETCODE_OK;
  } else {
    free(participant_factory_singleton); // TODO don't blindly free here, need to check that all participants created by factory are destroyed properly
    ret = RTPS_RETCODE_OK;
  }
  return ret;
}

