/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:01:10 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/26 20:04:30 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stddef.h>
#include <unistd.h>

static int	handle_redirect(t_ast_node *node, t_parser *parser,
							t_token *token, int fd)
{
	t_redirect_value	*redir_node;

	redir_node = create_redir_node(token);
	parser_advance(parser);
	token = parser_current(parser);
	if (!token || (token->type != TOKEN_WORD && token->type != TOKEN_SQUOTE))
	{
		free(redir_node->type);
		free(redir_node->target);
		free(redir_node);
		return (FAILURE);
	}
	redir_node->target = ft_strtrim(token->lexeme, "'");
	redir_node->og_fd = fd;
	parser_advance(parser);
	node->u_data.cmd.redirects[node->u_data.cmd.redirect_count++] = redir_node;
	node->u_data.cmd.redirects[node->u_data.cmd.redirect_count] = NULL;
	return (SUCESS);
}

static void	handle_args(t_parser *parser, t_ast_node *node, t_token *token)
{
	if (node->u_data.cmd.argc >= node->u_data.cmd.arg_capacity)
	{
		node->u_data.cmd.arg_capacity *= 2;
		node->u_data.cmd.args = ft_realloc(node->u_data.cmd.args,
				(node->u_data.cmd.arg_capacity + 1) * sizeof(char *));
	}
	node->u_data.cmd.args[
		node->u_data.cmd.argc++] = ft_strtrim(token->lexeme, "'");
	node->u_data.cmd.args[node->u_data.cmd.argc] = NULL;
	parser_advance(parser);
}

static void	loop_through_node(t_parser *parser, t_ast_node *node)
{
	t_token			*token;

	token = parser_current(parser);
	while (token)
	{
		if (token->type == TOKEN_REDIR_OUT)
		{
			if (handle_redirect(node, parser, token, STDOUT_FILENO) != SUCESS)
				break ;
		}
		else if (token->type == TOKEN_WORD || token->type == TOKEN_SQUOTE)
			handle_args(parser, node, token);
		else
			break ;
		token = parser_current(parser);
	}
}

t_ast_node	*parse_command(t_parser *parser)
{
	t_token		*token;
	t_ast_node	*res;

	token = parser_current(parser);
	if (!token)
		return (NULL);
	res = create_node(NODE_CMD);
	res->u_data.cmd.redirects = ft_calloc(4, sizeof(t_redirect_value *));
	res->u_data.cmd.args = ft_calloc(8, sizeof(char *));
	res->u_data.cmd.arg_capacity = 8;
	if (token->type == TOKEN_REDIR_IN)
		handle_redirect(res, parser, token, STDIN_FILENO);
	token = parser_current(parser);
	if (!token || (token->type != TOKEN_WORD && token->type != TOKEN_SQUOTE))
	{
		clear_command_node(res, NODE_PIPE);
		return (NULL);
	}
	res->u_data.cmd.cmd = ft_strtrim(token->lexeme, "'");
	loop_through_node(parser, res);
	return (res);
}
