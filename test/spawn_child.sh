#!/bin/bash

PATH_SUPP="test/valgrind.supp"
NAME="lem-ipc"
CHILD_MAX="30"

log_error()		{ echo -e "\033[1;31m[ERROR]\033[0m $1"; }

if test "$1" = "" || test "$1" -lt "0" || test "$1" -gt "$CHILD_MAX"; then
	log_error "Usage: $0 [number between 0 and $CHILD_MAX] [OPTIONAL: --valgrind]"
	exit 1
fi

i=0
while test "$i" -lt "$1"; do
	if test "$2" = "--valgrind"; then
		valgrind --show-leak-kinds=all --leak-check=yes --suppressions="$PATH_SUPP" ./"$NAME" &
	else
		./"$NAME" &
	fi
	((++i))
done