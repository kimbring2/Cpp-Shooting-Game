# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /home/kimbring2/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/kimbring2/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kimbring2/CppND-Capstone-Shooting-Game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kimbring2/CppND-Capstone-Shooting-Game/build

# Include any dependencies generated for this target.
include CMakeFiles/ShootingGame.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ShootingGame.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ShootingGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ShootingGame.dir/flags.make

CMakeFiles/ShootingGame.dir/src/bullet.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/bullet.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/bullet.cpp
CMakeFiles/ShootingGame.dir/src/bullet.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ShootingGame.dir/src/bullet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/bullet.cpp.o -MF CMakeFiles/ShootingGame.dir/src/bullet.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/bullet.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/bullet.cpp

CMakeFiles/ShootingGame.dir/src/bullet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/bullet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/bullet.cpp > CMakeFiles/ShootingGame.dir/src/bullet.cpp.i

CMakeFiles/ShootingGame.dir/src/bullet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/bullet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/bullet.cpp -o CMakeFiles/ShootingGame.dir/src/bullet.cpp.s

CMakeFiles/ShootingGame.dir/src/controller.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/controller.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/controller.cpp
CMakeFiles/ShootingGame.dir/src/controller.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ShootingGame.dir/src/controller.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/controller.cpp.o -MF CMakeFiles/ShootingGame.dir/src/controller.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/controller.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/controller.cpp

CMakeFiles/ShootingGame.dir/src/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/controller.cpp > CMakeFiles/ShootingGame.dir/src/controller.cpp.i

CMakeFiles/ShootingGame.dir/src/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/controller.cpp -o CMakeFiles/ShootingGame.dir/src/controller.cpp.s

CMakeFiles/ShootingGame.dir/src/enemy.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/enemy.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/enemy.cpp
CMakeFiles/ShootingGame.dir/src/enemy.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ShootingGame.dir/src/enemy.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/enemy.cpp.o -MF CMakeFiles/ShootingGame.dir/src/enemy.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/enemy.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/enemy.cpp

CMakeFiles/ShootingGame.dir/src/enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/enemy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/enemy.cpp > CMakeFiles/ShootingGame.dir/src/enemy.cpp.i

CMakeFiles/ShootingGame.dir/src/enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/enemy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/enemy.cpp -o CMakeFiles/ShootingGame.dir/src/enemy.cpp.s

CMakeFiles/ShootingGame.dir/src/game.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/game.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/game.cpp
CMakeFiles/ShootingGame.dir/src/game.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ShootingGame.dir/src/game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/game.cpp.o -MF CMakeFiles/ShootingGame.dir/src/game.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/game.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/game.cpp

CMakeFiles/ShootingGame.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/game.cpp > CMakeFiles/ShootingGame.dir/src/game.cpp.i

CMakeFiles/ShootingGame.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/game.cpp -o CMakeFiles/ShootingGame.dir/src/game.cpp.s

CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/gameObject.cpp
CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o -MF CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/gameObject.cpp

CMakeFiles/ShootingGame.dir/src/gameObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/gameObject.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/gameObject.cpp > CMakeFiles/ShootingGame.dir/src/gameObject.cpp.i

CMakeFiles/ShootingGame.dir/src/gameObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/gameObject.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/gameObject.cpp -o CMakeFiles/ShootingGame.dir/src/gameObject.cpp.s

CMakeFiles/ShootingGame.dir/src/main.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/main.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/main.cpp
CMakeFiles/ShootingGame.dir/src/main.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ShootingGame.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/main.cpp.o -MF CMakeFiles/ShootingGame.dir/src/main.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/main.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/main.cpp

CMakeFiles/ShootingGame.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/main.cpp > CMakeFiles/ShootingGame.dir/src/main.cpp.i

CMakeFiles/ShootingGame.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/main.cpp -o CMakeFiles/ShootingGame.dir/src/main.cpp.s

