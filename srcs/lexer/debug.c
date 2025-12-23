/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:25:06 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/23 13:27:32 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	print_tokens(t_token *tokens)
{
	t_token	*node;

	node = tokens;
	while (node)
	{
		// dprint remove
		dprintf(2, "type: %d | lexeme: %s\n", node->type, node->lexeme);
		node = node->next;
	}
}
