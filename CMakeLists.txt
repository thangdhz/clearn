cmake_minimum_required(VERSION 2.8)
project(clearn C )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lrt -Wall -lpthread -lm -Wparentheses -Wno-array-bounds -std=gnu99 -D_DEFAULT_SOURCE")
set(CMAKE_C_COMPILER /opt/toolchains/gcc-linaro-5.5.0-2017.10-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)

add_executable(test_queue test_queue_msg.c queuemsg.c)