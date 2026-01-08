#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
MAGENTA='\033[0;35m'
NC='\033[0m'

MINISHELL="./minishell"

run_test="./minishell"

run_test() {
	local cmd="$1"
	
	echo "$cmd" | bash > out_bash 2> err_bash
	status_bash=$?

	echo "$cmd" | valgrind --leak-check=full \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				--quiet --log-file=valgrind_log.txt \
				$MINISHELL > out_mini 2> err_mini
	
	status_mini=$?

	mem_err=0
	[ $status_mini -eq 42 ] && mem_err=1

	diff out_bash out_mini > /dev/null
	diff_out=$?

	diff err_bash err_mini > /dev/null
	diff_err=$?

	if [ $status_bash -eq $status_mini ] && [ $diff_out -eq 0 ] && [ $diff_err -eq 0 ]; then
		echo -e "${GREEN}[OK]${NC} \"$cmd\""
	else
		echo -e "${RED}[KO]${NC} \"$cmd\""

		[ $mem_err -eq 1 ] && echo -e "	${MAGENTA}Memory Error/Leak detected!${NC}"
		# show the status
		if [ $status_bash -ne $status_mini ]; then
			echo -e "	${RED}Status Diff:${NC} Bash ($status_bash) vs Mini ($status_mini)"
		fi
		# Show the diff Output (STDOUT_FILENO)
		if [ $diff_out -ne 0 ]; then
			echo -e "	${RED}STDOUT Diff (-bash, +minishell):${NC}"
			diff -u out_bash out_mini | tail -n +3 | sed 's/^/		/'
		fi
		if [ $diff_err -ne 0 ]; then
			echo -e "	${RED}STDERR Diff (-bash, +minishell):${NC}"
			diff -u err_bash err_mini | tail -n +3 | sed 's/^/		/'
		fi
		#[ $diff_out -ne 0 ] && echo "       -> diff in output"
		#[ $status_bash -ne $status_mini ] && echo "      -> Status Bash: $status_bash | Mini: $status_mini "
	fi
}

# variaveis e concatenação

echo "Init tests..."
run_test "echo test"
run_test "echo 'test'"
run_test "echo \"test\""
run_test "echo \$USER"
run_test "echo \$USER\$USER"
run_test "echo \$USER \$USER"
run_test "echo \$USER_test"
run_test "echo \$USER123"
run_test "echo \$?"
run_test "echo \$?USER"
run_test "echo \$ USER"
run_test "echo \$"
run_test "echo test\$USER"
run_test "echo \$USER-test"
run_test "echo \$INVALID_VAR"
run_test "echo \$USER\$INVALID_VAR\$USER"
run_test "echo \$PWD"
run_test "echo \$SHLVL"
run_test "echo \$HOME"
run_test "echo \$USER\$PWD"
run_test "echo \$USER \$"
run_test "echo \$\$"
run_test "echo \$9"

# Aspas simples
run_test "echo '\$USER'"
run_test "echo '\$?'"
run_test "echo '\"\$USER\"'"
run_test "echo '\$USER \$PWD'"
run_test "echo '   \$USER   '"
run_test "echo ''"
run_test "echo ' '"
run_test "echo '\"\"'"
run_test "echo '\$(echo test)'"
run_test "echo 'text without expansion'"
run_test "echo '   '"
run_test "echo 'echo \$USER'"
run_test "echo '\$USER'test"
run_test "echo test'\$USER'"
run_test "echo '\$USER'\$USER"
run_test "echo \$USER'\$USER'"
run_test "echo ''''"
run_test "echo ' \" ' \" ' \" '"
run_test "echo '>>>>'"
run_test "echo '|||&&&'"

# Aspas duplas
run_test "echo \"\$USER\""
run_test "echo \"\$?\""
run_test "echo \"\$USER \$PWD\""
run_test "echo \"'\$USER'\""
run_test "echo \"   \$USER   \""
run_test "echo \"\""
run_test "echo \" \""
run_test "echo \"''\""
run_test "echo \"\$(echo test)\""
run_test "echo \"text with \$USER\""
run_test "echo \"\$USER\"test"
run_test "echo test\"\$USER\""
run_test "echo \"\$USER\"\$USER"
run_test "echo \$USER\"\$USER\""
run_test "echo \"\$USER   \$?\""
run_test "echo \"\"\"\""
run_test "echo \"   \""
run_test "echo \"\$(pwd)\""
run_test "echo \"Hello \$USER\""
run_test "echo \"\$USER \$INVALID_VAR\""

# Subshells
run_test "echo \$(echo hello)"
run_test "echo \$(echo \$USER)"
run_test "echo \$(echo \"\$USER\")"
run_test "echo \$(echo '\$USER')"
run_test "echo \$(echo \$(echo nest))"
run_test "echo \"\$(echo hello)\""
run_test "echo '\$(echo hello)'"
run_test "echo \$(pwd)"
run_test "echo \$(ls | grep e)"
run_test "echo \$(echo test | cat -e)"
run_test "echo \$(echo \$?)"
run_test "echo \$(echo \"\")"
run_test "echo \$(echo ' ')"
run_test "echo \$(echo \$USER)\$USER"
run_test "echo \$USER\$(echo \$USER)"
run_test "echo \"The user is \$(echo \$USER)\""
run_test "echo \$(echo -n test)"
run_test "echo \$(echo \$USER | tr a-z A-Z)"
run_test "echo \$(echo \$(pwd))"
run_test "echo \$(echo \$(echo \$(echo deep)))"

# Mistakes
run_test "echo \"\$USER\" '\$USER' \$(echo \$USER)"
run_test "echo \"'\$USER'\" '\$(echo \$USER)'"
run_test "echo \"\"''\"\$(echo)\""
run_test "echo \$USER\"\$USER\"'\$USER'\$(echo \$USER)"
run_test "echo \"\$USER \$(echo \"\$USER\") \$USER\""
run_test "echo '\$USER \$(echo \"\$USER\") \$USER'"
run_test "echo \$(echo \"\$USER\")\"\$USER\"'\$USER'"
run_test "echo \$?\"\$?\"'\$?'\$(echo \$?)"
run_test "echo \" \$(echo \" \$(echo hi) \") \")"
run_test "echo \"\"\"\"''''"
run_test "echo \$USER\$USER\"\$USER\"'\$USER'"
run_test "echo \$(echo \"\$USER\"'\$USER'\"\$USER\")"
run_test "echo \"\$(echo \"\$(echo \"\$(echo nested)\")\")\""
run_test "echo \$INVALID_VAR\"\$INVALID_VAR\"'\$INVALID_VAR'"
run_test "echo \"\$USER \" \$USER ' \$USER '"
run_test "echo \$(echo \$USER)\$?"
run_test "echo \"\$USER\"\$?"
run_test "echo '\$USER'\$?"
run_test "echo \$(echo \"\$USER\" | cat)"
run_test "echo \"FINISH TEST\""

rm -f out_bash out_mini err_bash err_mini valgrind_log.txt 
