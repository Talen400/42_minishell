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

int	exec_pipe(t_ast_node *node, t_data *data)
{
	t_pipe_args	args;
	int			i;

	args.pipe_node = node->u_data.pipe;
	args.fd_in = STDIN_FILENO;
	i = 0;
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
			father_process(&args);
		i++;
	}
	i = 0;
	while (args.pipe_node.commands[i++])
		wait(&args.status);
	return (args.status);
}
