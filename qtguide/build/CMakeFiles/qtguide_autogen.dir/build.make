# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xdoo/workspace/qt_Learning/qtguide

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xdoo/workspace/qt_Learning/qtguide/build

# Utility rule file for qtguide_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/qtguide_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qtguide_autogen.dir/progress.make

CMakeFiles/qtguide_autogen: qtguide_autogen/timestamp

qtguide_autogen/timestamp: /usr/bin/moc
qtguide_autogen/timestamp: /usr/bin/uic
qtguide_autogen/timestamp: CMakeFiles/qtguide_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/xdoo/workspace/qt_Learning/qtguide/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target qtguide"
	/usr/bin/cmake -E cmake_autogen /home/xdoo/workspace/qt_Learning/qtguide/build/CMakeFiles/qtguide_autogen.dir/AutogenInfo.json ""
	/usr/bin/cmake -E touch /home/xdoo/workspace/qt_Learning/qtguide/build/qtguide_autogen/timestamp

CMakeFiles/qtguide_autogen.dir/codegen:
.PHONY : CMakeFiles/qtguide_autogen.dir/codegen

qtguide_autogen: CMakeFiles/qtguide_autogen
qtguide_autogen: qtguide_autogen/timestamp
qtguide_autogen: CMakeFiles/qtguide_autogen.dir/build.make
.PHONY : qtguide_autogen

# Rule to build all files generated by this target.
CMakeFiles/qtguide_autogen.dir/build: qtguide_autogen
.PHONY : CMakeFiles/qtguide_autogen.dir/build

CMakeFiles/qtguide_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qtguide_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qtguide_autogen.dir/clean

CMakeFiles/qtguide_autogen.dir/depend:
	cd /home/xdoo/workspace/qt_Learning/qtguide/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xdoo/workspace/qt_Learning/qtguide /home/xdoo/workspace/qt_Learning/qtguide /home/xdoo/workspace/qt_Learning/qtguide/build /home/xdoo/workspace/qt_Learning/qtguide/build /home/xdoo/workspace/qt_Learning/qtguide/build/CMakeFiles/qtguide_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/qtguide_autogen.dir/depend

