/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:11:01 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/09 16:39:49 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/lexer.h"

t_token	*parser_current(t_parser *parser)
{
	t_token	*token;

	if (!parser || !*parser->tokens)
		return (NULL);
	token = *parser->tokens;
	return (token);
}

void	parser_advance(t_parser *parser)
{
	t_token	*new_token;
	t_token	*tokens;

	tokens = *parser->tokens;
	if (tokens && parser->pos < parser->count)
	{
		new_token = tokens->next;
		*parser->tokens = new_token;
		parser->pos += 1;
	}
}

int	is_token_arg(t_token *token)
{
	if (token->type == TOKEN_WORD
		|| token->type == TOKEN_SQUOTE
		|| token->type == TOKEN_DQUOTE
		|| token->type == TOKEN_EXPANSER
		|| token->type == TOKEN_SUB_CMD
		|| token->type == TOKEN_OPEN_PAR)
		return (1);
	return (0);
}

int	is_redirect_token(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_APPEND)
		return (1);
	return (0);
}

int	get_redirect_fd(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}
