
cmake_minimum_required(VERSION 3.0.0)
project(Smart_RTU VERSION 0.1.0)

#set c++ 11 standart
set (CMAKE_CXX_STANDARD 11)
#will work with 11 and above c++ standart otherwise sends error into console
set(CMAKE_CXX_STANDARD_REQUIRED True)

#uncoment this to get reliese build by defoult it is in debug mode
#set(CMAKE_BUILD_TYPE Release)

#cmake debging stuff (something about testing)
include(CTest)
enable_testing()

#var where EXTERNAL(oPENvg) .o files are stored
set(OBJ /home/pi/openvg/libshapes.o /home/pi/openvg/oglinit.o)

#for debug purpose added CXX flags
set(CMAKE_CXX_FLAGS "-g -Wall -Werxtra")

#expand CXX flags with lib flags
set(CMAKE_CXX_FLAGS "-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lpthread -ljpeg -lshapes -lm -lpng -ljpeg -fpermissive  -lstdc++ -lfreetype -lwiringPi -lbcm_host -lpthread -lcurl")

#ADD SUBDIRS TO PROJECT 
add_subdirectory(src/configurator)
add_subdirectory(src/lib)
add_subdirectory(src/widgets)
add_subdirectory(src/storage)
add_subdirectory(src/engine)

#change EXE OUTPUT DIR 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#create exe
add_executable(infoboard ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )


#link external .o and libs TO EXE
#maybe '_' can rise an error need to check
target_link_libraries(infoboard ${OBJ}  BoardLib 
					BoardStorage 
					BoardWidgets 
					BoardEngine
					BoardConfig
)

#where compiler to search PATHS
target_include_directories(infoboard PUBLIC  /src/engine
	 				     /src/storage
						 /src
						 /src/configurator
                                            )

#cmake stuff                                            
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
