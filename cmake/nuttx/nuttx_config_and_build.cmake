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

# --------------------------- fetch nuttx -----------------------------------#
function(fetch_nuttx)
  # Note: ExternalProject is used here basically just for downloading the 
  # NuttX_Glob.  Nuttx requires so much additional configuration that 
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
    BUILD_COMMAND "" 
    INSTALL_COMMAND ""
    )
endfunction()
# ----------------------- copy nuttx configuration ---------------------------#
function(copy_nuttx_config)
  ExternalProject_Add_Step(
    NuttX_Glob copy_configuraiton
    DEPENDEES update
    # Note: by wrapping these add_steps in a function we can't specify Dependers
    # as they may not be a valid target yet.   
    COMMAND cp -r ${CMAKE_SOURCE_DIR}/tiny_nuttx_configs/stm32f4discovery/ 
    ${CMAKE_SOURCE_DIR}/NuttX_Glob/nuttx/configs/stm32f4discovery
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endfunction()
# ----------------------- copy nuttx configuration ---------------------------#
function(run_nuttx_configure_script)
  ExternalProject_Add_Step(
    NuttX_Glob configure_board
    DEPENDEES copy_configuraiton
    # Note: by wrapping these add_steps in a function we can't specify Dependers
    # as they may not be a valid target yet.   
    COMMAND bash configure.sh stm32f4discovery/usbnsh 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/NuttX_Glob/nuttx/tools
    )
endfunction()
#-----------------------------------------------------------------------------#
# Change toolchain to compile for ARM
set_toolchain_arm_none_eabi()
fetch_nuttx()
copy_nuttx_config()
run_nuttx_configure_script()




