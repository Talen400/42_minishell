/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:58:35 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 15:02:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

int	exec_logical(t_ast_node *node, t_data *data, int iter)
{
	if (node->type == PIPE)
		return (exec_pipe(node, data));
	exec_ast(node->u_data.logical.left, data);
	return (0);
}
