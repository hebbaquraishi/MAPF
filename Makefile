# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.20.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.20.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hebbaquraishi/Desktop/MAPF

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hebbaquraishi/Desktop/MAPF/CBS

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.20.1/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.20.1/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/hebbaquraishi/Desktop/MAPF/CBS/CMakeFiles /Users/hebbaquraishi/Desktop/MAPF/CBS//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/hebbaquraishi/Desktop/MAPF/CBS/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named MAPF

# Build rule for target.
MAPF: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 MAPF
.PHONY : MAPF

# fast build rule for target.
MAPF/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/build
.PHONY : MAPF/fast

AStar.o: AStar.cpp.o
.PHONY : AStar.o

# target to build an object file
AStar.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/AStar.cpp.o
.PHONY : AStar.cpp.o

AStar.i: AStar.cpp.i
.PHONY : AStar.i

# target to preprocess a source file
AStar.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/AStar.cpp.i
.PHONY : AStar.cpp.i

AStar.s: AStar.cpp.s
.PHONY : AStar.s

# target to generate assembly for a file
AStar.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/AStar.cpp.s
.PHONY : AStar.cpp.s

Agent.o: Agent.cpp.o
.PHONY : Agent.o

# target to build an object file
Agent.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Agent.cpp.o
.PHONY : Agent.cpp.o

Agent.i: Agent.cpp.i
.PHONY : Agent.i

# target to preprocess a source file
Agent.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Agent.cpp.i
.PHONY : Agent.cpp.i

Agent.s: Agent.cpp.s
.PHONY : Agent.s

# target to generate assembly for a file
Agent.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Agent.cpp.s
.PHONY : Agent.cpp.s

BreadthFirstSearch.o: BreadthFirstSearch.cpp.o
.PHONY : BreadthFirstSearch.o

# target to build an object file
BreadthFirstSearch.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/BreadthFirstSearch.cpp.o
.PHONY : BreadthFirstSearch.cpp.o

BreadthFirstSearch.i: BreadthFirstSearch.cpp.i
.PHONY : BreadthFirstSearch.i

# target to preprocess a source file
BreadthFirstSearch.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/BreadthFirstSearch.cpp.i
.PHONY : BreadthFirstSearch.cpp.i

BreadthFirstSearch.s: BreadthFirstSearch.cpp.s
.PHONY : BreadthFirstSearch.s

# target to generate assembly for a file
BreadthFirstSearch.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/BreadthFirstSearch.cpp.s
.PHONY : BreadthFirstSearch.cpp.s

ConstraintTree.o: ConstraintTree.cpp.o
.PHONY : ConstraintTree.o

# target to build an object file
ConstraintTree.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/ConstraintTree.cpp.o
.PHONY : ConstraintTree.cpp.o

ConstraintTree.i: ConstraintTree.cpp.i
.PHONY : ConstraintTree.i

# target to preprocess a source file
ConstraintTree.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/ConstraintTree.cpp.i
.PHONY : ConstraintTree.cpp.i

ConstraintTree.s: ConstraintTree.cpp.s
.PHONY : ConstraintTree.s

# target to generate assembly for a file
ConstraintTree.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/ConstraintTree.cpp.s
.PHONY : ConstraintTree.cpp.s

Graph.o: Graph.cpp.o
.PHONY : Graph.o

# target to build an object file
Graph.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Graph.cpp.o
.PHONY : Graph.cpp.o

Graph.i: Graph.cpp.i
.PHONY : Graph.i

# target to preprocess a source file
Graph.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Graph.cpp.i
.PHONY : Graph.cpp.i

Graph.s: Graph.cpp.s
.PHONY : Graph.s

# target to generate assembly for a file
Graph.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Graph.cpp.s
.PHONY : Graph.cpp.s

TSP.o: TSP.cpp.o
.PHONY : TSP.o

# target to build an object file
TSP.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/TSP.cpp.o
.PHONY : TSP.cpp.o

TSP.i: TSP.cpp.i
.PHONY : TSP.i

# target to preprocess a source file
TSP.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/TSP.cpp.i
.PHONY : TSP.cpp.i

TSP.s: TSP.cpp.s
.PHONY : TSP.s

# target to generate assembly for a file
TSP.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/TSP.cpp.s
.PHONY : TSP.cpp.s

TSPBranchAndBound.o: TSPBranchAndBound.cpp.o
.PHONY : TSPBranchAndBound.o

# target to build an object file
TSPBranchAndBound.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/TSPBranchAndBound.cpp.o
.PHONY : TSPBranchAndBound.cpp.o

TSPBranchAndBound.i: TSPBranchAndBound.cpp.i
.PHONY : TSPBranchAndBound.i

# target to preprocess a source file
TSPBranchAndBound.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/TSPBranchAndBound.cpp.i
.PHONY : TSPBranchAndBound.cpp.i

TSPBranchAndBound.s: TSPBranchAndBound.cpp.s
.PHONY : TSPBranchAndBound.s

# target to generate assembly for a file
TSPBranchAndBound.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/TSPBranchAndBound.cpp.s
.PHONY : TSPBranchAndBound.cpp.s

Vertex.o: Vertex.cpp.o
.PHONY : Vertex.o

# target to build an object file
Vertex.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Vertex.cpp.o
.PHONY : Vertex.cpp.o

Vertex.i: Vertex.cpp.i
.PHONY : Vertex.i

# target to preprocess a source file
Vertex.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Vertex.cpp.i
.PHONY : Vertex.cpp.i

Vertex.s: Vertex.cpp.s
.PHONY : Vertex.s

# target to generate assembly for a file
Vertex.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/Vertex.cpp.s
.PHONY : Vertex.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MAPF.dir/build.make CMakeFiles/MAPF.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... MAPF"
	@echo "... AStar.o"
	@echo "... AStar.i"
	@echo "... AStar.s"
	@echo "... Agent.o"
	@echo "... Agent.i"
	@echo "... Agent.s"
	@echo "... BreadthFirstSearch.o"
	@echo "... BreadthFirstSearch.i"
	@echo "... BreadthFirstSearch.s"
	@echo "... ConstraintTree.o"
	@echo "... ConstraintTree.i"
	@echo "... ConstraintTree.s"
	@echo "... Graph.o"
	@echo "... Graph.i"
	@echo "... Graph.s"
	@echo "... TSP.o"
	@echo "... TSP.i"
	@echo "... TSP.s"
	@echo "... TSPBranchAndBound.o"
	@echo "... TSPBranchAndBound.i"
	@echo "... TSPBranchAndBound.s"
	@echo "... Vertex.o"
	@echo "... Vertex.i"
	@echo "... Vertex.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

