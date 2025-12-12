/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:16:34 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 14:39:38 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	check_if_should_exec(int type, int status)
{
	if (type == TOKEN_OR)
		return (status);
	return (!status);
}

int	exec_ast(t_ast_node *root, t_data *data)
{
	int	should_exec_right;
	int	status;

	if (!root || !data->is_running)
		return (1);
	if (root->type == NODE_CMD)
		return (exec_cmd(root, data));
	if (root->type == NODE_PIPE)
		return (exec_pipe(root, data));
	if (root->type == NODE_LOGICAL)
	{
		status = exec_ast(root->u_data.logical.left, data);
		should_exec_right = check_if_should_exec(root->u_data.logical.op, status);
		if (should_exec_right)
			status = exec_ast(root->u_data.logical.right, data);
		return (status);
	}
	return (0);
}
