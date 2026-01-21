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
#include <stdio.h>
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

static int	redirect_handler(t_redirect_value *redir, int type)
{
	int		flag;
	int		open_fd;

	flag = O_RDWR;
	if (type == STDOUT_FILENO)
		flag = O_WRONLY | O_CREAT | O_TRUNC;
	if (type == STDOUT_FILENO && ft_strncmp(redir->type, ">>\0", 3) == 0)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	if (ft_strncmp(redir->type, "<<\0", 3) == 0)
		open_fd = redir->tmp_fd_heredoc;
	else
		open_fd = open(redir->target->processed, flag, 0777);
	if (open_fd < 0)
	{
		perror(redir->target->processed);
		return (FAILURE);
	}
	if (dup2(open_fd, type) < 0)
	{
		close(open_fd);
		perror("dup2");
		return (FAILURE);
	}
	close(open_fd);
	return (SUCESS);
}

int	handle_failure(t_redirect_args *args)
{
	restore_std(args);
	return (FAILURE);
}

int	handle_redirects(t_ast_node *node, t_redirect_args *args)
{
	t_redirect_value	*stdin_file;
	t_redirect_value	*stdout_file;

	args->og_stdin = -1;
	args->og_stdout = -1;
	stdin_file = NULL;
	stdout_file = NULL;
	if (node->type == NODE_CMD)
	{
		stdin_file = find_redirect(&node->u_data.cmd, STDIN_FILENO);
		stdout_file = find_redirect(&node->u_data.cmd, STDOUT_FILENO);
	}
	if (stdin_file)
		args->og_stdin = dup(STDIN_FILENO);
	if (stdout_file)
		args->og_stdout = dup(STDOUT_FILENO);
	if (stdin_file && redirect_handler(stdin_file, STDIN_FILENO))
		return (handle_failure(args));
	if (stdout_file && redirect_handler(stdout_file, STDOUT_FILENO))
		return (handle_failure(args));
	return (SUCESS);
}

void	restore_std(t_redirect_args *args)
{
	if (args->og_stdin >= 0)
	{
		dup2(args->og_stdin, STDIN_FILENO);
		close(args->og_stdin);
	}
	if (args->og_stdout >= 0)
	{
		dup2(args->og_stdout, STDOUT_FILENO);
		close(args->og_stdout);
	}
}
