#!/bin/bash

#SECTION - global variables

readonly PATH_SUPP="test/valgrind.supp"
readonly PATH_SCRIPT="test/spawn_child.sh"
readonly PATH_SHM="/dev/shm/lem-ipc_shared_memory"
readonly NAME="lem-ipc"
readonly CHILD_MAX="30"

CHILD_NUM="0"
USE_VALGRIND="false"
USE_GDB="false"
ARGS=""

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

#https://stackoverflow.com/questions/806906/how-do-i-test-if-a-variable-is-a-number-in-bash
is_num()
{
	local n="$1"

	if test "$n" != "" && test "$n" -eq "$n" 2>/dev/null; then
		echo -n "true"
	else
		echo -n "false"
	fi
}

#@description setups syntax error protection and error handler
script_setup()
{
	local check

	log_info "script setup..."
	check=$(is_num "$1")
	if test "$check" = "false" || test "$1" -lt "0" || test "$1" -gt "$CHILD_MAX"; then
		log_error "Usage: $0 [number between 0 and $CHILD_MAX] [OPTIONAL: --valgrind || --gdb || --wait] [OPTIONAL: lem-ipc flags]"
		exit 1
	fi
	CHILD_NUM="$1"
	if test "$2" = "--valgrind"; then
		USE_VALGRIND="true"
		shift 1
	elif test "$2" = "--gdb";then
		USE_GDB="true"
		shift 1
	elif test "$2" = "--wait";then
		check=$(test -f "$PATH_SHM" && echo -n "ready" || echo -n "not_ready")
		while test "$check" = "not_ready";do
			# log_info "shm file not ready. Waiting for a second.."
			sleep 1
			check=$(test -f "$PATH_SHM" && echo -n "ready" || echo -n "not_ready")
		done
		log_info "shm file ready."
		shift 1
	fi
	shift 1
	set -e				#DOC	=> e: exit on errors (check only )
	set -u				#DOC	=> u:track undefined variables
	set -E				#DOC	=> E:track functions
	shopt -s extglob	#DOC	=> shopt: allows shell to parse regex safely
	#set -x		#DEBUG	=> x: prints every command run
	#DOC	=> trap is like UNIX signal with argument handling
	#DOC	=> LINENO:last executed line in script
	#DOC	=> BASH_COMMAND: last command executed
	trap 'catch_error ${LINENO} "${BASH_COMMAND}"' ERR 
	#clear
	make
	for arg in "$@"
	do
		ARGS="$ARGS $arg"
	done
}

main()
{
	local	i
	local	pid

	script_setup "$@"
	log_info "args=$ARGS"
	log_info "selected $1 players. Use valgrind: $USE_VALGRIND"
	echo $CHILD_NUM
	if test "$USE_GDB" = "true"; then
		((--CHILD_NUM)) || test "1" = "1"
		shift 2
		log_success "Running gdb"
		"$PATH_SCRIPT" "$CHILD_NUM" "--wait" $@ &
		pid="$!"	#DOC =>	$! is last cmd pid
		gdb --args ./"$NAME" $ARGS
		kill -9 "$pid" || test "1" = "1"
		exit 0
	fi
	log_success "Running program"
	i=0
	while test "$i" -lt "$CHILD_NUM"; do
		if test "$USE_VALGRIND" = "true"; then
			valgrind --show-leak-kinds=all --leak-check=yes --suppressions="$PATH_SUPP" ./"$NAME" $ARGS &
		else
			./"$NAME" $ARGS &
		fi
		((++i))
		sleep 0.01
	done
}

main "$@"