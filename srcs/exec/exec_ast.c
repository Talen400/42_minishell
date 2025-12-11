/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:16:34 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/11 13:17:52 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_ast(t_ast_node *root, t_data *data)
{
	if (!root || !data->is_running)
		return ;
	if (root->type == NODE_CMD)
		exec_cmd(root, data);
	if (root->type == NODE_PIPE)
		exec_pipe(root, data);
}
