/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:25:06 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/23 22:53:28 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	print_tokens(t_token *tokens)
{
	t_token	*node;

	node = tokens;
	while (node)
	{
		dprintf(2, "type: %d | lexeme: '%s'\n", node->type, node->lexeme);
		node = node->next;
	}
}