CMakeFiles/ShootingGame.dir/src/mobile.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/mobile.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/mobile.cpp
CMakeFiles/ShootingGame.dir/src/mobile.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ShootingGame.dir/src/mobile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/mobile.cpp.o -MF CMakeFiles/ShootingGame.dir/src/mobile.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/mobile.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/mobile.cpp

CMakeFiles/ShootingGame.dir/src/mobile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/mobile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/mobile.cpp > CMakeFiles/ShootingGame.dir/src/mobile.cpp.i

CMakeFiles/ShootingGame.dir/src/mobile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/mobile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/mobile.cpp -o CMakeFiles/ShootingGame.dir/src/mobile.cpp.s

CMakeFiles/ShootingGame.dir/src/player.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/player.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/player.cpp
CMakeFiles/ShootingGame.dir/src/player.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ShootingGame.dir/src/player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/player.cpp.o -MF CMakeFiles/ShootingGame.dir/src/player.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/player.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/player.cpp

CMakeFiles/ShootingGame.dir/src/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/player.cpp > CMakeFiles/ShootingGame.dir/src/player.cpp.i

CMakeFiles/ShootingGame.dir/src/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/player.cpp -o CMakeFiles/ShootingGame.dir/src/player.cpp.s

CMakeFiles/ShootingGame.dir/src/renderer.cpp.o: CMakeFiles/ShootingGame.dir/flags.make
CMakeFiles/ShootingGame.dir/src/renderer.cpp.o: /home/kimbring2/CppND-Capstone-Shooting-Game/src/renderer.cpp
CMakeFiles/ShootingGame.dir/src/renderer.cpp.o: CMakeFiles/ShootingGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ShootingGame.dir/src/renderer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ShootingGame.dir/src/renderer.cpp.o -MF CMakeFiles/ShootingGame.dir/src/renderer.cpp.o.d -o CMakeFiles/ShootingGame.dir/src/renderer.cpp.o -c /home/kimbring2/CppND-Capstone-Shooting-Game/src/renderer.cpp

CMakeFiles/ShootingGame.dir/src/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ShootingGame.dir/src/renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kimbring2/CppND-Capstone-Shooting-Game/src/renderer.cpp > CMakeFiles/ShootingGame.dir/src/renderer.cpp.i

CMakeFiles/ShootingGame.dir/src/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ShootingGame.dir/src/renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kimbring2/CppND-Capstone-Shooting-Game/src/renderer.cpp -o CMakeFiles/ShootingGame.dir/src/renderer.cpp.s

# Object files for target ShootingGame
ShootingGame_OBJECTS = \
"CMakeFiles/ShootingGame.dir/src/bullet.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/controller.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/enemy.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/game.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/main.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/mobile.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/player.cpp.o" \
"CMakeFiles/ShootingGame.dir/src/renderer.cpp.o"

# External object files for target ShootingGame
ShootingGame_EXTERNAL_OBJECTS =

ShootingGame: CMakeFiles/ShootingGame.dir/src/bullet.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/controller.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/enemy.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/game.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/gameObject.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/main.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/mobile.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/player.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/src/renderer.cpp.o
ShootingGame: CMakeFiles/ShootingGame.dir/build.make
ShootingGame: CMakeFiles/ShootingGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ShootingGame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ShootingGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ShootingGame.dir/build: ShootingGame
.PHONY : CMakeFiles/ShootingGame.dir/build

CMakeFiles/ShootingGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ShootingGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ShootingGame.dir/clean

CMakeFiles/ShootingGame.dir/depend:
	cd /home/kimbring2/CppND-Capstone-Shooting-Game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kimbring2/CppND-Capstone-Shooting-Game /home/kimbring2/CppND-Capstone-Shooting-Game /home/kimbring2/CppND-Capstone-Shooting-Game/build /home/kimbring2/CppND-Capstone-Shooting-Game/build /home/kimbring2/CppND-Capstone-Shooting-Game/build/CMakeFiles/ShootingGame.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ShootingGame.dir/depend

