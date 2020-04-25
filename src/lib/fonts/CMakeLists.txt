cmake_minimum_required(VERSION 3.0.0)

set(SRC ftf.cpp
        TFont.cpp
        )

add_library(TFont ${SRC} )

target_include_directories(TFont  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
                                                /opt/vc/include 
						/home/pi/openvg
                                                /usr/include/freetype2
                                                /usr/local/include 
                                                )
