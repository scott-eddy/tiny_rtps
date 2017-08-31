

#include <gtest/gtest.h>
#include "participant.h"

TEST(ParticipantTesting, FactoryCreationDestruction){
  // Act
  ParticipantFactory_t* participant_factory = ParticipantFactoryInit();
  // Assert
  ASSERT_TRUE((participant_factory != NULL));
}


int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return 0;
}
