/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:53:53 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:57:15 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/signals.h"

static int	grace_exit(int status, t_data *data)
{
	int	i;

	i = 0;
	while (data->envvars[i])
	{
		free(data->envvars[i]);
		i++;
	}
	free(data->envvars);
	free(data->user);
	clear_ast((t_ast_node *)data->ast_ref);
	clear_parser((t_parser *)data->parser_ref);
	exit(status);
}

static int	exec_from_path(char **args, t_data *data,
		t_redirect_args *redir_args)
{
	char	*path;

	path = get_path_of_cmd(args[0], data);
	if (!path)
	{
		ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
		ft_putendl_fd(args[0], STDERR_FILENO);
		free_splitted(args);
		restore_std(redir_args);
		return (grace_exit(127, data));
	}
	execve(path, args, data->envvars);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(args[0]);
	free(path);
	free_splitted(args);
	restore_std(redir_args);
	return (grace_exit(126, data));
}

static void	handle_pipe_paren(t_redirect_args *redir_args, t_ast_node *node,
		t_data *data)
{
	t_cmd_node	cmd;
	int			status;

	cmd = node->u_data.cmd;
	if (handle_redirects(node, redir_args, data) == FAILURE)
		grace_exit(1, data);
	status = handle_paren(cmd.args[0]->raw, data);
	restore_std(redir_args);
	grace_exit(status, data);
}

static void	exec_cmd_pipe(t_ast_node *node, t_data *data)
{
	t_cmd_node		cmd;
	char			**args;
	t_builtin_cmd	builtin;
	t_redirect_args	redir_args;
	int				status;

	if (node->type != NODE_CMD)
		exit(1);
	cmd = node->u_data.cmd;
	if (cmd.is_paren)
		handle_pipe_paren(&redir_args, node, data);
	args = convert_expandable(cmd.args);
	if (!args || !args[0])
		exit(1);
	if (handle_redirects(node, &redir_args, data) == FAILURE)
		grace_exit(1, data);
	builtin = get_builtin(args[0]);
	if (builtin)
	{
		status = exec_from_builtin(builtin, args, data);
		restore_std(&redir_args);
		grace_exit(status, data);
	}
	else
		exec_from_path(args, data, &redir_args);
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
	data->is_running = 0;
}
