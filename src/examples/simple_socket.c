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
#include <stdlib.h> // exit
#include <string.h> // Memset
#include <stdio.h>  // printf
#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket()
#include <errno.h>  //errno
#include <arpa/inet.h> //inet_ntoa
#include <poll.h> // poll()

#define BUF_LEN 256
void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char **argv){
  int reader_fd;
  int writer_fd;
  int rx_len = 0;
  struct sockaddr_in si_reader;
  struct sockaddr_in si_writer;

  uint8_t buf[BUF_LEN];
 
  int message_len = 6; 
  uint8_t message[6] = "Hello!"; 

  reader_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(reader_fd == -1){
    die("Socket creation failed with error:");
  }
  
  writer_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(writer_fd == -1){
    die("Socket creation failed with error:");
  }

  memset(&si_reader, '0', sizeof(si_reader));
  memset(&si_writer, '0', sizeof(si_writer));
  
  si_reader.sin_family = AF_INET;
  si_reader.sin_addr.s_addr = INADDR_ANY;
  si_reader.sin_port = 2000;
  
  if(bind(reader_fd, (struct sockaddr *)&si_reader, sizeof(si_reader))){
    die("Binding reader socket failed");
  }
  
  si_writer.sin_family = AF_INET;
  si_writer.sin_addr.s_addr = INADDR_ANY;
  si_writer.sin_port = 3000;
  
  if(bind(writer_fd, (struct sockaddr *)&si_writer, sizeof(si_writer))){
    die("Binding reader socket failed");
  }


  struct pollfd poll_fd[2];
  memset(&poll_fd, '0', sizeof(poll_fd)); 
  poll_fd[0].fd = reader_fd;
  poll_fd[0].events = POLLIN;
  poll_fd[1].fd = writer_fd;
  poll_fd[1].events = POLLOUT;
  int rv; 


  socklen_t reader_len = sizeof(si_reader);
  int count = 0;
  while(1){
    rv = poll(&poll_fd[0], 2, 1000);
    if(rv == -1){
      die("Poll Error");
    }else if(rv == 0){
      die("No messages after 1 s");
    }else{
      // check for events on s1:
      if (poll_fd[0].revents & POLLIN) {
        if ((rx_len = recvfrom(reader_fd, buf, BUF_LEN, 0, (struct sockaddr *) &si_writer, &reader_len)) == -1)
        {
          die("recvfrom()");
        }
        
        ++count;
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_reader.sin_addr), ntohs(si_reader.sin_port));
        printf("Data: %s\n" , buf);
      }

      // check for events on s2:
      if (poll_fd[1].revents & POLLOUT) {
        //printf("Sending message\n");
        
        if (sendto(writer_fd, message, message_len, 0, (struct sockaddr*) &si_reader, reader_len) == -1)
        {
          die("sendto()");
        }
      }
    } // Successful poll
    if(count == 5){
      break;
    }
  } // Read & Write looop


}



