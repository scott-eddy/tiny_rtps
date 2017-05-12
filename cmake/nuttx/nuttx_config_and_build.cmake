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


###
# nuttx_config_and_build.cmake
# ---------------------------
#
###
#-----------------------     Includes  ---------------------------------------#
# Enable ExternalProject CMake module
include(ExternalProject)
# Allows setting of the toolchain
include(${CMAKE_CURRENT_LIST_DIR}/set_toolchain_arm_none_eabi.cmake)


#-----------------------------------------------------------------------------#
# Change toolchain to compile for ARM
set_toolchain_arm_none_eabi()

#######
# Add the external project, this specifies the download and build steps only
# All other nuttx configuration, cleaning, etc is done below
######
ExternalProject_Add(NuttX_Glob
  GIT_REPOSITORY https://github.com/scott-eddy/NuttX_Glob
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/NuttX_Glob
  SOURCE_SUBDIR nuttx
  # We configure the board with ./configure.sh in a seperate step 
  # since the API for ExternalProject_Add_step makes speciffying the 
  # working directory trivial
  CONFIGURE_COMMAND ""   
  BUILD_IN_SOURCE 1  
  # Change to the nuttx dir and run make 
  BUILD_COMMAND ${CMAKE_COMMAND} -E chdir nuttx make 
  INSTALL_COMMAND ""
  )

ExternalProject_Add_Step(
  NuttX_Glob configure_board
  DEPENDEES copy_configuraiton
  DEPENDERS build
  COMMAND bash configure.sh stm32f4discovery/usbnsh 
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/NuttX_Glob/nuttx/tools
  )

ExternalProject_Add_Step(
  NuttX_Glob copy_configuraiton
  DEPENDEES update
  DEPENDERS configure_board
  COMMAND cp -r ${CMAKE_SOURCE_DIR}/tiny_nuttx_configs/stm32f4discovery/ 
  ${CMAKE_SOURCE_DIR}/NuttX_Glob/nuttx/configs/stm32f4discovery
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )


ADD_CUSTOM_TARGET(distclean
  command git clean -fd ${CMAKE_SOURCE_DIR}/NuttX_Glob/nuttx)
