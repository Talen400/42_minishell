/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:34:59 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/19 19:33:02 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/exec.h"

static int	find_subshell_len(t_automato_expander *aut)
{
	int	depth;
	int	len;

	depth = 1;
	len = 0;
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
		return (-1);
	return (len);
}

char	*extract_subshell(t_automato_expander *aut)
{
	int		start;
	int		len;
	char	*cmd;

	aut->i++;
	start = aut->i;
	len = find_subshell_len(aut);
	if (len < 0)
		return (ft_strdup(""));
	aut->i++;
	cmd = ft_substr(aut->word, start, len);
	return (cmd);
}

static void	run_subshell_child(char *cmd, t_data *data, int fd_out)
{
	int	status;

	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	status = minishell(cmd, data);
	exit(status);
}

static char	*read_subshell_out(int fd_in)
{
	char	*result;
	char	buffer[4096];
	int		nbytes;
	int		len;

	result = ft_strdup("");
	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd_in, buffer, 4095);
		if (nbytes == -1)
			break ;
		buffer[nbytes] = '\0';
		result = join_free(result, ft_strdup(buffer));
	}
	len = ft_strlen(result);
	while (len > 0 && result[len - 1] == '\n')
	{
		result[len - 1] = '\0';
		len--;
	}
	return (result);
}

char	*execute_subshell(char *cmd, t_data *data)
{
	int		fds[2];
	pid_t	pid;
	int		status;
	char	*result;

	if (pipe(fds) == -1)
		return (ft_strdup(""));
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		run_subshell_child(cmd, data, fds[1]);
	}
	close(fds[1]);
	waitpid(pid, &status, 0);
	result = read_subshell_out(fds[0]);
	close(fds[0]);
	return (result);
}
