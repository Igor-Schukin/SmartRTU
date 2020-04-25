cmake_minimum_required(VERSION 3.0.0)

#source list
set(SRC Picture.cpp
        )
 

#create BoardPic lib)
add_library(BoardPic ${SRC} )

#where compiler search includes
target_include_directories(BoardPic  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR} 
					/home/pi/openvg
					/opt/vc/include
                                                )
