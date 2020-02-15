cmake_minimum_required(VERSION 3.0.0)

set(SRC json.cpp
        )

add_library(json ${SRC} )

target_include_directories(json  PUBLIC /${CMAKE_CURRENT_LIST_DIR}/TFont 
                                                ${CMAKE_CURRENT_SOURCE_DIR}
                                                )