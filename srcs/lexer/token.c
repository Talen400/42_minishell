/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:29:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/24 16:30:25 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*create_node_token(char *lexeme, int type)
{
	t_token	*node;

	node = malloc (sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->lexeme = lexeme;
	node->next = NULL;
	return (node);
}

void	add_front_token(t_token **list, char *lexeme, int type)
{
	t_token	*head;
	t_token	*token;

	head = *list;
	token = create_node_token(lexeme, type);
	if (!token)
		return ;
	if (!head)
	{
		*list = token;
		return ;
	}
	while (head && head->next)
		head = head->next;
	head->next = token;
}

void	token_clear_list(t_token **list)
{
	t_token	*head;
	t_token	*node;

	if (list)
	{
		head = *list;
		while (head)
		{
			node = head->next;
			if (head->lexeme)
				free(head->lexeme);
			free(head);
			head = node;
		}
	}
}
