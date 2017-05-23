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
#include <tiny_socket.h>

#define BUF_LEN 256

TEST(EchoTest, ReadWriteInSecond){
  // The SOCKET data type is win32 specific, but it acts very similarly
  // to a POSIX file descriptor
  SOCKET reader_fd;
  SOCKET writer_fd;

  // Zero initialize socket address input structures.  Note we have
  // 3 inputs here:
  // 1. si_reader: the socket address that will be bound to the reader_fd
  // 2. si_writer: the socket address that will be bound to the writer_fd
  // 3. si_writer_target: the address that will be used in the sendto()
  //                      function.  This is necessary because winsock
  //                      appears unable to sendto INADDR_ANY.  Therefore we
  //                      must callout the target address as loopback
  struct sockaddr_in si_reader = {0};
  struct sockaddr_in si_writer= {0};
  struct sockaddr_in si_writer_targ = {0};
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

  // The socket address that the writer will target.  This is the same port
  // number as the reader but a specific address
  si_writer_targ.sin_family = AF_INET;
  si_writer_targ.sin_addr.s_addr = inet_addr("127.0.0.1");
  si_writer_targ.sin_port = 2000;

  socklen_t writer_targ_len = sizeof(si_writer_targ);
  
  // Write the message and attempt it read it on the other socket
  int os_ret;
  os_ret = sendto(writer_fd, message, message_len, 0, 
                  (struct sockaddr*) &si_reader, writer_targ_len); 
  if( os_ret == -1){
    FAIL() << "Failed sendto call";
  }
  
  // Wait for 1 second on the reader waiting for the message
  rv = socket_fd_pollin(&poll_fd[0], 1, 1000); 
  if(rv == -1){
    FAIL() << "Polling failed!";
  }else if(rv == 0){
    FAIL() << "Failed to recieve a message within 1second";
  }else{
    // check for events on s1:
      if (poll_fd[0].revents & POLLIN) {
        int rx_len;
        if ((rx_len = recvfrom(reader_fd, buf, BUF_LEN, 
                0, (struct sockaddr *) &si_writer, &writer_targ_len)) == -1)
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
