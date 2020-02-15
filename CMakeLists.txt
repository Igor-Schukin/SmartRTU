cmake_minimum_required(VERSION 3.0.0)
project(Smart_RTU VERSION 0.1.0)

#set c++ 11 standart
set (CMAKE_CXX_STANDARD 11)
#will work with 11 and above c++ standart otherwise sends error into console
set(CMAKE_CXX_STANDARD_REQUIRED True)

#cmake debging stuff (something about testing)
include(CTest)
enable_testing()

#var where EXTERNAL(oPENvg) .o files are stored
set(OBJ /home/pi/openvg/libshapes.o /home/pi/openvg/oglinit.o)

#for debug purpose added CXX flags
set(CMAKE_CXX_FLAGS "-g -Wall")

#expand CXX flags with lib flags
set(CMAKE_CXX_FLAGS "-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lpthread -ljpeg -lshapes -lm -lpng -ljpeg -fpermissive  -lstdc++ -lfreetype -lwiringPi -lbcm_host -lpthread -lcurl")

#ADD SUBDIRS TO PROJECT
add_subdirectory(src/lib)
add_subdirectory(src/widgets)
add_subdirectory(src/engine)

#change EXE OUTPUT DIR 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#create exe
add_executable(infoboard ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )


#link external .o and libs TO EXE
target_link_libraries(infoboard ${OBJ} BoardLib Boardwidgets BoardEngine)

#where compiler to search PATHS
target_include_directories(infoboard PUBLIC /opt/vc/include 
                                            /opt/vc/include/interface/vmcs_host/linux 
                                            /opt/vc/include/interface/vcos/pthreads 
                                            /home/pi/openvg
                                            /res 
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

#cmake stuff                                            
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
