# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug"

# Include any dependencies generated for this target.
include src/CMakeFiles/Assignment1.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Assignment1.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Assignment1.dir/flags.make

src/CMakeFiles/Assignment1.dir/Main.cpp.o: src/CMakeFiles/Assignment1.dir/flags.make
src/CMakeFiles/Assignment1.dir/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Assignment1.dir/Main.cpp.o"
	cd "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/src" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Assignment1.dir/Main.cpp.o -c "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/src/Main.cpp"

src/CMakeFiles/Assignment1.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment1.dir/Main.cpp.i"
	cd "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/src" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/src/Main.cpp" > CMakeFiles/Assignment1.dir/Main.cpp.i

src/CMakeFiles/Assignment1.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment1.dir/Main.cpp.s"
	cd "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/src" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/src/Main.cpp" -o CMakeFiles/Assignment1.dir/Main.cpp.s

# Object files for target Assignment1
Assignment1_OBJECTS = \
"CMakeFiles/Assignment1.dir/Main.cpp.o"

# External object files for target Assignment1
Assignment1_EXTERNAL_OBJECTS =

src/Assignment1: src/CMakeFiles/Assignment1.dir/Main.cpp.o
src/Assignment1: src/CMakeFiles/Assignment1.dir/build.make
src/Assignment1: src/CMakeFiles/Assignment1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Assignment1"
	cd "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assignment1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Assignment1.dir/build: src/Assignment1

.PHONY : src/CMakeFiles/Assignment1.dir/build

src/CMakeFiles/Assignment1.dir/clean:
	cd "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/src" && $(CMAKE_COMMAND) -P CMakeFiles/Assignment1.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Assignment1.dir/clean

src/CMakeFiles/Assignment1.dir/depend:
	cd "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1" "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/src" "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug" "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/src" "/Users/hayden/Documents/Uni/CS/Year 2 Semester 1/Data Strucures & Algoritms/Assignment/Assignment1/cmake-build-debug/src/CMakeFiles/Assignment1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/Assignment1.dir/depend

