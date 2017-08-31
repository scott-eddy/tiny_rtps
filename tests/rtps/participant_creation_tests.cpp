

#include <gtest/gtest.h>
#include "participant.h"

TEST(ParticipantTesting, FactoryCreationDestruction){
  // Arrange
  RTPS_ReturnCode_t ret = RTPS_RETCODE_ERROR;
  ret = ParticipantFactory_Finalize();

  // Act
  ParticipantFactory_t* participant_factory = ParticipantFactory_GetInstance();
  // Assert
  ASSERT_TRUE((participant_factory != NULL));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return 0;
}
