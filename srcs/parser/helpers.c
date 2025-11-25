/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:11:01 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/24 17:44:34 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_token	*parser_current(t_parser *parser)
{
	t_token	**token;

	token = parser->tokens;
	if (token)
		return (*token);
	return (NULL);
}

void	parser_advance(t_parser *parser)
{
	t_token	*new_token;
	t_token	*tokens;

	tokens = *parser->tokens;
	if (parser->pos < parser->count)
	{
		new_token = tokens->next;
		*parser->tokens = new_token;
		parser->pos += 1;
	}
}
