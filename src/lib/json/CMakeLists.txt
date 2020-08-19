cmake_minimum_required(VERSION 3.0.0)
set(SRC json.cpp
        )

#turns off notes of GCC compilator #but it do not work??
# https://unix.stackexchange.com/questions/547567/want-to-turn-off-note-level-messages-in-gcc
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcompare-debug-second")

add_library(json   ${SRC} )

target_include_directories(json  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR} 
                                                
                                                )
