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
CMAKE_SOURCE_DIR = /home/lihan/tinywebserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lihan/tinywebserver/build

# Include any dependencies generated for this target.
include CMakeFiles/testmuduo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testmuduo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testmuduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testmuduo.dir/flags.make

CMakeFiles/testmuduo.dir/acceptor.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/acceptor.o: ../acceptor.cc
CMakeFiles/testmuduo.dir/acceptor.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testmuduo.dir/acceptor.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/acceptor.o -MF CMakeFiles/testmuduo.dir/acceptor.o.d -o CMakeFiles/testmuduo.dir/acceptor.o -c /home/lihan/tinywebserver/acceptor.cc

CMakeFiles/testmuduo.dir/acceptor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/acceptor.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/acceptor.cc > CMakeFiles/testmuduo.dir/acceptor.i

CMakeFiles/testmuduo.dir/acceptor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/acceptor.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/acceptor.cc -o CMakeFiles/testmuduo.dir/acceptor.s

CMakeFiles/testmuduo.dir/buffer.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/buffer.o: ../buffer.cc
CMakeFiles/testmuduo.dir/buffer.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testmuduo.dir/buffer.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/buffer.o -MF CMakeFiles/testmuduo.dir/buffer.o.d -o CMakeFiles/testmuduo.dir/buffer.o -c /home/lihan/tinywebserver/buffer.cc

CMakeFiles/testmuduo.dir/buffer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/buffer.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/buffer.cc > CMakeFiles/testmuduo.dir/buffer.i

CMakeFiles/testmuduo.dir/buffer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/buffer.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/buffer.cc -o CMakeFiles/testmuduo.dir/buffer.s

CMakeFiles/testmuduo.dir/callbacks.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/callbacks.o: ../callbacks.cc
CMakeFiles/testmuduo.dir/callbacks.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/testmuduo.dir/callbacks.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/callbacks.o -MF CMakeFiles/testmuduo.dir/callbacks.o.d -o CMakeFiles/testmuduo.dir/callbacks.o -c /home/lihan/tinywebserver/callbacks.cc

CMakeFiles/testmuduo.dir/callbacks.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/callbacks.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/callbacks.cc > CMakeFiles/testmuduo.dir/callbacks.i

CMakeFiles/testmuduo.dir/callbacks.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/callbacks.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/callbacks.cc -o CMakeFiles/testmuduo.dir/callbacks.s

CMakeFiles/testmuduo.dir/channel.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/channel.o: ../channel.cc
CMakeFiles/testmuduo.dir/channel.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/testmuduo.dir/channel.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/channel.o -MF CMakeFiles/testmuduo.dir/channel.o.d -o CMakeFiles/testmuduo.dir/channel.o -c /home/lihan/tinywebserver/channel.cc

CMakeFiles/testmuduo.dir/channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/channel.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/channel.cc > CMakeFiles/testmuduo.dir/channel.i

CMakeFiles/testmuduo.dir/channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/channel.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/channel.cc -o CMakeFiles/testmuduo.dir/channel.s

CMakeFiles/testmuduo.dir/currentthread.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/currentthread.o: ../currentthread.cc
CMakeFiles/testmuduo.dir/currentthread.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/testmuduo.dir/currentthread.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/currentthread.o -MF CMakeFiles/testmuduo.dir/currentthread.o.d -o CMakeFiles/testmuduo.dir/currentthread.o -c /home/lihan/tinywebserver/currentthread.cc

CMakeFiles/testmuduo.dir/currentthread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/currentthread.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/currentthread.cc > CMakeFiles/testmuduo.dir/currentthread.i

CMakeFiles/testmuduo.dir/currentthread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/currentthread.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/currentthread.cc -o CMakeFiles/testmuduo.dir/currentthread.s

CMakeFiles/testmuduo.dir/defaultpoller.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/defaultpoller.o: ../defaultpoller.cc
CMakeFiles/testmuduo.dir/defaultpoller.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/testmuduo.dir/defaultpoller.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/defaultpoller.o -MF CMakeFiles/testmuduo.dir/defaultpoller.o.d -o CMakeFiles/testmuduo.dir/defaultpoller.o -c /home/lihan/tinywebserver/defaultpoller.cc

CMakeFiles/testmuduo.dir/defaultpoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/defaultpoller.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/defaultpoller.cc > CMakeFiles/testmuduo.dir/defaultpoller.i

