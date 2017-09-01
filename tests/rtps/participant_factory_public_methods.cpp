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
#include <gtest/gtest.h>
#include "participant_factory.h"

TEST(ParticipantFactoryPublicTesting, ParticipantCreation) {
  // Arrange
  RTPS_ReturnCode_t ret = RTPS_RETCODE_ERROR;
  if(RTPS_ParticipantFactory){
    FAIL() << "Invalid test, expected the RTPS Participant Factory to not exist";
  }
  Participant_t* participant_ptr = NULL;

}

/**
 * @brief Tests that a newly initialized participant factory can be finalized
 */
TEST(ParticipantFactoryPublicTesting, EmptyFactoryDestruction) {
  // Arrange
  RTPS_ReturnCode_t ret = RTPS_RETCODE_ERROR;
  ret = RTPS_ParticipantFactory_Init();
  if (ret) {
    FAIL() << "Invalid test, problem initializing the singleton factory";
  }
  ASSERT_EQ(0, RTPS_ParticipantFactory->number_active_participants)
                << "Invalid test, expected factory to have no active participants";

  // Act
  ret = ParticipantFactory_Finalize();

  // Assert
  ASSERT_EQ(RTPS_RETCODE_OK, ret);
  ASSERT_TRUE((ParticipantFactory_GetInstance() == NULL));
  ParticipantFactory_Finalize();
}

/**
 * @brief Test that the ParticipantFactroy can be created successfully
 */
TEST(ParticipantFactoryPublicTesting, FactoryCreation) {
  // Arrange
  RTPS_ReturnCode_t ret = RTPS_RETCODE_ERROR;
  if (RTPS_ParticipantFactory) {
    ret = ParticipantFactory_Finalize();
    if (ret) {
      FAIL() << "Invalid test, problem setting up static instance of participant factory";
    }
  }

  // Act
  ret = RTPS_ParticipantFactory_Init();

  // Assert
  ASSERT_TRUE((ParticipantFactory_GetInstance() != NULL));
  ASSERT_EQ(RTPS_RETCODE_OK, ret);
  ParticipantFactory_Finalize();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return 0;
}
