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
CMAKE_SOURCE_DIR = "/home/pi/projects/C'monBoard"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/pi/projects/C'monBoard/build"

# Include any dependencies generated for this target.
include src/lib/json/CMakeFiles/json.dir/depend.make

# Include the progress variables for this target.
include src/lib/json/CMakeFiles/json.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib/json/CMakeFiles/json.dir/flags.make

src/lib/json/CMakeFiles/json.dir/json.cpp.o: src/lib/json/CMakeFiles/json.dir/flags.make
src/lib/json/CMakeFiles/json.dir/json.cpp.o: ../src/lib/json/json.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib/json/CMakeFiles/json.dir/json.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/lib/json" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/json.dir/json.cpp.o -c "/home/pi/projects/C'monBoard/src/lib/json/json.cpp"

src/lib/json/CMakeFiles/json.dir/json.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json.dir/json.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/lib/json" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/lib/json/json.cpp" > CMakeFiles/json.dir/json.cpp.i

src/lib/json/CMakeFiles/json.dir/json.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json.dir/json.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/lib/json" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/lib/json/json.cpp" -o CMakeFiles/json.dir/json.cpp.s

# Object files for target json
json_OBJECTS = \
"CMakeFiles/json.dir/json.cpp.o"

# External object files for target json
json_EXTERNAL_OBJECTS =

src/lib/json/libjson.a: src/lib/json/CMakeFiles/json.dir/json.cpp.o
src/lib/json/libjson.a: src/lib/json/CMakeFiles/json.dir/build.make
src/lib/json/libjson.a: src/lib/json/CMakeFiles/json.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libjson.a"
	cd "/home/pi/projects/C'monBoard/build/src/lib/json" && $(CMAKE_COMMAND) -P CMakeFiles/json.dir/cmake_clean_target.cmake
	cd "/home/pi/projects/C'monBoard/build/src/lib/json" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/json.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib/json/CMakeFiles/json.dir/build: src/lib/json/libjson.a

.PHONY : src/lib/json/CMakeFiles/json.dir/build

src/lib/json/CMakeFiles/json.dir/clean:
	cd "/home/pi/projects/C'monBoard/build/src/lib/json" && $(CMAKE_COMMAND) -P CMakeFiles/json.dir/cmake_clean.cmake
.PHONY : src/lib/json/CMakeFiles/json.dir/clean

src/lib/json/CMakeFiles/json.dir/depend:
	cd "/home/pi/projects/C'monBoard/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/pi/projects/C'monBoard" "/home/pi/projects/C'monBoard/src/lib/json" "/home/pi/projects/C'monBoard/build" "/home/pi/projects/C'monBoard/build/src/lib/json" "/home/pi/projects/C'monBoard/build/src/lib/json/CMakeFiles/json.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/lib/json/CMakeFiles/json.dir/depend

