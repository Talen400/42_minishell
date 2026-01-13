#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
MAGENTA='\033[0;35m'
NC='\033[0m'

MINISHELL="./minishell"

run_test="./minishell"

run_test() {
	local cmd="$1"
	
	echo "$cmd" | bash > out_bash 2> /dev/null
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

	if [ $status_bash -eq $status_mini ] && [ $diff_out -eq 0 ]; then
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
		#[ $diff_out -ne 0 ] && echo "       -> diff in output"
		#[ $status_bash -ne $status_mini ] && echo "      -> Status Bash: $status_bash | Mini: $status_mini "
	fi
}

#!/bin/bash

# Array com todos os casos de teste fornecidos
commands=(
	"echo \"exit_code ->\$? user ->\$USER home -> \$HOME"
	"export A-"
	"export HELLO-=123"
	"export ="
	"export 123"
	"cd \$PDW hi"
	"exit 123"
	"exit 298"
	"exit +100"
	"exit \"+100\""
	"exit +\"100\""
	"exit -100"
	"exit \"-100\""
	"exit -\"100\""
	"exit hello"
	"exit 42 world"
	"cat ./test_files/infile_big | grep oi"
	"cat <\"1\"\"2\"\"3\"\"4\"\"5\""
	"echo <\"./test_files/infile\" <missing <\"./test_files/infile\""
	"ls >./outfiles/outfile01 >./outfiles/outfile02"
	"ls >./outfiles/outfile01 >./test_files/invalid_permission"
	"ls >\"./outfiles/outfile01\" >./test_files/invalid_permission >\"./outfiles/outfile02\""
	"ls >./test_files/invalid_permission >\"./outfiles/outfile01\" >./test_files/invalid_permission"
	"echo hi >./outfiles/outfile01 | echo bye"
	"echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye"
	"echo hi | echo >./outfiles/outfile01 bye"
	"echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02"
	"echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02"
	"echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye"
	"echo hi >./test_files/invalid_permission | echo bye"
	"echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye"
	"echo hi | echo bye >./test_files/invalid_permission"
	"echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission"
	"echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01"
	"cat <\"./test_files/infile\" >./test_files/invalid_permission"
	"cat >./test_files/invalid_permission <\"./test_files/infile\""
	"cat <missing >./outfiles/outfile01"
	"cat >./outfiles/outfile01 <missing"
	"cat <missing >./test_files/invalid_permission"
	"cat >./test_files/invalid_permission <missing"
	"cat >./outfiles/outfile01 <missing >./test_files/invalid_permission"
	"ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02"
	"ls >>./outfiles/outfile01 >>./outfiles/outfile02"
	"ls >>./test_files/invalid_permission"
	"ls >>./test_files/invalid_permission >>./outfiles/outfile01"
	"ls >>./outfiles/outfile01 >>./test_files/invalid_permission"
	"ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02"
	"ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02"
	"ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing"
	"echo hi >>./outfiles/outfile01 | echo bye"
	"echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye"
	"echo hi | echo >>./outfiles/outfile01 bye"
	"echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02"
	"echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02"
	"echo hi >>./test_files/invalid_permission | echo bye"
	"echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye"
	"echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission"
	"cat <minishell.h>./outfiles/outfile"
	"cat <minishell.h|ls"
	"< infile"
	// EXTRAS
	""
	"\$PWD"
	"\$EMPTY"
	"\$EMPTY echo hi"
)

for cmd in "${commands[@]}"; do
    run_test "$cmd"
done

rm -f out_bash out_mini err_bash err_mini valgrind_log.txt 
