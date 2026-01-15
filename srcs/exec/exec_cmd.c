/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:00:35 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:13:12 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/exec.h"
#include "../../includes/signals.h"
#include <time.h>
#include <errno.h>

static void	handle_child(char **args, t_data *data, char *path)
{
	int	status;

	restore_sigint();
	status = execve(path, args, data->envvars);
	if (status == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
			exit(126);
		}
		if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
			exit(127);
		}
	}
	free(path);
	free_splitted(args);
	exit(status);
}

static int	handle_no_args(char **args, int status)
{
	free_splitted(args);
	return (status);
}

static int	exec_from_path(char **args, t_data *data)
{
	char	*path;
	int		status;
	pid_t	pid;

	status = 0;
	if (!args || !args[0])
		return (handle_no_args(args, status));
	path = get_path_of_cmd(args[0], data);
	if (!path)
	{
		ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
		ft_putendl_fd(args[0], STDERR_FILENO);
		free_splitted(args);
		return (127 * 256);
	}
	pid = fork();
	if (pid == 0)
		handle_child(args, data, path);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork failed");
	free(path);
	free_splitted(args);
	return (status);
}

int	exec_cmd(t_ast_node *node, t_data *data)
{
	t_cmd_node		cmd;
	char			**args;
	t_builtin_cmd	builtin;
	int				status;
	t_redirect_args	redir_args;

	if (node->type != NODE_CMD)
		return (1);
	cmd = node->u_data.cmd;
	args = convert_expandable(cmd.args);	
	if (handle_redirects(node, &redir_args) == FAILURE)
	{
		free_splitted(args);
		return (1 * 256);
	}
	builtin = get_builtin(args[0]);
	if (builtin)
		status = exec_from_builtin(builtin, args, data);
	else
		status = exec_from_path(args, data);
	restore_std(&redir_args);
	return (status);
}
