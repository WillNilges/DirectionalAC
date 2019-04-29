# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/nvidia/Documents/directionalac/cpp_code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nvidia/Documents/directionalac/cpp_code

# Include any dependencies generated for this target.
include CMakeFiles/dirac.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dirac.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dirac.dir/flags.make

CMakeFiles/dirac.dir/dirac.cpp.o: CMakeFiles/dirac.dir/flags.make
CMakeFiles/dirac.dir/dirac.cpp.o: dirac.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nvidia/Documents/directionalac/cpp_code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dirac.dir/dirac.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dirac.dir/dirac.cpp.o -c /home/nvidia/Documents/directionalac/cpp_code/dirac.cpp

CMakeFiles/dirac.dir/dirac.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dirac.dir/dirac.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nvidia/Documents/directionalac/cpp_code/dirac.cpp > CMakeFiles/dirac.dir/dirac.cpp.i

CMakeFiles/dirac.dir/dirac.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dirac.dir/dirac.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nvidia/Documents/directionalac/cpp_code/dirac.cpp -o CMakeFiles/dirac.dir/dirac.cpp.s

CMakeFiles/dirac.dir/dirac.cpp.o.requires:

.PHONY : CMakeFiles/dirac.dir/dirac.cpp.o.requires

CMakeFiles/dirac.dir/dirac.cpp.o.provides: CMakeFiles/dirac.dir/dirac.cpp.o.requires
	$(MAKE) -f CMakeFiles/dirac.dir/build.make CMakeFiles/dirac.dir/dirac.cpp.o.provides.build
.PHONY : CMakeFiles/dirac.dir/dirac.cpp.o.provides

CMakeFiles/dirac.dir/dirac.cpp.o.provides.build: CMakeFiles/dirac.dir/dirac.cpp.o


# Object files for target dirac
dirac_OBJECTS = \
"CMakeFiles/dirac.dir/dirac.cpp.o"

# External object files for target dirac
dirac_EXTERNAL_OBJECTS =

dirac: CMakeFiles/dirac.dir/dirac.cpp.o
dirac: CMakeFiles/dirac.dir/build.make
dirac: /usr/lib/libopencv_dnn.so.3.3.1
dirac: /usr/lib/libopencv_ml.so.3.3.1
dirac: /usr/lib/libopencv_objdetect.so.3.3.1
dirac: /usr/lib/libopencv_shape.so.3.3.1
dirac: /usr/lib/libopencv_stitching.so.3.3.1
dirac: /usr/lib/libopencv_superres.so.3.3.1
dirac: /usr/lib/libopencv_videostab.so.3.3.1
dirac: /usr/lib/libopencv_calib3d.so.3.3.1
dirac: /usr/lib/libopencv_features2d.so.3.3.1
dirac: /usr/lib/libopencv_flann.so.3.3.1
dirac: /usr/lib/libopencv_highgui.so.3.3.1
dirac: /usr/lib/libopencv_photo.so.3.3.1
dirac: /usr/lib/libopencv_video.so.3.3.1
dirac: /usr/lib/libopencv_videoio.so.3.3.1
dirac: /usr/lib/libopencv_imgcodecs.so.3.3.1
dirac: /usr/lib/libopencv_imgproc.so.3.3.1
dirac: /usr/lib/libopencv_core.so.3.3.1
dirac: CMakeFiles/dirac.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nvidia/Documents/directionalac/cpp_code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dirac"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dirac.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dirac.dir/build: dirac

.PHONY : CMakeFiles/dirac.dir/build

CMakeFiles/dirac.dir/requires: CMakeFiles/dirac.dir/dirac.cpp.o.requires

.PHONY : CMakeFiles/dirac.dir/requires

CMakeFiles/dirac.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dirac.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dirac.dir/clean

CMakeFiles/dirac.dir/depend:
	cd /home/nvidia/Documents/directionalac/cpp_code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nvidia/Documents/directionalac/cpp_code /home/nvidia/Documents/directionalac/cpp_code /home/nvidia/Documents/directionalac/cpp_code /home/nvidia/Documents/directionalac/cpp_code /home/nvidia/Documents/directionalac/cpp_code/CMakeFiles/dirac.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dirac.dir/depend
