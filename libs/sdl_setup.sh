#!/bin/bash

#SECTION - global variables

G_CONF_BUILD_PATH="../build"
G_CONF_LIBS_PATH="libs/"
G_CONF_TEST_PATH="test/sdl_valid_compilation.c"

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
	git clone git@github.com:libsdl-org/SDL.git
	git clone git@github.com:libsdl-org/SDL_mixer.git
}

#SECTION - compile

#description compiles SDL and SDL_mixer shared libraries
sdl_compile()
{
	log_info "SDL compilation..."
	cd SDL
	mkdir build && cd build
	cmake ../
	make
	cd ../../SDL_mixer && mkdir build && cd build
	#DOC	=>	SDL3_DIR is a cmake conf param to specify SDL shared library path.
	#			SDL_mixer requires SDL main library to work
	cmake ../ -DSDL3_DIR=/home/alerusso/Desktop/sdl-tests/SDL/build
	make
	cd ../../
	#DOC	=>	now shared libraries are moved into the build path.
	#			it's important that all shared libraries share the same directory (see LD_LIBRARY_PATH)
	mkdir -p "$G_CONF_BUILD"
	cp SDL/build/libSDL3.so SDL/build/libSDL3.so.0 "$G_CONF_BUILD"
	cp SDL_mixer/build/libSDL3_mixer.so SDL_mixer/build/libSDL3_mixer.so.0 "$G_CONF_BUILD"
}

#SECTION - test

#description tests if a sdl program can be compiled
test()
{
	log_info "test if everything works ok..."
	cd ..
	gcc -Wall -Wextra -Werror -I "$G_CONF_LIBS_PATH"/SDL/include/ -I "$G_CONF_LIBS_PATH"/SDL_mixer/include/  -Wl,-rpath="$PWD"/"$G_CONF_BUILD_PATH" "$G_CONF_BUILD_PATH"/libSDL3.so "$G_CONF_BUILD_PATH"/libSDL3_mixer.so "$G_CONF_TEST_PATH" -o ./sdltest.out
	rm ./sdltest.out
}

#SECTION - show usage

#description compiles SDL and SDL_mixer shared libraries
print_usage()
{
	log_success "SDL correctly setup!"
	log_info 	"To use it, run the following commands (more explaination in the bash script):\n\
	export LD_LIBRARY_PATH=$G_CONF_BUILD \n\
	gcc -Wall -Wextra -Werror -I $G_CONF_LIBS_PATH/SDL/include/ -I $G_CONF_LIBS_PATH/SDL_mixer/include/  -Wl,-rpath=$PWD"/"$G_CONF_BUILD_PATH $G_CONF_BUILD_PATH/libSDL3.so $G_CONF_BUILD_PATH/libSDL3_mixer.so [.c files to compile] "
	#DOC	=>	LD_LIBRARY_PATH:	a linker flag to specify the default shared libraries location. Must be set in .bashrc or exported in every new shell
	#DOC	=>	-I:					a compiler flag to specify the location of a set of .h files (ex: #include <SDL3/SDL3.h>)
	#DOC	=>	-Wl:				"hey gcc, do not interpet the next flag: give it directly to the linker"
	#DOC	=>	-rpath:				the path of shared libraries. Without this, if we wanted to run the executable in another path, the path of shared libraries would fail in the resolution
}

main()
{
	script_setup
	sdl_install
	sdl_compile
	test
	print_usage
}
