/******************************************************************************
   Copyright (C) 2017 Edward Scott. All rights reserved.
   Authors: Edward Scott <eddy.scott88@gmail.com>

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.
 3. Neither the name Tiny RTPS nor the names of its contributors may be
    used to endorse or promote products derived from this software
    without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

******************************************************************************/
#include <gtest/gtest.h>
#include <stdlib.h> // exit
#include <string.h> // Memset
#include <stdio.h>  // printf
#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket()
#include <errno.h>  //errno
#include <arpa/inet.h> //inet_ntoa
#include <poll.h> // poll()

#define BUF_LEN 256

TEST(EchoTest, ReadWriteInSecond){
  int reader_fd;
  int writer_fd;
  int rx_len = 0;
  struct sockaddr_in si_reader;
  struct sockaddr_in si_writer;

  char buf[BUF_LEN];
 
  int message_len = 6; 
  char message[6] = "Hello"; 

  reader_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(reader_fd == -1){
    FAIL() << "Reader failed to initialize";
  }
  
  writer_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(writer_fd == -1){
    FAIL() << "Writer failed to initialize";
  }

  memset(&si_reader, '0', sizeof(si_reader));
  memset(&si_writer, '0', sizeof(si_writer));
  
  si_reader.sin_family = AF_INET;
  si_reader.sin_addr.s_addr = INADDR_ANY;
  si_reader.sin_port = 2000;
  
  if(bind(reader_fd, (struct sockaddr *)&si_reader, sizeof(si_reader))){
    FAIL() << "Failed to bind reader to socket"; 
  }
  
  si_writer.sin_family = AF_INET;
  si_writer.sin_addr.s_addr = INADDR_ANY;
  si_writer.sin_port = 3000;
  
  if(bind(writer_fd, (struct sockaddr *)&si_writer, sizeof(si_writer))){
    FAIL() << "Failed to bind writer to socket"; 
  }


  struct pollfd poll_fd[1];
  memset(&poll_fd, '0', sizeof(poll_fd)); 
  poll_fd[0].fd = reader_fd;
  poll_fd[0].events = POLLIN;
  int rv; 


  socklen_t reader_len = sizeof(si_reader);
  
  // Write the message and attempt it read it on the other socket
  int os_ret;
  os_ret = sendto(writer_fd, message, message_len, 0, 
                  (struct sockaddr*) &si_reader, reader_len); 
  if( os_ret == -1){
    FAIL() << "Failed sendto call";
  }
  
  // Wait for 1 second on the reader waiting for the message
  rv = poll(&poll_fd[0], 1, 1000); 
  if(rv == -1){
    FAIL() << "Polling failed!";
  }else if(rv == 0){
    FAIL() << "Failed to recieve a message within 1second";
  }else{
    // check for events on s1:
      if (poll_fd[0].revents & POLLIN) {
        if ((rx_len = recvfrom(reader_fd, buf, BUF_LEN, 
                0, (struct sockaddr *) &si_writer, &reader_len)) == -1)
        {
          FAIL() << "Failed recvfrom call";
        }
        ASSERT_STREQ(&message[0], &buf[0]);  
      }
  } // Successful poll

}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