CMakeFiles/testmuduo.dir/defaultpoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/defaultpoller.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/defaultpoller.cc -o CMakeFiles/testmuduo.dir/defaultpoller.s

CMakeFiles/testmuduo.dir/epollpoller.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/epollpoller.o: ../epollpoller.cc
CMakeFiles/testmuduo.dir/epollpoller.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/testmuduo.dir/epollpoller.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/epollpoller.o -MF CMakeFiles/testmuduo.dir/epollpoller.o.d -o CMakeFiles/testmuduo.dir/epollpoller.o -c /home/lihan/tinywebserver/epollpoller.cc

CMakeFiles/testmuduo.dir/epollpoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/epollpoller.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/epollpoller.cc > CMakeFiles/testmuduo.dir/epollpoller.i

CMakeFiles/testmuduo.dir/epollpoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/epollpoller.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/epollpoller.cc -o CMakeFiles/testmuduo.dir/epollpoller.s

CMakeFiles/testmuduo.dir/eventloop.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/eventloop.o: ../eventloop.cc
CMakeFiles/testmuduo.dir/eventloop.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/testmuduo.dir/eventloop.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/eventloop.o -MF CMakeFiles/testmuduo.dir/eventloop.o.d -o CMakeFiles/testmuduo.dir/eventloop.o -c /home/lihan/tinywebserver/eventloop.cc

CMakeFiles/testmuduo.dir/eventloop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/eventloop.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/eventloop.cc > CMakeFiles/testmuduo.dir/eventloop.i

CMakeFiles/testmuduo.dir/eventloop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/eventloop.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/eventloop.cc -o CMakeFiles/testmuduo.dir/eventloop.s

CMakeFiles/testmuduo.dir/eventloopthread.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/eventloopthread.o: ../eventloopthread.cc
CMakeFiles/testmuduo.dir/eventloopthread.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/testmuduo.dir/eventloopthread.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/eventloopthread.o -MF CMakeFiles/testmuduo.dir/eventloopthread.o.d -o CMakeFiles/testmuduo.dir/eventloopthread.o -c /home/lihan/tinywebserver/eventloopthread.cc

CMakeFiles/testmuduo.dir/eventloopthread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/eventloopthread.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/eventloopthread.cc > CMakeFiles/testmuduo.dir/eventloopthread.i

CMakeFiles/testmuduo.dir/eventloopthread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/eventloopthread.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/eventloopthread.cc -o CMakeFiles/testmuduo.dir/eventloopthread.s

CMakeFiles/testmuduo.dir/eventloopthreadpool.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/eventloopthreadpool.o: ../eventloopthreadpool.cc
CMakeFiles/testmuduo.dir/eventloopthreadpool.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/testmuduo.dir/eventloopthreadpool.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/eventloopthreadpool.o -MF CMakeFiles/testmuduo.dir/eventloopthreadpool.o.d -o CMakeFiles/testmuduo.dir/eventloopthreadpool.o -c /home/lihan/tinywebserver/eventloopthreadpool.cc

CMakeFiles/testmuduo.dir/eventloopthreadpool.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/eventloopthreadpool.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/eventloopthreadpool.cc > CMakeFiles/testmuduo.dir/eventloopthreadpool.i

CMakeFiles/testmuduo.dir/eventloopthreadpool.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/eventloopthreadpool.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/eventloopthreadpool.cc -o CMakeFiles/testmuduo.dir/eventloopthreadpool.s

CMakeFiles/testmuduo.dir/inetaddress.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/inetaddress.o: ../inetaddress.cc
CMakeFiles/testmuduo.dir/inetaddress.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/testmuduo.dir/inetaddress.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/inetaddress.o -MF CMakeFiles/testmuduo.dir/inetaddress.o.d -o CMakeFiles/testmuduo.dir/inetaddress.o -c /home/lihan/tinywebserver/inetaddress.cc

CMakeFiles/testmuduo.dir/inetaddress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/inetaddress.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/inetaddress.cc > CMakeFiles/testmuduo.dir/inetaddress.i

CMakeFiles/testmuduo.dir/inetaddress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/inetaddress.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/inetaddress.cc -o CMakeFiles/testmuduo.dir/inetaddress.s

CMakeFiles/testmuduo.dir/log.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/log.o: ../log.cc
CMakeFiles/testmuduo.dir/log.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/testmuduo.dir/log.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/log.o -MF CMakeFiles/testmuduo.dir/log.o.d -o CMakeFiles/testmuduo.dir/log.o -c /home/lihan/tinywebserver/log.cc

