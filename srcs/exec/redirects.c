/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:02:40 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/26 23:04:06 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/exec.h"
#include <fcntl.h>
#include <unistd.h>

t_redirect_value	*find_redirect(t_cmd_node *cmd, int type)
{
	t_redirect_value	*res;

	res = NULL;
	if (!cmd->redirects[type])
		return (NULL);
	if (cmd->redirects[type]->og_fd == type)
		res = cmd->redirects[type];
	return (res);
}

static int	redirect_handler(t_redirect_value *redir,
						t_redirect_args *args, int type)
{
	int		flag;
	int		open_fd;

	flag = O_RDWR;
	if (type == STDOUT_FILENO)
		flag = O_WRONLY | O_CREAT | O_TRUNC;
	if (type == STDOUT_FILENO && ft_strncmp(redir->type, ">>\0", 3) == 0)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	if (ft_strncmp(redir->type, "<<\0", 3) == 0)
		open_fd = handle_heredoc(redir->target->processed);
	else
		open_fd = open(redir->target->processed, flag, 0777);
	if (open_fd < 0)
	{
		perror(redir->target->processed);
		restore_std(args);
		return (FAILURE);
	}
	if (type == STDIN_FILENO)
		args->dup_stdin = dup2(open_fd, type);
	if (type == STDOUT_FILENO)
		args->dup_stdout = dup2(open_fd, type);
	close(open_fd);
	return (SUCESS);
}

t_redirect_value	*find_last_pipex_cmd_stdout(t_ast_node *node)
{
	int			i;
	t_cmd_node	cmd;

	i = 0;
	while (node->u_data.pipe.commands[i])
	{
		if (node->u_data.pipe.commands[i + 1] == NULL)
			cmd = node->u_data.pipe.commands[i]->u_data.cmd;
		i++;
	}
	return (find_redirect(&cmd, STDOUT_FILENO));
}

int	handle_redirects(t_ast_node *node, t_redirect_args *args)
{
	t_redirect_value	*stdin_file;
	t_redirect_value	*stdout_file;

	args->dup_stdin = -1;
	args->dup_stdout = -1;
	args->og_stdin = dup(STDIN_FILENO);
	args->og_stdout = dup(STDOUT_FILENO);
	stdin_file = NULL;
	stdout_file = NULL;
	if (node->type == NODE_CMD)
	{
		stdin_file = find_redirect(&node->u_data.cmd, STDIN_FILENO);
		stdout_file = find_redirect(&node->u_data.cmd, STDOUT_FILENO);
	}
	if (stdin_file && redirect_handler(stdin_file, args, STDIN_FILENO))
		return (FAILURE);
	if (stdout_file && redirect_handler(stdout_file, args, STDOUT_FILENO))
		return (FAILURE);
	return (SUCESS);
}

void	restore_std(t_redirect_args *args)
{
	if (args->dup_stdin >= 0)
		close(args->dup_stdin);
	dup2(args->og_stdin, STDIN_FILENO);
	close(args->og_stdin);
	if (args->dup_stdout >= 0)
		close(args->dup_stdout);
	dup2(args->og_stdout, STDOUT_FILENO);
	close(args->og_stdout);
}
