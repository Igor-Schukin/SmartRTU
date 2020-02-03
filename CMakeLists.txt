cmake_minimum_required(VERSION 3.0.0)
project(Smart_RTU VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()


set(OBJ /home/pi/openvg/libshapes.o /home/pi/openvg/oglinit.o)

set(CMAKE_CXX_FLAGS "-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lpthread -ljpeg -lshapes -lm -lpng -ljpeg -fpermissive  -lstdc++ -lfreetype -lwiringPi -lbcm_host -lpthread -lcurl")

#add_subdirectory(widgets)
#add_subdirectory(resources)
#add_subdirectory(lib)

#include_directories(widgets 
#resources 
#lib 
#/usr/local/include/freetype2 
#/usr/local/include 
#/usr/include
#/opt/vc/lib)

set(MAIN_SRC CPicturesStorage.cpp CFontStorage.cpp timetable.cpp desktop.cpp Engine.cpp Timer.cpp board.cpp)
set(MAIN_INC CPicturesStorage.h CFontStorage.h timetable.h desktop.h Engine.h Timer.h board.h)


#ADD WIDGETS SUB DIR
add_subdirectory(widgets)
add_subdirectory(lib)
#add_subdirectory(InfoBoard)

#CREATE LAST LIB
add_library( MAINLIB ${MAIN_SRC} ${MAIN_INC})
target_link_libraries(MAINLIB PUBLIC widgets lib TFont)
#include MAINLIB
target_include_directories(MAINLIB PUBLIC /opt/vc/include 
                                            /opt/vc/include/interface/vmcs_host/linux 
                                            /opt/vc/include/interface/vcos/pthreads 
                                            /home/pi/openvg
                                            /opt/vc/include/VG
                                            /widgets 
                                            /resources 
                                            /lib 
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




add_executable(infoboard main.cpp )


#link external .o 
target_link_libraries(infoboard ${OBJ} widgets lib MAINLIB TFont)


target_include_directories(infoboard PUBLIC /opt/vc/include 
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
                                            ~/projects/SmartRTU/
                                            )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#target_link_directories(infoboard ${CMAKE_BINARY_DIR} )

#cmake_minimum_required(VERSION 3.0.0)
#project(Brick_MOvement VERSION 0.1.0)

#include(CTest)
#enable_testing()

#set(OBJ /home/pi/openvg/libshapes.o /home/pi/openvg/oglinit.o)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

#add_executable(Brick_MOvement main.cpp  )

#set(CMAKE_CXX_FLAGS "-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lpthread  -ljpeg")
#add_definitions(-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lpthread  -ljpeg)
#link external .o 
#target_link_libraries(Brick_MOvement ${OBJ} )
#/opt/vc/lib/brcmEGL 
#/opt/vc/lib/brcmGLESv2 
#/opt/vc/lib/bcm_host 
#/opt/vc/lib/pthread  
#/opt/vc/lib/jpeg
#)
#target_include_directories(Brick_MOvement PUBLIC /opt/vc/include 
#/opt/vc/include/interface/vmcs_host/linux 
#/opt/vc/include/interface/vcos/pthreads 
#/home/pi/openvg)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
