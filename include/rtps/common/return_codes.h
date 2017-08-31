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
#ifndef TINY_RTPS_RETURN_CODES_H
#define TINY_RTPS_RETURN_CODES_H

#ifdef __cplusplus
extern "C"{
#endif

typedef enum RTPS_ReturnCode_t{
  /**
   * @brief The function succeeded with no errors
   */
  RTPS_RETCODE_OK,

  /**
   * @brief General, unspecified error occured
   */
  RTPS_RETCODE_ERROR,

  /**
   * @brief A value of the parameter that is passed in has an illegal value.  This might include a NULL pointer being
   *        passed in or a value that is out of range
   */
  RTPS_RETCODE_BAD_PARAMETER,

  /**
   * @brief tiny_rtps ran out of the resource(s) needed to complete the operation
   */
  RTPS_RETCODE_OUT_OF_RESOURCES

} RTPS_ReturnCode_t;



#ifdef __cplusplus
}
#endif
#endif //TINY_RTPS_RETURN_CODES_H
