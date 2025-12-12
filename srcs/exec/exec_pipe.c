/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:39:27 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 13:59:34 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"
#include <unistd.h>

static int	exec_from_path(char **args, t_data *data)
{
	char	*path;

	path = get_path_of_cmd(args[0], data);
	if (!path)
	{
		ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
		ft_putendl_fd(args[0], STDERR_FILENO);
		free_splitted(args);
		exit(127);
	}
	execve(path, args, data->envvars);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(args[0]);
	free(path);
	free_splitted(args);
	exit(126);
}

static void	exec_cmd_pipe(t_ast_node *node, t_data *data)
{
	t_cmd_node		cmd;
	char			**args;
	t_builtin_cmd	builtin;

	if (node->type != NODE_CMD)
		exit(1);
	cmd = node->u_data.cmd;
	args = convert_expandable(cmd.args);
	if (!args || !args[0])
		exit(1);
	builtin = get_builtin(args[0]);
	if (builtin)
		exec_from_builtin(builtin, args, data);
	else
		exec_from_path(args, data);
}

static void	child_process(t_ast_node *node, t_data *data, int *fd_in,
		int *fd_out, int is_last)
{
	if (*fd_in != STDIN_FILENO)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if (!is_last)
	{
		close(fd_out[0]);
		dup2(fd_out[1], STDOUT_FILENO);
		close(fd_out[1]);
	}
	exec_cmd_pipe(node, data);
	exit(1);
}

static void	father_process(int *fd_in, int *fd_out, int is_last)
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (!is_last)
	{
		close(fd_out[1]);
		*fd_in = fd_out[0];
	}
}

int	exec_pipe(t_ast_node *node, t_data *data)
{
	t_pipe_node	pipe_node;
	int			fd[2];
	int			fd_in;
	int			i;
	pid_t		pid;
	int			status;
	int			is_last;

	pipe_node = node->u_data.pipe;
	fd_in = STDIN_FILENO;
	i = 0;
	while (pipe_node.commands[i])
	{
		is_last = (pipe_node.commands[i + 1] == NULL);
		if (!is_last && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			if (!is_last)
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}
		if (pid == 0)
			child_process(pipe_node.commands[i], data, &fd_in, fd, is_last);
		else
			father_process(&fd_in, fd, is_last);
		i++;
	}
	i = 0;
	while (pipe_node.commands[i++])
		wait(&status);
	return (status);
}
