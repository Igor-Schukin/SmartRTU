# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Desktop/PP/SmartRTU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/PP/SmartRTU/build

# Include any dependencies generated for this target.
include CMakeFiles/infoboard.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/infoboard.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/infoboard.dir/flags.make

CMakeFiles/infoboard.dir/src/main.cpp.o: CMakeFiles/infoboard.dir/flags.make
CMakeFiles/infoboard.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PP/SmartRTU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/infoboard.dir/src/main.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/infoboard.dir/src/main.cpp.o -c /home/pi/Desktop/PP/SmartRTU/src/main.cpp

CMakeFiles/infoboard.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/infoboard.dir/src/main.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PP/SmartRTU/src/main.cpp > CMakeFiles/infoboard.dir/src/main.cpp.i

CMakeFiles/infoboard.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/infoboard.dir/src/main.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PP/SmartRTU/src/main.cpp -o CMakeFiles/infoboard.dir/src/main.cpp.s

# Object files for target infoboard
infoboard_OBJECTS = \
"CMakeFiles/infoboard.dir/src/main.cpp.o"

# External object files for target infoboard
infoboard_EXTERNAL_OBJECTS =

../infoboard: CMakeFiles/infoboard.dir/src/main.cpp.o
../infoboard: CMakeFiles/infoboard.dir/build.make
../infoboard: /home/pi/openvg/libshapes.o
../infoboard: /home/pi/openvg/oglinit.o
../infoboard: src/lib/libBoardLib.a
../infoboard: src/storage/libBoardStorage.a
../infoboard: src/widgets/libBoardWidgets.a
../infoboard: src/engine/libBoardEngine.a
../infoboard: src/configurator/libBoardConfig.a
../infoboard: src/lib/pictures/libBoardPic.a
../infoboard: src/lib/json/libjson.a
../infoboard: src/lib/fonts/libTFont.a
../infoboard: src/widgets/libBoardWidgets.a
../infoboard: CMakeFiles/infoboard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/PP/SmartRTU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../infoboard"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/infoboard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/infoboard.dir/build: ../infoboard

.PHONY : CMakeFiles/infoboard.dir/build

CMakeFiles/infoboard.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/infoboard.dir/cmake_clean.cmake
.PHONY : CMakeFiles/infoboard.dir/clean

CMakeFiles/infoboard.dir/depend:
	cd /home/pi/Desktop/PP/SmartRTU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/PP/SmartRTU /home/pi/Desktop/PP/SmartRTU /home/pi/Desktop/PP/SmartRTU/build /home/pi/Desktop/PP/SmartRTU/build /home/pi/Desktop/PP/SmartRTU/build/CMakeFiles/infoboard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/infoboard.dir/depend

