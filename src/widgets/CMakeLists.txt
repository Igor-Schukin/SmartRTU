cmake_minimum_required(VERSION 3.0.0)

set(SRC IWidget.cpp
    WgAds.cpp
    WgHtmlAds.cpp
    WgBackground.cpp
    WgCalendar.cpp 
    WgClock.cpp 
    WgForecast.cpp 
    WgSockets.cpp 
    WgTimetable.cpp 
    WgWatchdog.cpp
    )
#set(INC "*.h")
add_library(Boardwidgets ${SRC} )

target_include_directories(Boardwidgets  PUBLIC ${CMAKE_CURRENT_LIST_DIR}
                                        ../engine
                                        ../lib/fonts
                                            ../lib/json
                                            ../lib/pictures
                                            ../lib
                                            ../../src
                                          /opt/vc/include/VG
                                          /opt/vc/include 
                                        /opt/vc/include/VG
                                        /opt/vc/include/interface/vmcs_host/linux 
                                        /opt/vc/include/interface/vcos/pthreads 
                                        /home/pi/openvg 
                                        /usr/local/include/freetype2 
                                        /usr/include/freetype2
                                        /usr/local/include 
                                        /usr/include
                                        /opt/vc/lib
                                          )