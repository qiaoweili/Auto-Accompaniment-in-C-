# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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

#Suppress display of executed commands.
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
CMAKE_SOURCE_DIR = "/Users/qiaoweiiii/Desktop/music X lab/CLion"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/qiaoweiiii/Desktop/music X lab/CLion/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/acco.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/acco.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/acco.dir/flags.make

CMakeFiles/acco.dir/accompaniment.cpp.o: CMakeFiles/acco.dir/flags.make
CMakeFiles/acco.dir/accompaniment.cpp.o: ../accompaniment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/qiaoweiiii/Desktop/music X lab/CLion/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/acco.dir/accompaniment.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/acco.dir/accompaniment.cpp.o -c "/Users/qiaoweiiii/Desktop/music X lab/CLion/accompaniment.cpp"

CMakeFiles/acco.dir/accompaniment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acco.dir/accompaniment.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/qiaoweiiii/Desktop/music X lab/CLion/accompaniment.cpp" > CMakeFiles/acco.dir/accompaniment.cpp.i

CMakeFiles/acco.dir/accompaniment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acco.dir/accompaniment.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/qiaoweiiii/Desktop/music X lab/CLion/accompaniment.cpp" -o CMakeFiles/acco.dir/accompaniment.cpp.s

# Object files for target acco
acco_OBJECTS = \
"CMakeFiles/acco.dir/accompaniment.cpp.o"

# External object files for target acco
acco_EXTERNAL_OBJECTS =

acco: CMakeFiles/acco.dir/accompaniment.cpp.o
acco: CMakeFiles/acco.dir/build.make
acco: /usr/local/lib/libfftw3.dylib
acco: CMakeFiles/acco.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/qiaoweiiii/Desktop/music X lab/CLion/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable acco"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/acco.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/acco.dir/build: acco

.PHONY : CMakeFiles/acco.dir/build

CMakeFiles/acco.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/acco.dir/cmake_clean.cmake
.PHONY : CMakeFiles/acco.dir/clean

CMakeFiles/acco.dir/depend:
	cd "/Users/qiaoweiiii/Desktop/music X lab/CLion/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/qiaoweiiii/Desktop/music X lab/CLion" "/Users/qiaoweiiii/Desktop/music X lab/CLion" "/Users/qiaoweiiii/Desktop/music X lab/CLion/cmake-build-debug" "/Users/qiaoweiiii/Desktop/music X lab/CLion/cmake-build-debug" "/Users/qiaoweiiii/Desktop/music X lab/CLion/cmake-build-debug/CMakeFiles/acco.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/acco.dir/depend

