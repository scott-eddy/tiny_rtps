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
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(tiny_rtps)

if(NOT WIN32)
  # TODO: Toolchain native needs to support windows builds better
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/toolchains/Toolchain-native.cmake)
endif()

# Note: for development purposes on visual studio if you want to launch 
# an example in debug mode you need to set this variable from 
# THIS CMakeList.txt, as it is the one that calls project()
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
              PROPERTY VS_STARTUP_PROJECT win32_socket)
#-------------------- Build Configuration Variables  -------------------------#
#set(BUILD_NUTTX FALSE CACHE BOOL Enabling this will build NuttX)
set(BUILD_NUTTX FALSE CACHE BOOL "Enabling this will build NuttX, 
                                   only supported on *Nix systems")

set(BUILD_TESTS TRUE CACHE BOOL "Enabling this will build Gtest unit tests")

set(BUILD_EXAMPLES TRUE CACHE BOOL 
                      "Enabling this will build the examples in src/examples")

if(BUILD_NUTTX)
 include(cmake/nuttx/nuttx_config_and_build.cmake)
endif()

#-------------------- Tiny RTPS Sources  -------------------------#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

add_library(tiny_socket
            ${CMAKE_CURRENT_LIST_DIR}/src/networking/tiny_socket.c)

# Allow for controlling of building the test code or not
if (NOT BUILD_NUTTX)
  # NuttX switches the C & C++ Toolchain to be arm-none-eabi which doesn't
  # include threads.  
  # TODO Here we should change back such that we can build NuttX
  # and still build unit tests
  if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
  endif()
endif()

# Allow for building the examples or not
if(BUILD_EXAMPLES)
  add_subdirectory(src/examples)
endif()

