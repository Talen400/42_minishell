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

	echo "$cmd" | valgrind --leak-check=full --error-exitcode=42 --quiet --log-file=valgrind_log.txt $MINISHELL > out_mini 2> err_mini
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
    # --- VARs ---
    "echo test"
    "echo 'test'"
    "echo \"test\""
	"e\'c\'h\'o\' test"
    "echo \$USER"
    "echo \$USER\$USER"
    "echo \$USER \$USER"
    "echo \$USER_test"
    "echo \$USER123"
    "echo \$?"
    "echo \$?USER"
    "echo \$ USER"
    "echo \$"
    "echo test\$USER"
    "echo \$USER-test"
    "echo \$INVALID_VAR"
    "echo \$USER\$INVALID_VAR\$USER"
    "echo \$PWD"
    "echo \$SHLVL"
    "echo \$HOME"
    "echo \$USER\$PWD"
    "echo \$USER \$"
    "echo \$\$"
    "echo \$9"

    # --- QUOTE ---
    "echo '\$USER'"
    "echo '\$?'"
    "echo '\"\$USER\"'"
    "echo '\$USER \$PWD'"
    "echo '   \$USER   '"
    "echo ''"
    "echo ' '"
    "echo '\"\"'"
    "echo '\$(echo test)'"
    "echo 'text without expansion'"
    "echo '   '"
    "echo 'echo \$USER'"
    "echo '\$USER'test"
    "echo test'\$USER'"
    "echo '\$USER'\$USER"
    "echo \$USER'\$USER'"
    "echo ''''"
    "echo ' \" ' \" ' \" '"
    "echo '>>>>'"
    "echo '|||&&&'"

    # --- DOUBLE QUOTE---
    "echo \"\$USER\""
    "echo \"\$?\""
    "echo \"\$USER \$PWD\""
    "echo \"'\$USER'\""
    "echo \"   \$USER   \""
    "echo \"\""
    "echo \" \""
    "echo \"''\""
    "echo \"\$(echo test)\""
    "echo \"text with \$USER\""
    "echo \"\$USER\"test"
    "echo test\"\$USER\""
    "echo \"\$USER\"\$USER"
    "echo \$USER\"\$USER\""
    "echo \"\$USER   \$?\""
    "echo \"\"\"\""
    "echo \"   \""
    "echo \"\$(pwd)\""
    "echo \"Hello \$USER\""
    "echo \"\$USER \$INVALID_VAR\""

    # --- SUBSHELLS (BONUS) ---
    "echo \$(echo hello)"
    "echo \$(echo \$USER)"
    "echo \$(echo \"\$USER\")"
    "echo \$(echo '\$USER')"
    "echo \$(echo \$(echo nest))"
    "echo \"\$(echo hello)\""
    "echo '\$(echo hello)'"
    "echo \$(pwd)"
    "echo \$(ls | grep e)"
    "echo \$(echo test | cat -e)"
    "echo \$(echo \$?)"
    "echo \$(echo \"\")"
    "echo \$(echo ' ')"
    "echo \$(echo \$USER)\$USER"
    "echo \$USER\$(echo \$USER)"
    "echo \"The user is \$(echo \$USER)\""
    "echo \$(echo -n test)"
    "echo \$(echo \$USER | tr a-z A-Z)"
    "echo \$(echo \$(pwd))"
    "echo \$(echo \$(echo \$(echo deep)))"

    # --- Mistakes ---
    "echo \"\$USER\" '\$USER' \$(echo \$USER)"
    "echo \"'\$USER'\" '\$(echo \$USER)'"
    "echo \"\"''\"\$(echo)\""
    "echo \$USER\"\$USER\"'\$USER'\$(echo \$USER)"
    "echo \"\$USER \$(echo \"\$USER\") \$USER\""
    "echo '\$USER \$(echo \"\$USER\") \$USER'"
    "echo \$(echo \"\$USER\")\"\$USER\"'\$USER'"
    "echo \$?\"\$?\"'\$?'\$(echo \$?)"
    "echo \" \$(echo \" \$(echo hi) \") \")"
    "echo \"\"\"\"''''"
    "echo \$USER\$USER\"\$USER\"'\$USER'"
    "echo \$(echo \"\$USER\"'\$USER'\"\$USER\")"
    "echo \"\$(echo \"\$(echo \"\$(echo nested)\")\")\""
    "echo \$INVALID_VAR\"\$INVALID_VAR\"'\$INVALID_VAR'"
    "echo \"\$USER \" \$USER ' \$USER '"
    "echo \$(echo \$USER)\$?"
    "echo \"\$USER\"\$?"
    "echo '\$USER'\$?"
    "echo \$(echo \"\$USER\" | cat)"

    # --- Logic Operator (BONUS) ---
    "true && echo 'deve imprimir'"
    "false && echo 'NAO deve imprimir'"
    "true || echo 'NAO deve imprimir'"
    "false || echo 'deve imprimir'"
    "echo hello && echo world"
    "ls /non_existent && echo 'erro'"
    "ls /non_existent || echo 'imprime depois do erro'"
    "true && true && echo 'ok'"
    "true && false && echo 'nao'"
    "false || false || echo 'ok'"
    "true && false || echo 'imprime porque o anterior falhou'"
    "false || true && echo 'imprime porque o anterior deu certo'"
    "echo a && echo b && echo c || echo d"
    "ls / && false || echo 'recuperou do erro'"

    # --- Precedence and parenthesis ---
    "(echo hello)"
    "(true || false) && echo 'ok'"
    "false && (echo 'nao') || echo 'sim'"
    "(echo a && echo b) || (echo c && echo d)"
    "echo a && (false || echo b)"
    "(ls / && (echo interno && false)) || echo 'externo'"
    "((echo nested))"
    "(echo a && (echo b && (echo c)))"
    "echo \$USER && echo \$PWD"
    "ls | grep a && echo 'encontrou a'"
    "ls | grep 'nao_existe' || echo 'nao encontrou'"
    "(echo \$USER && false) || echo \$HOME"

    # --- Errors syntax ---
    "&& echo erro"
    "echo erro &&"
    "echo a ||"
    "echo a || && echo b"
    "(echo a && echo b"
    "echo a && echo b)"
    "() && echo a"
    "echo a && ( )"
    "&&&"
    "|||"

    # ---  EXTRAS ---
    "\$PWD"
    "\$EMPTY"
    "\$EMPTY echo hi"
    "./test_files/invalid_permission"
    "./missing.out"
    "missing.out"
    "\"aaa\""
    "test_files"
    "./test_files"
    "/test_files"
    "minishell.h"
    "\$"
    "\$?"
    "README.md"
    "ls"
    "ls -l"
    "ls -l -a"
    "echo &"
    "echo \'"
    "echo \""
    "echo \'\'"
    "echo \"\""
    "echo \"\'\""
    "echo \'\"\'"
    "echo \'&\'"
    "ls | cat"
    "ls -l | cat -e"
    "ls -l | grep a | cat -e"
    "echo 1 && echo 2"
    "echo 1 && echo 2 && echo 3"
    "ls -l | cat -e && echo deu bom"
    "ls -l | cat -e && echo deu bom && echo eh isso"
    "ls -l | cat -e && echo deu bom || echo deu ruim agora"
    "ls -l | cat -e || echo deu ruim"
    "< infile"
    "< infile > ./outfiles/outfile"
    "< infile cat > ./outfiles/outfile -e"
    "/bin/cat < todo > ./outfiles/out > ./outfiles/out1 > ./outfiles/out2 < todo"
    "< infile cat > outfile -e && ls < infile > -a outfile -l"
    "< infile cat | grep a > out"
    "> ./outfiles/out | /bin/ls"
    "/bin/ls | < infile"
    "/bin/ls | /bin/grep o > ./outfiles/out | /bin/ps"
    "/bin/ps > ./outfiles/out | /bin/ls | /bin/grep o"
    "< infile cat > outfile | < infile grep a"
    "()"
    "(ls)"
    "(ls -l)"
    "((ls -l))"
    "(ls) -l"
    "(ls) -l -a"
    "-l (ls)"
    "< infile (/bin/cat > ./outfiles/out -e > ./outfiles/out2 | /bin/ps)"
    "( /bin/ls < infile ) < infile | < infile /bin/cat -e && ( ( ( < infile /bin/cat -e ) ) )"
    "echo hi | cat -e > ./outfiles/outfile1 && < infile1 | cat -e && < infile2 cat"
    "dsfasdf || echo hello | cat -e && echo bye || echo kitty"
    "echo oi && ech oi2 | echo oi3 | echo oi4 || echo oi5"
    "ech && echo oi || echo hey"
    "echo hello | cat -e && ls | wc -l"
    "cat > ."
    "cat > ./outfiles/"
    "cat > /usr/local/bin"
    "echo $\"\" USER"
    "echo \$ USER"
    "echo \"        \$USER   \""
    "echo \$"
    "echo \$\$"
    "export carol=55 && echo \$carol"
    "export carol=55 && echo \"\$carol\""
    "export carol=55 && echo '\$carol'"
    "export carol=55 && echo \$carolbia\$"
    "export carol=55 && echo \$carol?bia\$ hi"
    "export carol=55 && echo \$carolbia\$ | cat -e > outfile3 && echo bye"
    "echo \$adfasfsd"
    "\$adfasfsd"
    "export var=variable && export \$var=carol && export | grep \$var"
    "export var=oi | echo hey"
    "unset \"\""
    "export carol=55 && \$USER\$carol"
    "\"\$USER\""
    "'\$USER'"
    "echo hi | (echo hello | cat -e)"
    "(export var=carol) && export | grep var="
    "(ech hi || (echo carol > ./outfiles/outfile1 && echo bia)) | cat -e && echo bye"
    "((echo hi | cat -e) | cat -e)"
    "echo − -\$\$"
	"oi | oi"
	"oi |"
	"{"
	"}"
	# verificar ctrl-c
	# signal com python com ctrl-\
	"ls < oi > a < banana" # arquivo nao existente
	"echo \$123"
)

for cmd in "${commands[@]}"; do
    run_test "$cmd"
done

rm -f out_bash out_mini err_bash err_mini valgrind_log.txt 
