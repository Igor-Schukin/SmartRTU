
cmake_minimum_required(VERSION 3.0.0)
project(Smart_RTU VERSION 0.1.0)

#set c++ 11 standart
set (CMAKE_CXX_STANDARD 11)
#will work with 11 and above c++ standart otherwise sends error into console
set(CMAKE_CXX_STANDARD_REQUIRED True)

# uncoment 11 line for reliese build  and comment 12 line  by defoult build is in  debug mode
# if build type was changed using IDE make sure what in main CmakeLists.txt build type is same
# other wise will be broken exe 

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)


#cmake debging stuff (something about testing)
include(CTest)
enable_testing()

#var where EXTERNAL(oPENvg) .o files are stored
set(OBJ /home/pi/openvg/libshapes.o /home/pi/openvg/oglinit.o)

# -g adds debuging info into exe 
# -Wall will show most of the errors/warnings if compiler finds them
# -Wextra ads even more warnings if compiler will found them
# -03 means max level of compiler optimization
# -DNDEBUG  needed stuff but I do not know why(change build type in IDE on Release and check build/compile_comamands.json)

#diferent compiler flags for differnt builds
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
else(CMAKE_BUILD_TYPE MATCHES Debug)
	# if it not in Debug build when adds only -Wall
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -DNDEBUG")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

#expand CXX flags with lib flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lpthread -ljpeg -lshapes -lm -lpng -ljpeg")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/opt/vc/lib -fpermissive  -lstdc++ -lfreetype -lwiringPi -lbcm_host -lpthread -lcurl")


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


#link external .o and own libs TO EXE
target_link_libraries(infoboard ${OBJ} BoardConfig
							BoardLib
							BoardWidgets
							BoardStorage  
							BoardEngine
)

#where compiler to search PATHS
target_include_directories(infoboard PUBLIC /src/engine
	 				     	/src/storage
						 	/src
							 /src/configurator
							 ./src/widgets
							 /home/pi/openvg
                            /opt/vc/include
                            /opt/vc/include/VG
                            /src/widgets
                            /src/lib/fonts
                            /src/lib/json
                            /src/lib/pictures
)

#cmake stuff                                            
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