CMakeFiles/testmuduo.dir/log.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/log.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/log.cc > CMakeFiles/testmuduo.dir/log.i

CMakeFiles/testmuduo.dir/log.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/log.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/log.cc -o CMakeFiles/testmuduo.dir/log.s

CMakeFiles/testmuduo.dir/poller.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/poller.o: ../poller.cc
CMakeFiles/testmuduo.dir/poller.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/testmuduo.dir/poller.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/poller.o -MF CMakeFiles/testmuduo.dir/poller.o.d -o CMakeFiles/testmuduo.dir/poller.o -c /home/lihan/tinywebserver/poller.cc

CMakeFiles/testmuduo.dir/poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/poller.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/poller.cc > CMakeFiles/testmuduo.dir/poller.i

CMakeFiles/testmuduo.dir/poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/poller.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/poller.cc -o CMakeFiles/testmuduo.dir/poller.s

CMakeFiles/testmuduo.dir/socket.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/socket.o: ../socket.cc
CMakeFiles/testmuduo.dir/socket.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/testmuduo.dir/socket.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/socket.o -MF CMakeFiles/testmuduo.dir/socket.o.d -o CMakeFiles/testmuduo.dir/socket.o -c /home/lihan/tinywebserver/socket.cc

CMakeFiles/testmuduo.dir/socket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/socket.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/socket.cc > CMakeFiles/testmuduo.dir/socket.i

CMakeFiles/testmuduo.dir/socket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/socket.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/socket.cc -o CMakeFiles/testmuduo.dir/socket.s

CMakeFiles/testmuduo.dir/tcpconnection.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/tcpconnection.o: ../tcpconnection.cc
CMakeFiles/testmuduo.dir/tcpconnection.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/testmuduo.dir/tcpconnection.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/tcpconnection.o -MF CMakeFiles/testmuduo.dir/tcpconnection.o.d -o CMakeFiles/testmuduo.dir/tcpconnection.o -c /home/lihan/tinywebserver/tcpconnection.cc

CMakeFiles/testmuduo.dir/tcpconnection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/tcpconnection.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/tcpconnection.cc > CMakeFiles/testmuduo.dir/tcpconnection.i

CMakeFiles/testmuduo.dir/tcpconnection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/tcpconnection.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/tcpconnection.cc -o CMakeFiles/testmuduo.dir/tcpconnection.s

CMakeFiles/testmuduo.dir/tcpserver.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/tcpserver.o: ../tcpserver.cc
CMakeFiles/testmuduo.dir/tcpserver.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/testmuduo.dir/tcpserver.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/tcpserver.o -MF CMakeFiles/testmuduo.dir/tcpserver.o.d -o CMakeFiles/testmuduo.dir/tcpserver.o -c /home/lihan/tinywebserver/tcpserver.cc

CMakeFiles/testmuduo.dir/tcpserver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/tcpserver.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/tcpserver.cc > CMakeFiles/testmuduo.dir/tcpserver.i

CMakeFiles/testmuduo.dir/tcpserver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/tcpserver.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/tcpserver.cc -o CMakeFiles/testmuduo.dir/tcpserver.s

CMakeFiles/testmuduo.dir/test_main.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/test_main.o: ../test_main.cc
CMakeFiles/testmuduo.dir/test_main.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/testmuduo.dir/test_main.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/test_main.o -MF CMakeFiles/testmuduo.dir/test_main.o.d -o CMakeFiles/testmuduo.dir/test_main.o -c /home/lihan/tinywebserver/test_main.cc

CMakeFiles/testmuduo.dir/test_main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/test_main.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/test_main.cc > CMakeFiles/testmuduo.dir/test_main.i

CMakeFiles/testmuduo.dir/test_main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/test_main.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/test_main.cc -o CMakeFiles/testmuduo.dir/test_main.s

CMakeFiles/testmuduo.dir/thread.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/thread.o: ../thread.cc
CMakeFiles/testmuduo.dir/thread.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/testmuduo.dir/thread.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/thread.o -MF CMakeFiles/testmuduo.dir/thread.o.d -o CMakeFiles/testmuduo.dir/thread.o -c /home/lihan/tinywebserver/thread.cc

CMakeFiles/testmuduo.dir/thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/thread.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/thread.cc > CMakeFiles/testmuduo.dir/thread.i

CMakeFiles/testmuduo.dir/thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/thread.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/thread.cc -o CMakeFiles/testmuduo.dir/thread.s

