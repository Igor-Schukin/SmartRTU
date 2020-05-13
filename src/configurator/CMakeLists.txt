cmake_minimum_required(VERSION 3.0.0)


set(SRC configurator.cpp 
        )

add_library(BoardConfig ${SRC})

target_include_directories(BoardConfig PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}  

                                            )

