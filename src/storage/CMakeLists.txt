cmake_minimum_required(VERSION 3.0.0)


set(SRC CPicturesStorage.cpp 
        CFontStorage.cpp 
        )

add_library(BoardStorage ${SRC})

target_include_directories(BoardStorage PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}  
                                            /home/pi/openvg
                                            /opt/vc/include/VG 
					    /opt/vc/include
					   /usr/include/freetype2
                                            ../lib/pictures
                                            ../../src  
					   ../lib/fonts
                                            )

