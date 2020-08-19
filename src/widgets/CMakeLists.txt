cmake_minimum_required(VERSION 3.0.0)



##add libs
add_subdirectory(WgHtmlAds)

set(SRC IWidget.cpp
    WgBackground.cpp
    WgCalendar.cpp 
    WgClock.cpp 
    WgForecast.cpp 
    WgSockets.cpp 
    WgTimetable.cpp 
    WgWatchdog.cpp
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
#linking WgHtmlAds.lib + BoardWidgets.lib = Public BoardWidgets.lib
target_link_libraries(BoardWidgets PUBLIC WgHtmlAds)