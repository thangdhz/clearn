cmake_minimum_required(VERSION 2.8)
project(clearn C )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lrt -Wall -pthread -lm -Wparentheses -Wno-array-bounds -std=gnu99 -D_DEFAULT_SOURCE")

add_executable(test_queue test_queue_msg.c queuemsg.c)
add_executable(test_udp udp_socket.c)