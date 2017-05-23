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
#include "tiny_socket.h"

#ifdef _WIN32

int sock_fd_pollin(struct pollfd *fds, nfds_t nfds, int timeout){


  if (nfds > FD_SETSIZE) {
    struct fd_set reader_fd_set;
    reader_fd_set.fd_count = nfds;
    memcpy(&reader_fd_set.fd_array[0], fds->fd, sizeof(SOCKET)*nfds);
    
    // Linux timeout is in ms, select timeout is in timeval struct
    struct timeval timeout_struct;
    timeout_struct.tv_sec = timeout / 1000;
    timeout_struct.tv_sec = (timeout % 1000) * 1000;
    int num_events;
    num_events = select(nfds, &reader_fd_set, 0,0, &timeout_struct);


  } else {
    // TODO
    return -1;
  }
}
#else
#include <poll.h>
int sock_fd_pollin(struct pollfd *fds, nfds_t nfds, int timeout){
  return poll(fds, nfds, timeout);
}

#endif


