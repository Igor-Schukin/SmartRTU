cmake_minimum_required(VERSION 3.0.0)


set(SRC timetable.cpp 
        desktop.cpp 
        Engine.cpp 
        Timer.cpp 
        board.cpp
        )

add_library(BoardEngine ${SRC})

target_include_directories(BoardEngine PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}  
                                            /home/pi/openvg
                                            /opt/vc/include
                                            /opt/vc/include/VG
                                            ../widgets
                                            ../lib/fonts
                                            ../lib/json
                                            ../lib/pictures
                                            ../../src 
					    ../storage  
                                            ../configurator
                                            )

#linked to BoardEngine the Boardwidgets because uses objects from widgets??
#otherwise its not working in last linking stage 
target_link_libraries(BoardEngine  BoardWidgets  )
