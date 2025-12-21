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
	t_token	*merged;

	if (!parser || !*parser->tokens)
		return (NULL);
	token = *parser->tokens;
	if (token->type == TOKEN_SUB_CMD || token->type == TOKEN_OPEN_PAR)
	{
		merged = merge_expander_token(parser);
		return (merged);
	}
	return (token);
}

void	parser_advance(t_parser *parser)
{
	t_token	*new_token;
	t_token	*tokens;

	tokens = *parser->tokens;
	if (tokens && (tokens->type == TOKEN_SUB_CMD
		|| tokens->type == TOKEN_OPEN_PAR))
	{
		skip_matching_parens(parser);
		return ;
	}
	if (tokens && parser->pos < parser->count)
	{
		new_token = tokens->next;
		*parser->tokens = new_token;
		parser->pos += 1;
	}
}
