cmake_minimum_required(VERSION 3.0.0)

#source list
set(SRC Picture.cpp
        )
#for BoardPic need TFont.cpp 
#add lib to 
#add_subdirectory(fonts)
add_library(BoardPic ${SRC} )

#target_link_libraries(BoardPic PUBLIC TFont)

target_include_directories(BoardPic  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                            /../fonts
                                            /opt/vc/include 
                                            /opt/vc/include/interface/vmcs_host/linux 
                                            /opt/vc/include/interface/vcos/pthreads 
                                            /home/pi/openvg
                                            /opt/vc/include/VG
                                                )