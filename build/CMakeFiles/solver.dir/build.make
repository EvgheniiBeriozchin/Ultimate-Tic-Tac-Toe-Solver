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
CMAKE_SOURCE_DIR = /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build

# Include any dependencies generated for this target.
include CMakeFiles/solver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/solver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/solver.dir/flags.make

CMakeFiles/solver.dir/src/Board.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/Board.cpp.o: ../src/Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/solver.dir/src/Board.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solver.dir/src/Board.cpp.o -c /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/Board.cpp

CMakeFiles/solver.dir/src/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/Board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/Board.cpp > CMakeFiles/solver.dir/src/Board.cpp.i

CMakeFiles/solver.dir/src/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/Board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/Board.cpp -o CMakeFiles/solver.dir/src/Board.cpp.s

CMakeFiles/solver.dir/src/Board.cpp.o.requires:

.PHONY : CMakeFiles/solver.dir/src/Board.cpp.o.requires

CMakeFiles/solver.dir/src/Board.cpp.o.provides: CMakeFiles/solver.dir/src/Board.cpp.o.requires
	$(MAKE) -f CMakeFiles/solver.dir/build.make CMakeFiles/solver.dir/src/Board.cpp.o.provides.build
.PHONY : CMakeFiles/solver.dir/src/Board.cpp.o.provides

CMakeFiles/solver.dir/src/Board.cpp.o.provides.build: CMakeFiles/solver.dir/src/Board.cpp.o


CMakeFiles/solver.dir/src/TranspositionTable.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/TranspositionTable.cpp.o: ../src/TranspositionTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/solver.dir/src/TranspositionTable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solver.dir/src/TranspositionTable.cpp.o -c /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/TranspositionTable.cpp

CMakeFiles/solver.dir/src/TranspositionTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/TranspositionTable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/TranspositionTable.cpp > CMakeFiles/solver.dir/src/TranspositionTable.cpp.i

CMakeFiles/solver.dir/src/TranspositionTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/TranspositionTable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/TranspositionTable.cpp -o CMakeFiles/solver.dir/src/TranspositionTable.cpp.s

CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.requires:

.PHONY : CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.requires

CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.provides: CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.requires
	$(MAKE) -f CMakeFiles/solver.dir/build.make CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.provides.build
.PHONY : CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.provides

CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.provides.build: CMakeFiles/solver.dir/src/TranspositionTable.cpp.o


CMakeFiles/solver.dir/src/minimax.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/minimax.cpp.o: ../src/minimax.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/solver.dir/src/minimax.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solver.dir/src/minimax.cpp.o -c /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/minimax.cpp

CMakeFiles/solver.dir/src/minimax.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/minimax.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/minimax.cpp > CMakeFiles/solver.dir/src/minimax.cpp.i

CMakeFiles/solver.dir/src/minimax.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/minimax.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/minimax.cpp -o CMakeFiles/solver.dir/src/minimax.cpp.s

CMakeFiles/solver.dir/src/minimax.cpp.o.requires:

.PHONY : CMakeFiles/solver.dir/src/minimax.cpp.o.requires

CMakeFiles/solver.dir/src/minimax.cpp.o.provides: CMakeFiles/solver.dir/src/minimax.cpp.o.requires
	$(MAKE) -f CMakeFiles/solver.dir/build.make CMakeFiles/solver.dir/src/minimax.cpp.o.provides.build
.PHONY : CMakeFiles/solver.dir/src/minimax.cpp.o.provides

CMakeFiles/solver.dir/src/minimax.cpp.o.provides.build: CMakeFiles/solver.dir/src/minimax.cpp.o


CMakeFiles/solver.dir/src/main.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/solver.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solver.dir/src/main.cpp.o -c /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/main.cpp

CMakeFiles/solver.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/main.cpp > CMakeFiles/solver.dir/src/main.cpp.i

CMakeFiles/solver.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/main.cpp -o CMakeFiles/solver.dir/src/main.cpp.s

CMakeFiles/solver.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/solver.dir/src/main.cpp.o.requires

CMakeFiles/solver.dir/src/main.cpp.o.provides: CMakeFiles/solver.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/solver.dir/build.make CMakeFiles/solver.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/solver.dir/src/main.cpp.o.provides

CMakeFiles/solver.dir/src/main.cpp.o.provides.build: CMakeFiles/solver.dir/src/main.cpp.o


CMakeFiles/solver.dir/src/heuristic_functions.cpp.o: CMakeFiles/solver.dir/flags.make
CMakeFiles/solver.dir/src/heuristic_functions.cpp.o: ../src/heuristic_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/solver.dir/src/heuristic_functions.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solver.dir/src/heuristic_functions.cpp.o -c /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/heuristic_functions.cpp

CMakeFiles/solver.dir/src/heuristic_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solver.dir/src/heuristic_functions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/heuristic_functions.cpp > CMakeFiles/solver.dir/src/heuristic_functions.cpp.i

CMakeFiles/solver.dir/src/heuristic_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solver.dir/src/heuristic_functions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/src/heuristic_functions.cpp -o CMakeFiles/solver.dir/src/heuristic_functions.cpp.s

CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.requires:

.PHONY : CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.requires

CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.provides: CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.requires
	$(MAKE) -f CMakeFiles/solver.dir/build.make CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.provides.build
.PHONY : CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.provides

CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.provides.build: CMakeFiles/solver.dir/src/heuristic_functions.cpp.o


# Object files for target solver
solver_OBJECTS = \
"CMakeFiles/solver.dir/src/Board.cpp.o" \
"CMakeFiles/solver.dir/src/TranspositionTable.cpp.o" \
"CMakeFiles/solver.dir/src/minimax.cpp.o" \
"CMakeFiles/solver.dir/src/main.cpp.o" \
"CMakeFiles/solver.dir/src/heuristic_functions.cpp.o"

# External object files for target solver
solver_EXTERNAL_OBJECTS =

solver: CMakeFiles/solver.dir/src/Board.cpp.o
solver: CMakeFiles/solver.dir/src/TranspositionTable.cpp.o
solver: CMakeFiles/solver.dir/src/minimax.cpp.o
solver: CMakeFiles/solver.dir/src/main.cpp.o
solver: CMakeFiles/solver.dir/src/heuristic_functions.cpp.o
solver: CMakeFiles/solver.dir/build.make
solver: CMakeFiles/solver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable solver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/solver.dir/build: solver

.PHONY : CMakeFiles/solver.dir/build

CMakeFiles/solver.dir/requires: CMakeFiles/solver.dir/src/Board.cpp.o.requires
CMakeFiles/solver.dir/requires: CMakeFiles/solver.dir/src/TranspositionTable.cpp.o.requires
CMakeFiles/solver.dir/requires: CMakeFiles/solver.dir/src/minimax.cpp.o.requires
CMakeFiles/solver.dir/requires: CMakeFiles/solver.dir/src/main.cpp.o.requires
CMakeFiles/solver.dir/requires: CMakeFiles/solver.dir/src/heuristic_functions.cpp.o.requires

.PHONY : CMakeFiles/solver.dir/requires

CMakeFiles/solver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/solver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/solver.dir/clean

CMakeFiles/solver.dir/depend:
	cd /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build /home/evghenii/CS/Thesis/Ultimate-Tic-Tac-Toe-Solver/build/CMakeFiles/solver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/solver.dir/depend

