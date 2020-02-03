cmake_minimum_required(VERSION 3.0.0)

set(SRC ftf.cpp
        TFont.cpp
        )

        add_library(TFont ${SRC} )

        target_include_directories(TFont  PUBLIC /${CMAKE_CURRENT_LIST_DIR}/TFont 
                                                ${CMAKE_CURRENT_SOURCE_DIR}
                                                /opt/vc/include 
                                                /opt/vc/include/VG
                                                /opt/vc/include/interface/vmcs_host/linux 
                                                /opt/vc/include/interface/vcos/pthreads 
                                                /home/pi/openvg
                                                /widgets 
                                                /resources 
                                                /lib 
                                                /usr/local/include/freetype2 
                                                /usr/include/freetype2
                                                /usr/local/include 
                                                /usr/include
                                                /opt/vc/lib
                                                /${CMAKE_BINARY_DIR} 
                                                /${CMAKE_CURRENT_SOURCE_DIR} 
                                                /${CMAKE_CURRENT_BINARY_DIR}
                                                )