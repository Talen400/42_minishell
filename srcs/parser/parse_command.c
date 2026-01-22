/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:01:10 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/22 13:41:52 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/exec.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static t_token	*get_first_arg_token(t_parser *parser)
{
	t_token	*token;

	token = parser_current(parser);
	while (token)
	{
		if (is_token_arg(token))
			return (token);
		else if (is_redirect_token(token))
		{
			token = token->next;
			if (token && is_token_arg(token))
				token = token->next;
			else
				return (NULL);
		}
		else
			return (NULL);
	}
	return (NULL);
}

static int	handle_redirect(t_ast_node *node, t_parser *parser,
							t_token *token, t_data *data)
{
	t_redirect_value	*redir_node;
	int					fd;

	fd = get_redirect_fd(token);
	if (node->u_data.cmd.redirects[fd])
	{
		clear_expandable_value(node->u_data.cmd.redirects[fd]->target);
		free(node->u_data.cmd.redirects[fd]->type);
		free(node->u_data.cmd.redirects[fd]);
	}
	redir_node = create_redir_node(token);
	parser_advance(parser);
	token = parser_current(parser);
	if (!token || !is_token_arg(token))
		return (handle_redirect_failure(redir_node));
	redir_node->target = create_expandable_value(token);
	redir_node->og_fd = fd;
	if (ft_strcmp(redir_node->type, "<<") == 0)
	{
		redir_node->tmp_fd_heredoc = handle_heredoc(token->lexeme, data);
	}
	parser_advance(parser);
	node->u_data.cmd.redirects[fd] = redir_node;
	return (SUCESS);
}

size_t	count_args(t_parser *parser)
{
	t_token	*token;
	size_t	arg_count;

	token = parser_current(parser);
	arg_count = 0;
	while (token)
	{
		if (is_token_arg(token))
		{
			arg_count++;
			token = token->next;
		}
		else if (is_redirect_token(token))
		{
			token = token->next;
			if (token && is_token_arg(token))
				token = token->next;
			else
				break ;
		}
		else
			break ;
	}
	return (arg_count);
}

static void	parse_tokens(t_parser *parser, t_ast_node *node)
{
	t_token	*token;

	token = parser_current(parser);
	while (token)
	{
		if (is_redirect_token(token))
		{
			if (handle_redirect(node, parser, token, parser->data) == FAILURE)
				break ;
		}
		else if (is_token_arg(token))
		{
			node->u_data.cmd.args[
				node->u_data.cmd.argc++] = create_expandable_value(token);
			node->u_data.cmd.args[node->u_data.cmd.argc] = NULL;
			if (token->type == TOKEN_SUB_CMD)
				node->u_data.cmd.is_paren = 1;
			parser_advance(parser);
		}
		else
			break ;
		token = parser_current(parser);
	}
}

t_ast_node	*parse_command(t_parser *parser)
{
	t_token		*token;
	t_ast_node	*res;
	t_token		*first_arg_token;
	size_t		arg_count;

	token = parser_current(parser);
	if (!token)
		return (NULL);
	res = create_node(NODE_CMD);
	res->u_data.cmd.is_paren = 0;
	res->u_data.cmd.redirects = ft_calloc(3, sizeof(t_redirect_value *));
	res->u_data.cmd.cmd = NULL;
	arg_count = count_args(parser);
	res->u_data.cmd.args = ft_calloc(arg_count + 1,
			sizeof(t_expandable_value *));
	first_arg_token = get_first_arg_token(parser);
	parse_tokens(parser, res);
	if (res->u_data.cmd.argc == 0)
		return (res);
	res->u_data.cmd.cmd = create_expandable_value(first_arg_token);
	return (res);
}
