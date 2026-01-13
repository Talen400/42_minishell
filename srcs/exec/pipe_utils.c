/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:53:53 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/26 04:28:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/signals.h"

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
	t_redirect_args	redir_args;

	redir_args.dup_stdin = -1;
	redir_args.dup_stdout = -1;
	if (node->type != NODE_CMD)
		exit(1);
	cmd = node->u_data.cmd;
	args = convert_expandable(cmd.args);
	if (!args || !args[0])
		exit(1);
	if (handle_redirects(node, &redir_args) == FAILURE)
		return ;
	builtin = get_builtin(args[0]);
	if (builtin)
		exec_from_builtin(builtin, args, data);
	else
		exec_from_path(args, data);
	restore_std(&redir_args);
}

void	child_process(t_ast_node *node, t_data *data, t_pipe_args *args)
{
	restore_sigint();
	if (args->fd_in != STDIN_FILENO)
	{
		dup2(args->fd_in, STDIN_FILENO);
		close(args->fd_in);
	}
	if (!args->is_last)
	{
		close(args->fd[0]);
		dup2(args->fd[1], STDOUT_FILENO);
		close(args->fd[1]);
	}
	exec_cmd_pipe(node, data);
	exit(0);
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
