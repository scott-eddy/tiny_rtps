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
/**
 * This file is a stand alone socket echo example used to teach me how 
 * the WIN32 socket api differs from the POSIX API.  That way I can better
 * abstract the two behind tiny_socket
 */

#include <stdio.h>  // printf
#include <tiny_socket.h>
#define BUF_LEN 256

int main() {
  /**
   * All processes (applications or DLLs) that call Winsock functions must
   * initialize the use of the Windows Sockets DLL before making other
   * Winsock functions calls.
   */
  WSADATA wsa_data;

  //  the macro MAKEWORD requests version 2.2 of windsock on the system
  int dll_ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);
  if (dll_ret != 0) {
    printf("WSAStartup failed: %d\n", dll_ret);
    return 1;
  }

  // sockaddr_in is same as POSIX
  struct sockaddr_in si_reader = { 0 };
  struct sockaddr_in si_writer = { 0 };

  char buf[BUF_LEN];

  int message_len = 6;
  char message[6] = "Hello!";

  // TODO Why would you use 0 over IPPROTO_UDP (both are suppoted)
  // Also SOCK_RDM looks like perfect discovery layer for rtps
  // Zero for protocol allows for socket type to choose underlying
  // protocol.  Other option would be specify IPPROTO_UDP
  SOCKET reader_fd = socket(AF_INET, SOCK_DGRAM, 0);
  SOCKET writer_fd = socket(AF_INET, SOCK_DGRAM, 0);

  // sockaddr is a "base class" of sockaddr_in.  It is necessary to get 
  // the reader sockaddr from the SOCKET file descriptor because we will 
  // bind it to INADDR_ANY

  si_reader.sin_family = AF_INET;
  si_reader.sin_addr.s_addr = INADDR_ANY;
  si_reader.sin_port = htons(2000);
  
  if (bind(reader_fd, (struct sockaddr *)&si_reader, sizeof(si_reader))) {
    printf("Binding reader socket failed");
    return 1;
  }

  si_writer.sin_family = AF_INET;
  si_writer.sin_addr.s_addr = INADDR_ANY;
  si_writer.sin_port = htons(3000);
 
  if (bind(writer_fd, (struct sockaddr *)&si_writer, sizeof(si_writer))) {
    printf("Binding writer socket failed, error is %d", errno);
    return 1;
  }

  struct pollfd poll_fd[1] = { 0 };
  poll_fd[0].fd = reader_fd;
  poll_fd[0].events = POLLIN;
  int rv;

  struct sockaddr_in si_writer_target = { 0 };
  si_writer_target.sin_family = AF_INET;
  si_writer_target.sin_addr.s_addr = inet_addr("127.0.0.1");
  si_writer_target.sin_port = htons(2000);
  socklen_t reader_len = sizeof(si_writer_target);

  // Write the message and attempt it read it on the other socket
  int os_ret;
  os_ret = sendto(writer_fd, &message[0], message_len, 0,
    (struct sockaddr *) &si_writer_target, reader_len);
  if (os_ret == -1) {
    printf("Failed sendto call, error is %d\n", errno);
    return 1;
  }

  // Wait for 1 second on the reader waiting for the message
  rv = WSAPoll(&poll_fd[0], 1, 1000);
  if (rv == -1) {
    printf("Polling failed!");
    return 1;
  }
  else if (rv == 0) {
    printf("Failed to recieve a message within 1second");
    return 1;
  }
  else {
    // check for events on s1:
    if (poll_fd[0].revents & POLLIN) {
      int rx_len = 0;
      if ((rx_len = recvfrom(reader_fd, buf, BUF_LEN,
        0, (struct sockaddr *) &si_writer, &reader_len)) == -1)
      {
        printf("Failed recvfrom call");
        return 1;
      }
      printf("Recieved Message %s", message);
    }
  } // Successful poll
}