/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:39:27 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/11 22:36:35 by tlavared         ###   ########.fr       */
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

/*
 * A função wait() não retorna o status como um número
 * mas como um número com várias info. e tem que
 * fazer bitwise para capturar o status
 *
 * Felizmente, tem as macros WIFEXITED e WIFSIGNALED :>
 *
 * Pra isso, eu vou pegar o status do ultimo comando :>
 */

int	exec_pipe(t_ast_node *node, t_data *data)
{
	t_pipe_args	args;
	int			i;
	pid_t		last_pid;
	int			last_status;
	int			w_status;

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
		last_pid = args.pid;
		i++;
	}
	i = 0;
	while (args.pipe_node.commands[i++])
	{
		w_status = wait(&args.status);
		if (w_status == last_pid)
		{
			if (WIFEXITED(args.status))
				last_status = WEXITSTATUS(args.status);
			else if (WIFSIGNALED(args.status))
				last_status = 128 + WTERMSIG(args.status);
		}
	}
	data->last_status = last_status * 256;
	return (data->last_status);
}
