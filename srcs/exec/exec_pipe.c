/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:39:27 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:55:41 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	handle_fork_error(t_pipe_args *args)
{
	perror("fork");
	if (!args->is_last)
	{
		close(args->fd[0]);
		close(args->fd[1]);
	}
	return (1);
}

static int	wait_pids(int last_pid)
{
	pid_t	wpid;
	int		tmp_status;
	int		status;

	status = 0;
	while (1)
	{
		wpid = wait(&tmp_status);
		if (wpid == -1)
			break ;
		if (wpid == last_pid)
			status = tmp_status;
	}
	return (status);
}

void	father_process(t_pipe_args *args)
{
	if (args->fd_in != STDIN_FILENO)
		close(args->fd_in);
	if (!args->is_last)
	{
		close(args->fd[1]);
		args->fd_in = args->fd[0];
	}
}

static void	init_args(t_pipe_args *args)
{
	args->fd_in = STDIN_FILENO;
	args->i = 0;
	args->last_pid = -1;
}

int	exec_pipe(t_ast_node *node, t_data *data)
{
	t_pipe_args	args;

	args.pipe_node = node->u_data.pipe;
	init_args(&args);
	while (args.pipe_node.commands[args.i])
	{
		args.is_last = (args.pipe_node.commands[args.i + 1] == NULL);
		if (!args.is_last && pipe(args.fd) == -1)
			return (perror("pipe"), 1);
		args.pid = fork();
		if (args.pid == -1)
			return (handle_fork_error(&args));
		if (args.pid == 0)
			child_process(args.pipe_node.commands[args.i], data, &args);
		else
		{
			if (args.is_last)
				args.last_pid = args.pid;
			father_process(&args);
		}
		args.last_pid = args.pid;
		args.i++;
	}
	return (wait_pids(args.last_pid));
}
