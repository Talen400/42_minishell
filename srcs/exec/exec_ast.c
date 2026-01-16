/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:16:34 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:28:19 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/expander.h"

int	get_exit_code(int exit_code)
{
	return (exit_code / 256);
}

int	check_if_should_exec(int type, int status)
{
	if (type == TOKEN_OR)
		return (status != 0);
	return (status == 0);
}

int	handle_paren(char *cmd, t_data *data)
{
	char	*str;
	int		status;
	size_t	len;
	void	*saved_ast;
	void	*saved_parser;

	saved_parser = data->parser_ref;
	saved_ast = data->ast_ref;
	data->parser_ref = NULL;
	data->ast_ref = NULL;
	str = ft_strdup(cmd);
	len = ft_strlen(str);
	status = 0;
	if (str[0] == '(')
		ft_memmove(str, str + 1, len - 1);
	if (str[len - 1] == ')')
		str[len - 2] = '\0';
	status = minishell(str, data);
	if (status >= 0 && status < 256)
		status = status * 256;
	free(str);
	data->parser_ref = saved_parser;
	data->ast_ref = saved_ast;
	return (status);
}

static int	handle_cmd(t_ast_node *root, t_data *data)
{
	int	status;

	if (root->u_data.cmd.is_paren)
		status = handle_paren(root->u_data.cmd.args[0]->raw, data);
	else
		status = exec_cmd(root, data);
	return (status);
}

int	exec_ast(t_ast_node *root, t_data *data, int status)
{
	int	should_exec;
	int	exit_code;

	if (!root || !data->is_running)
		return (status);
	if (root->type == NODE_LOGICAL)
	{
		expand_ast(root->u_data.logical.left, data);
		status = exec_ast(root->u_data.logical.left, data, status);
		exit_code = get_exit_code(status);
		should_exec = check_if_should_exec(root->u_data.logical.op,
				exit_code);
		expand_ast(root->u_data.logical.right, data);
		if (should_exec)
			status = exec_ast(root->u_data.logical.right, data, status);
		data->last_status = get_exit_code(status);
		return (status);
	}
	if (root->type == NODE_CMD)
		status = handle_cmd(root, data);
	if (root->type == NODE_PIPE)
		status = exec_pipe(root, data);
	data->last_status = get_exit_code(status);
	return (status);
}
