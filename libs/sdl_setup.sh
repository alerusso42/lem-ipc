#!/bin/bash

#SECTION - global variables

readonly LINKER_PATH=$(cd ../ && pwd)/build
readonly START_PATH="$PWD"
readonly BUILD_PATH="../build"
readonly LIBS_PATH="libs/"
readonly TEST_PATH="../test/sdl_valid_compilation.c"

#SECTION script setup

log_success()	{ echo -e "\033[1;32m[SUCCESS]\033[0m $1"; }
log_info()		{ echo -e "\033[1;34m[INFO]\033[0m $1"; }
log_error()		{ echo -e "\033[1;31m[ERROR]\033[0m $1"; }

#@description signal handler given to trap
#@param {number} $1:LINENO 			last executed line in script
#@param {string} $2:BASH_COMMAND 	last command executed
catch_error()
{
	log_error "line $1: '$2'" >&2
	exit 1
}

#@description setups syntax error protection and error handler
script_setup()
{
	log_info "script setup..."
	set -e				#DOC	=> e: exit on errors (check only )
	set -u				#DOC	=> u:track undefined variables
	set -E				#DOC	=> E:track functions
	shopt -s extglob	#DOC	=> shopt: allows shell to parse regex safely
	#set -x		#DEBUG	=> x: prints every command run
	#DOC	=> trap is like UNIX signal with argument handling
	#DOC	=> LINENO:last executed line in script
	#DOC	=> BASH_COMMAND: last command executed
	trap 'catch_error ${LINENO} "${BASH_COMMAND}"' ERR 
}

#SECTION - install

#description install sdl and sdl_mixer
sdl_install()
{
	log_info "SDL install..."
	test -d SDL 		|| git clone git@github.com:libsdl-org/SDL.git
	test -d SDL_mixer 	|| git clone git@github.com:libsdl-org/SDL_mixer.git
	test -d SDL_ttf 	|| git clone git@github.com:libsdl-org/SDL_ttf.git
}

#SECTION - compile

#description compiles SDL and SDL_mixer shared libraries
sdl_compile()
{
	log_info "SDL compilation..."
	cd SDL
	mkdir -p build && cd build
	cmake ../
	make
	cd ../../SDL_mixer && mkdir -p build && cd build
	#DOC	=>	SDL3_DIR is a cmake conf param to specify SDL shared library path.
	#			SDL_mixer requires SDL main library to work
	cmake ../ -DSDL3_DIR="$START_PATH"/SDL/build
	make
	cd ../../SDL_ttf && mkdir -p build && cd build
	#DOC	=>	SDL3_DIR is a cmake conf param to specify SDL shared library path.
	#			SDL_mixer requires SDL main library to work
	cmake ../ -DSDL3_DIR="$START_PATH"/SDL/build
	make
	cd ../../
	#DOC	=>	now shared libraries are moved into the build path.
	#			it's important that all shared libraries share the same directory (see LD_LIBRARY_PATH)
	mkdir -p "$BUILD_PATH"
	cp SDL/build/libSDL3.so SDL/build/libSDL3.so.0 "$BUILD_PATH"
	cp SDL_mixer/build/libSDL3_mixer.so SDL_mixer/build/libSDL3_mixer.so.0 "$BUILD_PATH"
	cp SDL_ttf/build/libSDL3_ttf.so SDL_ttf/build/libSDL3_ttf.so.0 "$BUILD_PATH"
}

#SECTION - test

#description tests if a sdl program can be compiled
sdl_test()
{
	log_info "test if everything works ok..."
	export LD_LIBRARY_PATH="$LINKER_PATH" && gcc -Wall -Wextra -Werror -g -I SDL/include/ -I SDL_mixer/include/ -I SDL_ttf/include/  -Wl,-rpath="$LINKER_PATH" "$TEST_PATH" "$BUILD_PATH"/libSDL3.so "$BUILD_PATH"/libSDL3_mixer.so "$BUILD_PATH"/libSDL3_ttf.so -o ./sdltest.out
	# rm ./sdltest.out
}

#SECTION - show usage

#description compiles SDL and SDL_mixer shared libraries
print_usage()
{
	log_success "SDL correctly setup!"
	log_info 	"To use it, run the following commands (more explaination in the bash script):\n\
	export LD_LIBRARY_PATH=[path to build directory] \n\
	gcc -Wall -Wextra -Werror -I $LIBS_PATH""SDL/include/ -I $LIBS_PATH""SDL_mixer/include/  -Wl,-rpath="$LINKER_PATH" [.c files to compile] [build path]/libSDL3.so [build path]/libSDL3_mixer.so"
	#DOC	=>	LD_LIBRARY_PATH:	a linker flag to specify the default shared libraries location. Must be set in .bashrc or exported in every new shell
	#DOC	=>	-I:					a compiler flag to specify the location of a set of .h files (ex: #include <SDL3/SDL3.h>)
	#DOC	=>	-Wl:				"hey gcc, do not interpet the next flag: give it directly to the linker"
	#DOC	=>	-rpath:				the path of shared libraries. Without this, if we wanted to run the executable in another path, the path of shared libraries would fail in the resolution
	#DOC	=>	[build]/libSDL3.so:	the path to the actual shared library files
}

main()
{
	script_setup
	sdl_install
	sdl_compile
	sdl_test
	print_usage
}

main