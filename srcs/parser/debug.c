/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:39:03 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/06 19:00:28 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	print_exp_value(t_expandable_value *val)
{
	if (!val)
	{
		dprintf(2, "(NULL)");
		return ;
	}
	dprintf(2, "[Type: %d | Raw: '%s' | Proc: '%s']",
			val->type, val->raw, val->processed);
}

static void	print_cmd_node(t_ast_node *node, int indent)
{
	size_t	i;
	int		j;
	t_redirect_value *r;

	j = 0;
	while (j++ < indent)
		dprintf(2, "	");
	dprintf(2, "CMD_NODE: \n");
	j = 0;
	while (j++ < indent)
		dprintf(2, "	");
	// Execution
	dprintf(2, "Exec: ");
	print_exp_value(node->u_data.cmd.cmd);
	dprintf(2, "\n");
	j = 0;
	// ARGS
	while (j++ < indent)
		dprintf(2, "	");
	dprintf(2, "Args (%zu): ", node->u_data.cmd.argc);
	i = 0;
	while (i < node->u_data.cmd.argc)
	{
		print_exp_value(node->u_data.cmd.args[i]);
		if (i< node->u_data.cmd.argc - 1)
			dprintf(2, ", ");
		i++;
	}
	dprintf(2, "\n");
	// Redirects
	i = 0;
	while (i < node->u_data.cmd.redirect_count)
	{
		r = node->u_data.cmd.redirects[i];
		j = 0;
		while (j++ < indent)
			dprintf(2, "	");
		dprintf(2, "REDIRECT: [%s] no FD %d ->", r->type, r->og_fd);
		print_exp_value(r->target);
		dprintf(2, "\n");
		i++;
	}
}

static void	print_pipe(t_ast_node *node, int indent)
{
	int	i;

	i = 0;
	dprintf(2, "Pipeline: \n");
	while (node->u_data.pipe.commands[i])
	{
		print_ast(node->u_data.pipe.commands[i], indent + 1);
		i++;
	}
}

void	print_ast(t_ast_node *node, int indent)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i++ < indent)
		dprintf(2, "  ");
	if (node->type == NODE_PIPE)
		print_pipe(node, indent);
	else if (node->type == NODE_CMD)
		print_cmd_node(node, indent + 1);
	else
	{
		i = 0;
		while (i++ < indent)
			dprintf(2, "	");
		dprintf(2, "Logical: \n");
		print_ast(node->u_data.logical.left, indent + 1);
		print_ast(node->u_data.logical.right, indent + 1);
	}
}
