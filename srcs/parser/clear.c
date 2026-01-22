/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:41:29 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/22 13:41:21 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/lexer.h"

void	clear_parser(t_parser *parser)
{
	if (!parser)
		return ;
	token_clear_list(parser->head_of_tokens);
	free(parser->tokens);
	free(parser->head_of_tokens);
	free(parser);
}

void	clear_expandable_value(t_expandable_value *value)
{
	if (!value)
		return ;
	if (value->processed)
		free(value->processed);
	if (value->raw)
		free(value->raw);
	free(value);
}

void	clear_redir_node(t_redirect_value *value)
{
	clear_expandable_value(value->target);
	free(value->type);
	if (value->tmp_fd_heredoc >= 0)
		close(value->tmp_fd_heredoc);
	free(value);
}

void	clear_command_node(t_ast_node *node, int type)
{
	size_t	i;

	i = 0;
	while (node->u_data.cmd.args[i])
	{
		clear_expandable_value(node->u_data.cmd.args[i]);
		i++;
	}
	free(node->u_data.cmd.args);
	i = 0;
	while (i < 2)
	{
		if (node->u_data.cmd.redirects[i])
			clear_redir_node(node->u_data.cmd.redirects[i]);
		i++;
	}
	free(node->u_data.cmd.redirects);
	clear_expandable_value(node->u_data.cmd.cmd);
	if (type == NODE_PIPE)
		free(node);
}

void	clear_ast(t_ast_node *head)
{
	size_t	i;

	if (!head)
		return ;
	if (head->type == NODE_LOGICAL)
	{
		clear_ast(head->u_data.logical.left);
		clear_ast(head->u_data.logical.right);
	}
	if (head->type == NODE_CMD)
		clear_command_node(head, NODE_CMD);
	if (head->type == NODE_PIPE)
	{
		i = 0;
		while (head->u_data.pipe.commands[i])
			clear_command_node(head->u_data.pipe.commands[i++], NODE_PIPE);
		free(head->u_data.pipe.commands);
	}
	free(head);
}
