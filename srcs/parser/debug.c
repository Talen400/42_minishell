/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:39:03 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/09 16:35:23 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	print_cmd_node(t_ast_node *node, int indent)
{
	size_t	i;
	int		j;

	j = 0;
	while (j++ < indent)
		ft_printf("  ");
	ft_printf("Command: %s [", node->u_data.cmd.cmd->raw);
	i = 0;
	while (node->u_data.cmd.args[i++])
	{
		ft_printf("%s", node->u_data.cmd.args[i - 1]->raw);
		if (i - 1 < node->u_data.cmd.argc - 1)
			ft_printf(", ");
	}
	ft_printf("]\n");
	i = 0;
	while (node->u_data.cmd.redirects[i++])
	{
		j = 0;
		while (j++ < indent + 1)
			ft_printf("  ");
		ft_printf("Redirect: %s %s\n",
			node->u_data.cmd.redirects[i - 1]->type,
			node->u_data.cmd.redirects[i - 1]->target->raw);
	}
}

static void	print_pipe(t_ast_node *node, int indent)
{
	int	i;

	i = 0;
	ft_printf("Pipeline: \n");
	while (node->u_data.pipe.commands[i])
	{
		print_cmd_node(node->u_data.pipe.commands[i], indent + 1);
		i++;
	}
}

void	print_ast(t_ast_node *node, int indent)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < indent)
	{
		ft_printf("  ");
		i++;
	}
	if (node->type == NODE_PIPE)
		print_pipe(node, indent);
	else if (node->type == NODE_CMD)
		print_cmd_node(node, indent - 1);
	else
	{
		printf("Logical: \n");
		print_ast(node->u_data.logical.left, indent + 1);
		print_ast(node->u_data.logical.right, indent + 1);
	}
}
