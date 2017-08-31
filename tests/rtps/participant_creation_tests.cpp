

#include <gtest/gtest.h>
#include "participant.h"

TEST(ParticipantTesting, ParticipantCreation){
  // Arrange
  ParticipantFactory_t* participant_factory = ParticipantFactoryInit();
  ParticipantAttributes_t attributes;

  //Act
  Participant_t* participant = participant_factory->CreateParticipant(participant_factory, &attributes);
  // Assert
  ASSERT_TRUE((participant != NULL));

  free(participant);
}

TEST(ParticipantTesting, FactoryCreationDestruction){
  // Act
  ParticipantFactory_t* participant_factory = ParticipantFactoryInit();
  // Assert
  ASSERT_TRUE((participant_factory != NULL));
}


int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
