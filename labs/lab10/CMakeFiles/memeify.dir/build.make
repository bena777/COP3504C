# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\benad\CLionProjects\lab10

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\benad\CLionProjects\lab10

# Include any dependencies generated for this target.
include CMakeFiles/memeify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/memeify.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/memeify.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/memeify.dir/flags.make

CMakeFiles/memeify.dir/codegen:
.PHONY : CMakeFiles/memeify.dir/codegen

CMakeFiles/memeify.dir/memeify.cpp.obj: CMakeFiles/memeify.dir/flags.make
CMakeFiles/memeify.dir/memeify.cpp.obj: CMakeFiles/memeify.dir/includes_CXX.rsp
CMakeFiles/memeify.dir/memeify.cpp.obj: memeify.cpp
CMakeFiles/memeify.dir/memeify.cpp.obj: CMakeFiles/memeify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\benad\CLionProjects\lab10\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/memeify.dir/memeify.cpp.obj"
	C:\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/memeify.dir/memeify.cpp.obj -MF CMakeFiles\memeify.dir\memeify.cpp.obj.d -o CMakeFiles\memeify.dir\memeify.cpp.obj -c C:\Users\benad\CLionProjects\lab10\memeify.cpp

CMakeFiles/memeify.dir/memeify.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/memeify.dir/memeify.cpp.i"
	C:\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\benad\CLionProjects\lab10\memeify.cpp > CMakeFiles\memeify.dir\memeify.cpp.i

CMakeFiles/memeify.dir/memeify.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/memeify.dir/memeify.cpp.s"
	C:\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\benad\CLionProjects\lab10\memeify.cpp -o CMakeFiles\memeify.dir\memeify.cpp.s

# Object files for target memeify
memeify_OBJECTS = \
"CMakeFiles/memeify.dir/memeify.cpp.obj"

# External object files for target memeify
memeify_EXTERNAL_OBJECTS =

memeify.exe: CMakeFiles/memeify.dir/memeify.cpp.obj
memeify.exe: CMakeFiles/memeify.dir/build.make
memeify.exe: libmemer.a
memeify.exe: C:/Users/benad/Desktop/SFML-2.5.1/lib/libsfml-graphics-d.a
memeify.exe: C:/Users/benad/Desktop/SFML-2.5.1/lib/libsfml-audio-d.a
memeify.exe: C:/Users/benad/Desktop/SFML-2.5.1/lib/libsfml-window-d.a
memeify.exe: C:/Users/benad/Desktop/SFML-2.5.1/lib/libsfml-system-d.a
memeify.exe: CMakeFiles/memeify.dir/linkLibs.rsp
memeify.exe: CMakeFiles/memeify.dir/objects1.rsp
memeify.exe: CMakeFiles/memeify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\benad\CLionProjects\lab10\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable memeify.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\memeify.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/memeify.dir/build: memeify.exe
.PHONY : CMakeFiles/memeify.dir/build

CMakeFiles/memeify.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\memeify.dir\cmake_clean.cmake
.PHONY : CMakeFiles/memeify.dir/clean

CMakeFiles/memeify.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\benad\CLionProjects\lab10 C:\Users\benad\CLionProjects\lab10 C:\Users\benad\CLionProjects\lab10 C:\Users\benad\CLionProjects\lab10 C:\Users\benad\CLionProjects\lab10\CMakeFiles\memeify.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/memeify.dir/depend

