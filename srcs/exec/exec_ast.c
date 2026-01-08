/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:16:34 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/18 18:33:12 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

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

int	exec_ast(t_ast_node *root, t_data *data, int status)
{
	int	should_exec;
	int	exit_code;

	if (!root || !data->is_running)
		return (status);
	if (root->type == NODE_LOGICAL)
	{
		status = exec_ast(root->u_data.logical.left, data, status);
		exit_code = get_exit_code(status);
		should_exec = check_if_should_exec(root->u_data.logical.op,
				exit_code);
		if (should_exec)
			status = exec_ast(root->u_data.logical.right, data, status);
		data->last_status = get_exit_code(status);
		return (status);
	}
	if (root->type == NODE_CMD)
		status = exec_cmd(root, data);
	if (root->type == NODE_PIPE)
		status = exec_pipe(root, data);
	data->last_status = get_exit_code(status);
	return (status);
}
