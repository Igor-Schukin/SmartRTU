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
include src/widgets/CMakeFiles/Boardwidgets.dir/depend.make

# Include the progress variables for this target.
include src/widgets/CMakeFiles/Boardwidgets.dir/progress.make

# Include the compile flags for this target's objects.
include src/widgets/CMakeFiles/Boardwidgets.dir/flags.make

src/widgets/CMakeFiles/Boardwidgets.dir/IWidget.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/IWidget.cpp.o: ../src/widgets/IWidget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/IWidget.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/IWidget.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/IWidget.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/IWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/IWidget.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/IWidget.cpp" > CMakeFiles/Boardwidgets.dir/IWidget.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/IWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/IWidget.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/IWidget.cpp" -o CMakeFiles/Boardwidgets.dir/IWidget.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgAds.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgAds.cpp.o: ../src/widgets/WgAds.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgAds.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgAds.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgAds.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgAds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgAds.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgAds.cpp" > CMakeFiles/Boardwidgets.dir/WgAds.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgAds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgAds.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgAds.cpp" -o CMakeFiles/Boardwidgets.dir/WgAds.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgBackground.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgBackground.cpp.o: ../src/widgets/WgBackground.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgBackground.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgBackground.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgBackground.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgBackground.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgBackground.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgBackground.cpp" > CMakeFiles/Boardwidgets.dir/WgBackground.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgBackground.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgBackground.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgBackground.cpp" -o CMakeFiles/Boardwidgets.dir/WgBackground.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.o: ../src/widgets/WgCalendar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgCalendar.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgCalendar.cpp" > CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgCalendar.cpp" -o CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgClock.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgClock.cpp.o: ../src/widgets/WgClock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgClock.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgClock.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgClock.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgClock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgClock.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgClock.cpp" > CMakeFiles/Boardwidgets.dir/WgClock.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgClock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgClock.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgClock.cpp" -o CMakeFiles/Boardwidgets.dir/WgClock.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgForecast.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgForecast.cpp.o: ../src/widgets/WgForecast.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgForecast.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgForecast.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgForecast.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgForecast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgForecast.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgForecast.cpp" > CMakeFiles/Boardwidgets.dir/WgForecast.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgForecast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgForecast.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgForecast.cpp" -o CMakeFiles/Boardwidgets.dir/WgForecast.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgSockets.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgSockets.cpp.o: ../src/widgets/WgSockets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgSockets.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgSockets.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgSockets.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgSockets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgSockets.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgSockets.cpp" > CMakeFiles/Boardwidgets.dir/WgSockets.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgSockets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgSockets.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgSockets.cpp" -o CMakeFiles/Boardwidgets.dir/WgSockets.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.o: ../src/widgets/WgTimetable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgTimetable.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgTimetable.cpp" > CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgTimetable.cpp" -o CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.s

src/widgets/CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.o: src/widgets/CMakeFiles/Boardwidgets.dir/flags.make
src/widgets/CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.o: ../src/widgets/WgWatchdog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/widgets/CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.o"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.o -c "/home/pi/projects/C'monBoard/src/widgets/WgWatchdog.cpp"

src/widgets/CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.i"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/projects/C'monBoard/src/widgets/WgWatchdog.cpp" > CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.i

src/widgets/CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.s"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/projects/C'monBoard/src/widgets/WgWatchdog.cpp" -o CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.s

# Object files for target Boardwidgets
Boardwidgets_OBJECTS = \
"CMakeFiles/Boardwidgets.dir/IWidget.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgAds.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgBackground.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgClock.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgForecast.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgSockets.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.o" \
"CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.o"

# External object files for target Boardwidgets
Boardwidgets_EXTERNAL_OBJECTS =

src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/IWidget.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgAds.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgBackground.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgCalendar.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgClock.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgForecast.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgSockets.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgTimetable.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/WgWatchdog.cpp.o
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/build.make
src/widgets/libBoardwidgets.a: src/widgets/CMakeFiles/Boardwidgets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/pi/projects/C'monBoard/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libBoardwidgets.a"
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && $(CMAKE_COMMAND) -P CMakeFiles/Boardwidgets.dir/cmake_clean_target.cmake
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Boardwidgets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/widgets/CMakeFiles/Boardwidgets.dir/build: src/widgets/libBoardwidgets.a

.PHONY : src/widgets/CMakeFiles/Boardwidgets.dir/build

src/widgets/CMakeFiles/Boardwidgets.dir/clean:
	cd "/home/pi/projects/C'monBoard/build/src/widgets" && $(CMAKE_COMMAND) -P CMakeFiles/Boardwidgets.dir/cmake_clean.cmake
.PHONY : src/widgets/CMakeFiles/Boardwidgets.dir/clean

src/widgets/CMakeFiles/Boardwidgets.dir/depend:
	cd "/home/pi/projects/C'monBoard/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/pi/projects/C'monBoard" "/home/pi/projects/C'monBoard/src/widgets" "/home/pi/projects/C'monBoard/build" "/home/pi/projects/C'monBoard/build/src/widgets" "/home/pi/projects/C'monBoard/build/src/widgets/CMakeFiles/Boardwidgets.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/widgets/CMakeFiles/Boardwidgets.dir/depend

