# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/nr-gnb.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/nr-gnb.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nr-gnb.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nr-gnb.dir/flags.make

CMakeFiles/nr-gnb.dir/src/gnb.cpp.o: CMakeFiles/nr-gnb.dir/flags.make
CMakeFiles/nr-gnb.dir/src/gnb.cpp.o: ../src/gnb.cpp
CMakeFiles/nr-gnb.dir/src/gnb.cpp.o: CMakeFiles/nr-gnb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nr-gnb.dir/src/gnb.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nr-gnb.dir/src/gnb.cpp.o -MF CMakeFiles/nr-gnb.dir/src/gnb.cpp.o.d -o CMakeFiles/nr-gnb.dir/src/gnb.cpp.o -c /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/src/gnb.cpp

CMakeFiles/nr-gnb.dir/src/gnb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nr-gnb.dir/src/gnb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/src/gnb.cpp > CMakeFiles/nr-gnb.dir/src/gnb.cpp.i

CMakeFiles/nr-gnb.dir/src/gnb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nr-gnb.dir/src/gnb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/src/gnb.cpp -o CMakeFiles/nr-gnb.dir/src/gnb.cpp.s

# Object files for target nr-gnb
nr__gnb_OBJECTS = \
"CMakeFiles/nr-gnb.dir/src/gnb.cpp.o"

# External object files for target nr-gnb
nr__gnb_EXTERNAL_OBJECTS =

nr-gnb: CMakeFiles/nr-gnb.dir/src/gnb.cpp.o
nr-gnb: CMakeFiles/nr-gnb.dir/build.make
nr-gnb: src/asn/rrc/libasn-rrc.a
nr-gnb: src/asn/ngap/libasn-ngap.a
nr-gnb: src/lib/libcommon-lib.a
nr-gnb: src/gnb/libgnb.a
nr-gnb: src/lib/libcommon-lib.a
nr-gnb: src/asn/rrc/libasn-rrc.a
nr-gnb: src/asn/ngap/libasn-ngap.a
nr-gnb: src/asn/asn1c/libasn-asn1c.a
nr-gnb: src/utils/libutils.a
nr-gnb: src/ext/libext.a
nr-gnb: CMakeFiles/nr-gnb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nr-gnb"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nr-gnb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nr-gnb.dir/build: nr-gnb
.PHONY : CMakeFiles/nr-gnb.dir/build

CMakeFiles/nr-gnb.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nr-gnb.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nr-gnb.dir/clean

CMakeFiles/nr-gnb.dir/depend:
	cd /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/cmake-build-release /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/cmake-build-release /home/ubuntu/OAI-bpf-upf/Core-NFs/UERANSIM-OAI/cmake-build-release/CMakeFiles/nr-gnb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nr-gnb.dir/depend

