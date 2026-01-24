/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:32:37 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/24 02:04:24 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"

void	expand_var(t_expandable_value *value, t_data *data)
{
	char	*tmp;

	if (is_expander(value, data))
	{
		if (value->type == WILDCARD)
		{
			tmp = value->processed;
			value->processed = wildcard(tmp);
			free(tmp);
		}
	}
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
	if (node->u_data.cmd.redirects[0])
		expand_var(node->u_data.cmd.redirects[0]->target, data);
	if (node->u_data.cmd.redirects[1])
		expand_var(node->u_data.cmd.redirects[1]->target, data);
	expand_var(node->u_data.cmd.cmd, data);
}

void	expand_ast(t_ast_node *root, t_data *data)
{
	int	i;

	if (!root)
		return ;
	if (root->type == NODE_CMD)
		expand_cmd(root, data);
	if (root->type == NODE_PIPE)
	{
		i = 0;
		while (root->u_data.pipe.commands[i])
		{
			expand_cmd(root->u_data.pipe.commands[i], data);
			i++;
		}
	}
}
