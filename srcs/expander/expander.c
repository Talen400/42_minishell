/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:55:11 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/19 17:41:40 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"

/*
 *
 *
 * Here is experimental automato expanser
 *
 *
 */

void	expand_var(t_expandable_value *value, t_data *data)
{
	ft_is_expander(value, data);
}

void	expand_cmd(t_ast_node *node, t_data *data)
{
	int	i;

	if (node->type != NODE_CMD)
		return ;
	i = 0;
	while (node->u_data.cmd.args[i])
	{
		expand_var(node->u_data.cmd.args[i], data);
		i++;
	}
	i = 0;
	while (node->u_data.cmd.redirects[i])
	{
		expand_var(node->u_data.cmd.redirects[i]->target, data);
		i++;
	}
	expand_var(node->u_data.cmd.cmd, data);
}

void	expand_ast(t_ast_node *root, t_data *data)
{
	if (!root)
		return ;
	if (root->type == NODE_LOGICAL)
	{
		expand_ast(root->u_data.logical.left, data);
		expand_ast(root->u_data.logical.right, data);
	}
	if (root->type == NODE_CMD)
		expand_cmd(root, data);
}
