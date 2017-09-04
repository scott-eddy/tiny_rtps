#*****************************************************************************
#   Copyright (C) 2017 Edward Scott. All rights reserved.
#   Authors: Edward Scott <eddy.scott88@gmail.com>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name Tiny RTPS nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#**************************************************************************/
find_package(GTest)

if (NOT ${GTEST_FOUND})
  include(cmake/download_gtest.cmake)
endif()

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(participant_public_creation_tests rtps/participant_factory_public_methods.cpp)
target_compile_definitions(participant_public_creation_tests PUBLIC
    DYNAMIC_STRING_ALLOCATION)
target_link_libraries(participant_public_creation_tests rtps_lib ${GTEST_BOTH_LIBRARIES})
add_test(participant_public_creation_test participant_public_creation_tests)

add_executable(participant_private_creation_tests rtps/participant_factory_private_methods.cpp)
target_compile_definitions(participant_private_creation_tests PUBLIC
    DYNAMIC_STRING_ALLOCATION
    )
target_include_directories(participant_private_creation_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/rtps/participant)
target_link_libraries(participant_private_creation_tests rtps_lib ${GTEST_BOTH_LIBRARIES})
add_test(participant_private_creation_tests participant_private_creation_tests)

# Don't include /usr libraries in coverage, otherwise rely on the CMake add_test to bundle all of the
# tests into one single target that we can then execute
if(BUILD_COVERAGE)
  set(COVERAGE_EXCLUDES '/usr/*')
   SETUP_TARGET_FOR_COVERAGE(
       NAME test_coverage                    # New target name
       EXECUTABLE ctest -j ${PROCESSOR_COUNT} # Executable in PROJECT_BINARY_DIR
   )
endif()