CMakeFiles/testmuduo.dir/timestamp.o: CMakeFiles/testmuduo.dir/flags.make
CMakeFiles/testmuduo.dir/timestamp.o: ../timestamp.cc
CMakeFiles/testmuduo.dir/timestamp.o: CMakeFiles/testmuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/testmuduo.dir/timestamp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testmuduo.dir/timestamp.o -MF CMakeFiles/testmuduo.dir/timestamp.o.d -o CMakeFiles/testmuduo.dir/timestamp.o -c /home/lihan/tinywebserver/timestamp.cc

CMakeFiles/testmuduo.dir/timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmuduo.dir/timestamp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lihan/tinywebserver/timestamp.cc > CMakeFiles/testmuduo.dir/timestamp.i

CMakeFiles/testmuduo.dir/timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmuduo.dir/timestamp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lihan/tinywebserver/timestamp.cc -o CMakeFiles/testmuduo.dir/timestamp.s

# Object files for target testmuduo
testmuduo_OBJECTS = \
"CMakeFiles/testmuduo.dir/acceptor.o" \
"CMakeFiles/testmuduo.dir/buffer.o" \
"CMakeFiles/testmuduo.dir/callbacks.o" \
"CMakeFiles/testmuduo.dir/channel.o" \
"CMakeFiles/testmuduo.dir/currentthread.o" \
"CMakeFiles/testmuduo.dir/defaultpoller.o" \
"CMakeFiles/testmuduo.dir/epollpoller.o" \
"CMakeFiles/testmuduo.dir/eventloop.o" \
"CMakeFiles/testmuduo.dir/eventloopthread.o" \
"CMakeFiles/testmuduo.dir/eventloopthreadpool.o" \
"CMakeFiles/testmuduo.dir/inetaddress.o" \
"CMakeFiles/testmuduo.dir/log.o" \
"CMakeFiles/testmuduo.dir/poller.o" \
"CMakeFiles/testmuduo.dir/socket.o" \
"CMakeFiles/testmuduo.dir/tcpconnection.o" \
"CMakeFiles/testmuduo.dir/tcpserver.o" \
"CMakeFiles/testmuduo.dir/test_main.o" \
"CMakeFiles/testmuduo.dir/thread.o" \
"CMakeFiles/testmuduo.dir/timestamp.o"

# External object files for target testmuduo
testmuduo_EXTERNAL_OBJECTS =

testmuduo: CMakeFiles/testmuduo.dir/acceptor.o
testmuduo: CMakeFiles/testmuduo.dir/buffer.o
testmuduo: CMakeFiles/testmuduo.dir/callbacks.o
testmuduo: CMakeFiles/testmuduo.dir/channel.o
testmuduo: CMakeFiles/testmuduo.dir/currentthread.o
testmuduo: CMakeFiles/testmuduo.dir/defaultpoller.o
testmuduo: CMakeFiles/testmuduo.dir/epollpoller.o
testmuduo: CMakeFiles/testmuduo.dir/eventloop.o
testmuduo: CMakeFiles/testmuduo.dir/eventloopthread.o
testmuduo: CMakeFiles/testmuduo.dir/eventloopthreadpool.o
testmuduo: CMakeFiles/testmuduo.dir/inetaddress.o
testmuduo: CMakeFiles/testmuduo.dir/log.o
testmuduo: CMakeFiles/testmuduo.dir/poller.o
testmuduo: CMakeFiles/testmuduo.dir/socket.o
testmuduo: CMakeFiles/testmuduo.dir/tcpconnection.o
testmuduo: CMakeFiles/testmuduo.dir/tcpserver.o
testmuduo: CMakeFiles/testmuduo.dir/test_main.o
testmuduo: CMakeFiles/testmuduo.dir/thread.o
testmuduo: CMakeFiles/testmuduo.dir/timestamp.o
testmuduo: CMakeFiles/testmuduo.dir/build.make
testmuduo: CMakeFiles/testmuduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lihan/tinywebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Linking CXX executable testmuduo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testmuduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testmuduo.dir/build: testmuduo
.PHONY : CMakeFiles/testmuduo.dir/build

CMakeFiles/testmuduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testmuduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testmuduo.dir/clean

CMakeFiles/testmuduo.dir/depend:
	cd /home/lihan/tinywebserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lihan/tinywebserver /home/lihan/tinywebserver /home/lihan/tinywebserver/build /home/lihan/tinywebserver/build /home/lihan/tinywebserver/build/CMakeFiles/testmuduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testmuduo.dir/depend

