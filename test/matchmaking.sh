#!/bin/bash

#SECTION - global variables

readonly PATH_ROOT="../"

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

#SECTION tests



main()
{
	script_setup
}

main