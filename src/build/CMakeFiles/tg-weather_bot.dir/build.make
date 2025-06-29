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
CMAKE_SOURCE_DIR = /app

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /app/build

# Include any dependencies generated for this target.
include CMakeFiles/tg-weather_bot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tg-weather_bot.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tg-weather_bot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tg-weather_bot.dir/flags.make

CMakeFiles/tg-weather_bot.dir/main.cpp.o: CMakeFiles/tg-weather_bot.dir/flags.make
CMakeFiles/tg-weather_bot.dir/main.cpp.o: ../main.cpp
CMakeFiles/tg-weather_bot.dir/main.cpp.o: CMakeFiles/tg-weather_bot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tg-weather_bot.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tg-weather_bot.dir/main.cpp.o -MF CMakeFiles/tg-weather_bot.dir/main.cpp.o.d -o CMakeFiles/tg-weather_bot.dir/main.cpp.o -c /app/main.cpp

CMakeFiles/tg-weather_bot.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tg-weather_bot.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/main.cpp > CMakeFiles/tg-weather_bot.dir/main.cpp.i

CMakeFiles/tg-weather_bot.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tg-weather_bot.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/main.cpp -o CMakeFiles/tg-weather_bot.dir/main.cpp.s

CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o: CMakeFiles/tg-weather_bot.dir/flags.make
CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o: ../weatherapi.cpp
CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o: CMakeFiles/tg-weather_bot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o -MF CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o.d -o CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o -c /app/weatherapi.cpp

CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/weatherapi.cpp > CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.i

CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/weatherapi.cpp -o CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.s

CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o: CMakeFiles/tg-weather_bot.dir/flags.make
CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o: ../curleasy.cpp
CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o: CMakeFiles/tg-weather_bot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o -MF CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o.d -o CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o -c /app/curleasy.cpp

CMakeFiles/tg-weather_bot.dir/curleasy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tg-weather_bot.dir/curleasy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/curleasy.cpp > CMakeFiles/tg-weather_bot.dir/curleasy.cpp.i

CMakeFiles/tg-weather_bot.dir/curleasy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tg-weather_bot.dir/curleasy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/curleasy.cpp -o CMakeFiles/tg-weather_bot.dir/curleasy.cpp.s

CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o: CMakeFiles/tg-weather_bot.dir/flags.make
CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o: ../postgresclient.cpp
CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o: CMakeFiles/tg-weather_bot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o -MF CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o.d -o CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o -c /app/postgresclient.cpp

CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/postgresclient.cpp > CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.i

CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/postgresclient.cpp -o CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.s

# Object files for target tg-weather_bot
tg__weather_bot_OBJECTS = \
"CMakeFiles/tg-weather_bot.dir/main.cpp.o" \
"CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o" \
"CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o" \
"CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o"

# External object files for target tg-weather_bot
tg__weather_bot_EXTERNAL_OBJECTS =

tg-weather_bot: CMakeFiles/tg-weather_bot.dir/main.cpp.o
tg-weather_bot: CMakeFiles/tg-weather_bot.dir/weatherapi.cpp.o
tg-weather_bot: CMakeFiles/tg-weather_bot.dir/curleasy.cpp.o
tg-weather_bot: CMakeFiles/tg-weather_bot.dir/postgresclient.cpp.o
tg-weather_bot: CMakeFiles/tg-weather_bot.dir/build.make
tg-weather_bot: /usr/local/lib/libTgBot.a
tg-weather_bot: /usr/lib/x86_64-linux-gnu/libssl.so
tg-weather_bot: /usr/lib/x86_64-linux-gnu/libcrypto.so
tg-weather_bot: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
tg-weather_bot: /usr/lib/x86_64-linux-gnu/libcurl.so
tg-weather_bot: /usr/lib/x86_64-linux-gnu/libpq.so
tg-weather_bot: CMakeFiles/tg-weather_bot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable tg-weather_bot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tg-weather_bot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tg-weather_bot.dir/build: tg-weather_bot
.PHONY : CMakeFiles/tg-weather_bot.dir/build

CMakeFiles/tg-weather_bot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tg-weather_bot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tg-weather_bot.dir/clean

CMakeFiles/tg-weather_bot.dir/depend:
	cd /app/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /app /app /app/build /app/build /app/build/CMakeFiles/tg-weather_bot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tg-weather_bot.dir/depend

