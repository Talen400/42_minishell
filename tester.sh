#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

MINISHELL="./minishell"

run_test="./minishell"

run_test() {
	local cmd="$1"
	
	echo "$cmd" | bash > out_bash 2> err_bash
	status_bash=$?

	echo "$cmd" | $MINISHELL > out_mini 2> err_mini
	status_mini=$?

	diff out_bash out_mini > /dev/null
	diff_out=$?

	if [ $status_bash -eq $status_mini ] && [ $diff_out -eq 0 ]; then
		echo -e "${GREEN}[OK]${NC} \"$cmd\""
	else
		echo -e "${RED}[KO]${NC} \"$cmd\""
		# show the status
		if [ $status_bash -ne $status_mini ]; then
			echo -e "	${RED}Status Diff:${NC} Bash ($status_bash) vs Mini ($status_mini)"
		fi
		# Show the diff Output (STDOUT_FILENO)
		if [ $diff_out -ne 0 ]; then
			echo -e "	${RED}Output Diff (-bash, +minishell):${NC}"
			diff -u out_bash out_mini | tail -n +3 | sed 's/^/		/'
		fi
		#[ $diff_out -ne 0 ] && echo "       -> diff in output"
		#[ $status_bash -ne $status_mini ] && echo "      -> Status Bash: $status_bash | Mini: $status_mini "
	fi
}

echo "Init tests..."
run_test "echo test"

rm -f out_bash out_mini err_bash err_mini
