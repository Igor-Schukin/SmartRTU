cmake_minimum_required(VERSION 3.0.0)


set(SRC CPicturesStorage.cpp 
        CFontStorage.cpp 
        timetable.cpp 
        desktop.cpp 
        Engine.cpp 
        Timer.cpp 
        board.cpp
        )

add_library(BoardEngine ${SRC})

target_include_directories(BoardEngine PUBLIC /opt/vc/include 
                                            /opt/vc/include/interface/vmcs_host/linux 
                                            /opt/vc/include/interface/vcos/pthreads 
                                            /home/pi/openvg
                                            /opt/vc/include/VG
                                            ../widgets 
                                            /resources 
                                            ../lib/fonts
                                            ../lib/json
                                            ../lib/pictures
                                            ../lib
                                            ../../src
                                            /usr/local/include/freetype2 
                                            /usr/include/freetype2
                                            /usr/local/include 
                                            /usr/include
                                            /opt/vc/lib
                                            ${CMAKE_BINARY_DIR}/ 
                                            /${CMAKE_CURRENT_SOURCE_DIR}
                                            ${CMAKE_CURRENT_SOURCE_DIR}/lib
                                            ${CMAKE_CURRENT_SOURCE_DIR}/lib/TFont
                                            ${CMAKE_CURRENT_SOURCE_DIR}/widgets 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/resources 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/resources/shadows
                                            ${CMAKE_CURRENT_SOURCE_DIR}/resources/weather  
                                            /${CMAKE_CURRENT_BINARY_DIR}
                                            ~/projects/SmartRTU/
                                            )

#linked to BoardENgine the Boardwidgets because uses objects from wisgets 
target_link_libraries(BoardEngine  Boardwidgets )