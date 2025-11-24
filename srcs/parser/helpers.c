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
	size_t	i;
	t_token	*token;

	if (parser->pos > parser->count)
		return (NULL);
	i = 0;
	token = *parser->tokens;
	while (token && i < parser->pos)
	{
		i++;
		token = token->next;
	}
	return (token);
}

void	parser_advance(t_parser *parser)
{
	if (parser->pos < parser->count)
		parser->pos += 1;
}
