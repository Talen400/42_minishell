/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:39:27 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/18 16:26:46 by fbenini-         ###   ########.fr       */
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

static int wait_pids(int last_pid)
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

int	exec_pipe(t_ast_node *node, t_data *data)
{
	t_pipe_args	args;
	int			i;
	pid_t		last_pid;

	args.pipe_node = node->u_data.pipe;
	args.fd_in = STDIN_FILENO;
	i = 0;
	last_pid = -1;
	while (args.pipe_node.commands[i])
	{
		args.is_last = (args.pipe_node.commands[i + 1] == NULL);
		if (!args.is_last && pipe(args.fd) == -1)
			return (perror("pipe"), 1);
		args.pid = fork();
		if (args.pid == -1)
			return (handle_fork_error(&args));
		if (args.pid == 0)
			child_process(args.pipe_node.commands[i], data, &args);
		else
		{
			if (args.is_last)
				last_pid = args.pid;
			father_process(&args);
		}
		i++;
	}
	return (wait_pids(last_pid));
}
