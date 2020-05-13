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
include src/storage/CMakeFiles/BoardStorage.dir/depend.make

# Include the progress variables for this target.
include src/storage/CMakeFiles/BoardStorage.dir/progress.make

# Include the compile flags for this target's objects.
include src/storage/CMakeFiles/BoardStorage.dir/flags.make

src/storage/CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.o: src/storage/CMakeFiles/BoardStorage.dir/flags.make
src/storage/CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.o: ../src/storage/CPicturesStorage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PP/SmartRTU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/storage/CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.o"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && /usr/bin/arm-linux-gnueabihf-g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.o -c /home/pi/Desktop/PP/SmartRTU/src/storage/CPicturesStorage.cpp

src/storage/CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.i"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && /usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PP/SmartRTU/src/storage/CPicturesStorage.cpp > CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.i

src/storage/CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.s"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && /usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PP/SmartRTU/src/storage/CPicturesStorage.cpp -o CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.s

src/storage/CMakeFiles/BoardStorage.dir/CFontStorage.cpp.o: src/storage/CMakeFiles/BoardStorage.dir/flags.make
src/storage/CMakeFiles/BoardStorage.dir/CFontStorage.cpp.o: ../src/storage/CFontStorage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PP/SmartRTU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/storage/CMakeFiles/BoardStorage.dir/CFontStorage.cpp.o"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && /usr/bin/arm-linux-gnueabihf-g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BoardStorage.dir/CFontStorage.cpp.o -c /home/pi/Desktop/PP/SmartRTU/src/storage/CFontStorage.cpp

src/storage/CMakeFiles/BoardStorage.dir/CFontStorage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BoardStorage.dir/CFontStorage.cpp.i"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && /usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PP/SmartRTU/src/storage/CFontStorage.cpp > CMakeFiles/BoardStorage.dir/CFontStorage.cpp.i

src/storage/CMakeFiles/BoardStorage.dir/CFontStorage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BoardStorage.dir/CFontStorage.cpp.s"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && /usr/bin/arm-linux-gnueabihf-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PP/SmartRTU/src/storage/CFontStorage.cpp -o CMakeFiles/BoardStorage.dir/CFontStorage.cpp.s

# Object files for target BoardStorage
BoardStorage_OBJECTS = \
"CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.o" \
"CMakeFiles/BoardStorage.dir/CFontStorage.cpp.o"

# External object files for target BoardStorage
BoardStorage_EXTERNAL_OBJECTS =

src/storage/libBoardStorage.a: src/storage/CMakeFiles/BoardStorage.dir/CPicturesStorage.cpp.o
src/storage/libBoardStorage.a: src/storage/CMakeFiles/BoardStorage.dir/CFontStorage.cpp.o
src/storage/libBoardStorage.a: src/storage/CMakeFiles/BoardStorage.dir/build.make
src/storage/libBoardStorage.a: src/storage/CMakeFiles/BoardStorage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/PP/SmartRTU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libBoardStorage.a"
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && $(CMAKE_COMMAND) -P CMakeFiles/BoardStorage.dir/cmake_clean_target.cmake
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BoardStorage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/storage/CMakeFiles/BoardStorage.dir/build: src/storage/libBoardStorage.a

.PHONY : src/storage/CMakeFiles/BoardStorage.dir/build

src/storage/CMakeFiles/BoardStorage.dir/clean:
	cd /home/pi/Desktop/PP/SmartRTU/build/src/storage && $(CMAKE_COMMAND) -P CMakeFiles/BoardStorage.dir/cmake_clean.cmake
.PHONY : src/storage/CMakeFiles/BoardStorage.dir/clean

src/storage/CMakeFiles/BoardStorage.dir/depend:
	cd /home/pi/Desktop/PP/SmartRTU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/PP/SmartRTU /home/pi/Desktop/PP/SmartRTU/src/storage /home/pi/Desktop/PP/SmartRTU/build /home/pi/Desktop/PP/SmartRTU/build/src/storage /home/pi/Desktop/PP/SmartRTU/build/src/storage/CMakeFiles/BoardStorage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/storage/CMakeFiles/BoardStorage.dir/depend

