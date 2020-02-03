cmake_minimum_required(VERSION 3.0.0)

#set(SRC CPicturesStorage.cpp 
#CFontStorage.cpp 
#timetable.cpp 
#desktop.cpp 
#Engine.cpp
 #   )
#set(INC "*.h")
#add_library(Infoboard ${SRC} )

target_include_directories(Infoboard  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/text 
                                          ${CMAKE_CURRENT_SOURCE_DIR}
                                          /opt/vc/include/VG
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
                                          )