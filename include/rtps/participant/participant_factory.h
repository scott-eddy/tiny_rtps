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
#ifndef TINY_RTPS_PARTICIPANT_FACTORY_H
#define TINY_RTPS_PARTICIPANT_FACTORY_H

#include "participant.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief factory class used in creation of an RTPS RTPS_Participant_t
 */
#define MAX_NUMBER_PARTICIPANTS 1
typedef struct RTPS_ParticipantFactory_t {
  RTPS_Participant_t *(*CreateParticipant)(struct RTPS_ParticipantFactory_t *, RTPS_ParticipantAttributes_t *);
  RTPS_Participant_t *participant_list[MAX_NUMBER_PARTICIPANTS];
  int number_active_participants;
} RTPS_ParticipantFactory_t;

/**
 * @brief Returns a pointer to the instance of the ParticipantFactory.  If the factory has not yet
 *        been initialized it will return NULL
 * @return pointer to the instance of the ParticipantFactory, NULL if factory has not been initialized
 */
RTPS_ParticipantFactory_t *ParticipantFactory_GetInstance(void);
#define RTPS_ParticipantFactory ParticipantFactory_GetInstance()

/**
 * @brief Initializes the ParticipantFactory singleton.  This will allocate memory for the pointer
 * @return Return code indicating success or failure of the operation
 */
RTPS_ReturnCode_t RTPS_ParticipantFactory_Init();

/**
 * @brief Destroys the instance of the ParticipantFactory singleton.  This should only be done once all of
 *        the participants that the factory has created are also destroyed.  This will free the memory of
 *        the pointer used for the factory
 * @return Return code indicating success or failure of the operation
 */
RTPS_ReturnCode_t ParticipantFactory_Finalize();

#ifdef __cplusplus
}
#endif
#endif //TINY_RTPS_PARTICIPANT_FACTORY_H
