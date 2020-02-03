cmake_minimum_required(VERSION 3.0.0)

set(SRC json.cpp
    Picture.cpp
    
    )

set(CMAKE_CXX_FLAGS "-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lpthread -ljpeg -lshapes -lm -lpng -ljpeg -fpermissive  -lstdc++ -lfreetype -lwiringPi -lbcm_host -lpthread")


add_subdirectory(TFont)

#create lib
add_library(lib ${SRC} )

target_include_directories(lib  PUBLIC /${CMAKE_CURRENT_LIST_DIR}/TFont 
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
target_link_libraries(lib PUBLIC TFont)