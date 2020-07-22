cmake_minimum_required(VERSION 3.0.0)


set(SRC IWidget.cpp
    WgHtmlAds.cpp
    WgBackground.cpp
    WgCalendar.cpp 
    WgClock.cpp 
    WgForecast.cpp 
    WgSockets.cpp 
    WgTimetable.cpp 
    WgWatchdog.cpp
    #CFantik.cpp
    )

add_library(BoardWidgets ${SRC})

target_include_directories(BoardWidgets  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
					                            ../engine					
					                            ../storage
					                            ../lib/fonts
                                                ../../src
                                                ../lib/pictures
                                                ../lib/json
                                                ../configurator
					                            /opt/vc/include
					                            /usr/include/freetype2 
                                          )
