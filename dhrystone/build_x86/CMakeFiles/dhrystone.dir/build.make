# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/hhsw/桌面/dhrystone-new

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hhsw/桌面/dhrystone-new/build_x86

# Include any dependencies generated for this target.
include CMakeFiles/dhrystone.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dhrystone.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dhrystone.dir/flags.make

CMakeFiles/dhrystone.dir/dhry_1.c.o: CMakeFiles/dhrystone.dir/flags.make
CMakeFiles/dhrystone.dir/dhry_1.c.o: ../dhry_1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hhsw/桌面/dhrystone-new/build_x86/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dhrystone.dir/dhry_1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dhrystone.dir/dhry_1.c.o   -c /home/hhsw/桌面/dhrystone-new/dhry_1.c

CMakeFiles/dhrystone.dir/dhry_1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dhrystone.dir/dhry_1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hhsw/桌面/dhrystone-new/dhry_1.c > CMakeFiles/dhrystone.dir/dhry_1.c.i

CMakeFiles/dhrystone.dir/dhry_1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dhrystone.dir/dhry_1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hhsw/桌面/dhrystone-new/dhry_1.c -o CMakeFiles/dhrystone.dir/dhry_1.c.s

CMakeFiles/dhrystone.dir/dhry_2.c.o: CMakeFiles/dhrystone.dir/flags.make
CMakeFiles/dhrystone.dir/dhry_2.c.o: ../dhry_2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hhsw/桌面/dhrystone-new/build_x86/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/dhrystone.dir/dhry_2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dhrystone.dir/dhry_2.c.o   -c /home/hhsw/桌面/dhrystone-new/dhry_2.c

CMakeFiles/dhrystone.dir/dhry_2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dhrystone.dir/dhry_2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hhsw/桌面/dhrystone-new/dhry_2.c > CMakeFiles/dhrystone.dir/dhry_2.c.i

CMakeFiles/dhrystone.dir/dhry_2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dhrystone.dir/dhry_2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hhsw/桌面/dhrystone-new/dhry_2.c -o CMakeFiles/dhrystone.dir/dhry_2.c.s

# Object files for target dhrystone
dhrystone_OBJECTS = \
"CMakeFiles/dhrystone.dir/dhry_1.c.o" \
"CMakeFiles/dhrystone.dir/dhry_2.c.o"

# External object files for target dhrystone
dhrystone_EXTERNAL_OBJECTS =

dhrystone: CMakeFiles/dhrystone.dir/dhry_1.c.o
dhrystone: CMakeFiles/dhrystone.dir/dhry_2.c.o
dhrystone: CMakeFiles/dhrystone.dir/build.make
dhrystone: CMakeFiles/dhrystone.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hhsw/桌面/dhrystone-new/build_x86/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable dhrystone"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dhrystone.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dhrystone.dir/build: dhrystone

.PHONY : CMakeFiles/dhrystone.dir/build

CMakeFiles/dhrystone.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dhrystone.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dhrystone.dir/clean

CMakeFiles/dhrystone.dir/depend:
	cd /home/hhsw/桌面/dhrystone-new/build_x86 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hhsw/桌面/dhrystone-new /home/hhsw/桌面/dhrystone-new /home/hhsw/桌面/dhrystone-new/build_x86 /home/hhsw/桌面/dhrystone-new/build_x86 /home/hhsw/桌面/dhrystone-new/build_x86/CMakeFiles/dhrystone.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dhrystone.dir/depend

