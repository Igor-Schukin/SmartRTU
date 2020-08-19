cmake_minimum_required(VERSION 3.0.0)


set(SRC 
    WgHtmlAds.cpp
    advert_shell.cpp
    )

add_library(WgHtmlAds ${SRC})

target_include_directories(WgHtmlAds  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
../../widgets
../../engine					
../../storage
../../lib/fonts
../../../src
../../lib/pictures
../../lib/json
../../configurator
					                            /opt/vc/include
					                            /usr/include/freetype2 
                                          )
