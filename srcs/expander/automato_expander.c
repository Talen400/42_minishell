/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:10:39 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/22 02:06:21 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/*
 * TABLE DRIVE :
 *
 * ======================================
 *
 * states
 * 0: INIT
 * 1: D_QUOTE
 * 2: S_QUOTE
 * 3: subshell
 *
 *		 		LET	"	'	$	(	)	*	\0
 * state 0	=	0	1	2	0	0	0	0	0
 * state 1	=	1	0	1	3	1	1	1	0
 * state 2	=	2	2	0	2	2	2	2	0
 * state 2	=	3	3	3	3	3	0	3	0
 */

static int	(*get_table_expander(void))[NUM_TYPE_EXPANDER]
{
	static int	table[NUM_STATE_EXPANDER][NUM_TYPE_EXPANDER] = {
	{0, 1, 2, 0, 0, 0, 0, 0},
	{1, 0, 1, 1, 1, 1, 1, 0},
	{2, 2, 0, 2, 2, 2, 2, 0},
	{3, 3, 3, 3, 3, 0, 3, 0}
	};

	return (table);
}

void	check_state(t_automato_expander *aut)
{
	aut->prev_state = aut->state;
	aut->state = get_state_expander(aut, aut->word[aut->i]);
}

char	*extract_subshell(t_automato_expander *aut)
{
	int		start;
	int		len;
	int		depth;
	char	*cmd;

	aut->i += 2;
	start = aut->i;
	len = 0;
	depth = 1;
	while (aut->word[aut->i] && depth > 0)
	{
		if (aut->word[aut->i] == '(')
			depth++;
		else if (aut->word[aut->i] == ')')
			depth--;
		if (depth > 0)
		{
			len++;
			aut->i++;
		}
	}
	if (depth != 0)
		return (ft_strdup(""));
	aut->i++;
	cmd = ft_substr(aut->word, start, len);
	return (cmd);
}

char	*execute_subshell(char *cmd, t_data *data)
{
	int		fds[2];
	pid_t	pid;
	int		status;
	char	*result;
	char	buffer[4096];
	int		nbytes;
	int		len;

	if (pipe(fds) == -1)
		return (ft_strdup(""));
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		status = minishell(cmd, data);
		exit(status);
	}
	close(fds[1]);
	result = ft_strdup("");
	while ((nbytes = read(fds[0], buffer, 4095)) > 0)
	{
		buffer[nbytes] = '\0';
		result = join_free(result, ft_strdup(buffer));
	}
	close(fds[0]);
	waitpid(pid, &status, 0);
	len = ft_strlen(result);
	dprintf(2, "DEBUG: subshell raw output: [%s] (len=%zu)\n", result, ft_strlen(result));
	while (len > 0 && result[len - 1] == '\n')
	{
		result[len - 1] = '\0';
		len--;
	}
	dprintf(2, "DEBUG: subshell final result: [%s] (len=%zu)\n", result, ft_strlen(result));
	return (result);
}

/*
 * echo test'test'"test""$USER"'$USER'"$(echo $USER)" 
 */

void	automato_expander(t_expandable_value *value, t_data *data,
		t_automato_expander*aut)
{
	char	*subshell_cmd;

	while (aut->word[aut->i])
	{
		check_state(aut);
	//	ft_printf("[%d] prev: %d, state: %d, str: %c \n",
	//		aut->i, aut->prev_state, aut->state, aut->word[aut->i]);
		if ((aut->word[aut->i] == '\'' && (aut->state == 2
					|| aut->prev_state == 2))
			|| (aut->word[aut->i] == '\"' && (aut->state == 1
					|| aut->prev_state == 1)))
		{
			aut->i++;
			continue ;
		}
		if (aut->word[aut->i + 1] && aut->word[aut->i] == '$'
			&& aut->word[aut->i + 1] == '(' && aut->state != 2)
		{
			subshell_cmd = extract_subshell(aut);
			aut->tmp = execute_subshell(subshell_cmd, data);
			value->processed = join_free(value->processed, aut->tmp);
			continue ;
		}
		if (aut->word[aut->i] == '$' && aut->state != 2)
		{
			aut->tmp = handle_dollar(aut, data);
			value->processed = join_free(value->processed, aut->tmp);
			continue ;
		}
		value->processed = append_char(value->processed, aut->word[aut->i]);
		aut->i++;
	}
}

int	is_expander(t_expandable_value *value, t_data *data)
{
	t_automato_expander	aut;

	ft_memset(&aut, 0, sizeof(t_automato_expander));
	aut.word = value->raw;
	value->processed = ft_strdup("");
	aut.table = get_table_expander();
	//ft_printf("\n maquina de estado da expansão! Raw: %s \n", value->raw);
	automato_expander(value, data, &aut);
	if (aut.word[aut.i] == '\0')
		return (TRUE);
	return (FALSE);
}
