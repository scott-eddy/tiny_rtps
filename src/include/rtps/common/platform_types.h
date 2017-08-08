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

#ifndef TINY_RTPS_PLATFORM_TYPES_H
#define TINY_RTPS_PLATFORM_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif


#include <stdint.h> //int8_t
#include <stddef.h> //size_t

/**
 * @brief Type used to represent an integer composed of 8 bits
 */
typedef int8_t octet;


#ifdef DYNAMIC_STRING_ALLOCATION
/**
 * @brief A structure used to represent a string literal
 */
typedef struct RtpsString_t {
  //TODO should this be dynamically sized or fixed?
  size_t size;
  char* text;
} RtpsString_t;
#else

/**
 * @brief A structure used to represent a string literal
 */
#define MAX_STRING_TEXT_SIZE 256
typedef struct RtpsString_t {
  size_t size;
  char text[256];
} RtpsString_t;

#endif //DYNAMIC_STRING_ALLOCATION


#ifdef __cplusplus
}
#endif
#endif //TINY_RTPS_PLATFORM_TYPES_H
