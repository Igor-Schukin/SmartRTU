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
include src/lib/pictures/CMakeFiles/BoardPic.dir/depend.make

# Include the progress variables for this target.
include src/lib/pictures/CMakeFiles/BoardPic.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib/pictures/CMakeFiles/BoardPic.dir/flags.make

src/lib/pictures/CMakeFiles/BoardPic.dir/Picture.cpp.o: src/lib/pictures/CMakeFiles/BoardPic.dir/flags.make
src/lib/pictures/CMakeFiles/BoardPic.dir/Picture.cpp.o: ../src/lib/pictures/Picture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PP/SmartRTU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib/pictures/CMakeFiles/BoardPic.dir/Picture.cpp.o"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures && /usr/bin/arm-linux-gnueabihf-g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BoardPic.dir/Picture.cpp.o -c /home/pi/Desktop/PP/SmartRTU/src/lib/pictures/Picture.cpp

src/lib/pictures/CMakeFiles/BoardPic.dir/Picture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BoardPic.dir/Picture.cpp.i"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures && /usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PP/SmartRTU/src/lib/pictures/Picture.cpp > CMakeFiles/BoardPic.dir/Picture.cpp.i

src/lib/pictures/CMakeFiles/BoardPic.dir/Picture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BoardPic.dir/Picture.cpp.s"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures && /usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PP/SmartRTU/src/lib/pictures/Picture.cpp -o CMakeFiles/BoardPic.dir/Picture.cpp.s

# Object files for target BoardPic
BoardPic_OBJECTS = \
"CMakeFiles/BoardPic.dir/Picture.cpp.o"

# External object files for target BoardPic
BoardPic_EXTERNAL_OBJECTS =

src/lib/pictures/libBoardPic.a: src/lib/pictures/CMakeFiles/BoardPic.dir/Picture.cpp.o
src/lib/pictures/libBoardPic.a: src/lib/pictures/CMakeFiles/BoardPic.dir/build.make
src/lib/pictures/libBoardPic.a: src/lib/pictures/CMakeFiles/BoardPic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/PP/SmartRTU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libBoardPic.a"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures && $(CMAKE_COMMAND) -P CMakeFiles/BoardPic.dir/cmake_clean_target.cmake
	cd /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BoardPic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib/pictures/CMakeFiles/BoardPic.dir/build: src/lib/pictures/libBoardPic.a

.PHONY : src/lib/pictures/CMakeFiles/BoardPic.dir/build

src/lib/pictures/CMakeFiles/BoardPic.dir/clean:
	cd /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures && $(CMAKE_COMMAND) -P CMakeFiles/BoardPic.dir/cmake_clean.cmake
.PHONY : src/lib/pictures/CMakeFiles/BoardPic.dir/clean

src/lib/pictures/CMakeFiles/BoardPic.dir/depend:
	cd /home/pi/Desktop/PP/SmartRTU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/PP/SmartRTU /home/pi/Desktop/PP/SmartRTU/src/lib/pictures /home/pi/Desktop/PP/SmartRTU/build /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures /home/pi/Desktop/PP/SmartRTU/build/src/lib/pictures/CMakeFiles/BoardPic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib/pictures/CMakeFiles/BoardPic.dir/depend

