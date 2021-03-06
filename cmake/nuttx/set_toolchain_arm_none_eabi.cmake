
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

####
# Function set_toolchain_arm_none_eabi
# ------------------------------------
# This function sets C and C++ compiler to be arm-none-eabi and prints the 
# version to the terminal
#
# included CMake:
#   Toolchain-arm-none-eabi.cmake
#
# Variables set:
#   CMAKE_C_COMPILER
#   CMAKE_CXX_COMPILER 
#   CMAKE_EXE_LINKER_FLAGS
#
####
function(set_toolchain_arm_none_eabi)
  set(BUILD_SHARED_LIBS OFF)
  # Set the toolchain for ARM
  include(${CMAKE_SOURCE_DIR}/cmake/toolchains/Toolchain-arm-none-eabi.cmake)

  # print full c compiler version
  execute_process(COMMAND ${CMAKE_C_COMPILER} --version
      OUTPUT_VARIABLE c_compiler_version
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
  STRING(REGEX MATCH "[^\n]*" c_compiler_version_short ${c_compiler_version})
  message(STATUS "C compiler: ${c_compiler_version_short}")

  # print full c++ compiler version
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} --version
      OUTPUT_VARIABLE cxx_compiler_version
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
  STRING(REGEX MATCH "[^\n]*" cxx_compiler_version_short ${cxx_compiler_version})
  message(STATUS "C++ compiler: ${cxx_compiler_version_short}")
endfunction()

# ============================================================================#
