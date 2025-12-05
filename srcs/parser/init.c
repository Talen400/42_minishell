/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:36:54 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/26 20:05:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

static size_t	count_tokens(t_token **tokens)
{
	size_t	count;
	t_token	*token;

	count = 0;
	token = *tokens;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_parser	*init_parser(char *str)
{
	t_parser	*res;
	t_token		*tokens;

	res = malloc(sizeof(t_parser));
	if (!res)
		return (NULL);
	tokens = NULL;
	automato(str, &tokens);
	if (!tokens)
	{
		free(res);
		return (NULL);
	}
	res->pos = 0;
	res->tokens = malloc(sizeof(t_token *));
	*res->tokens = tokens;
	res->head_of_tokens = malloc(sizeof(t_token *));
	*res->head_of_tokens = tokens;
	res->count = count_tokens(&tokens);
	return (res);
}

t_redirect_value	*create_redir_node(t_token *token)
{
	t_redirect_value	*node;

	node = ft_calloc(1, sizeof(t_redirect_value));
	if (!node)
		return (NULL);
	node->type = ft_strdup(token->lexeme);
	return (node);
}

t_expandable_value	*create_expandable_value(t_token *token)
{
	t_expandable_value	*res;

	res = malloc(sizeof(t_expandable_value));
	res->type = LITERAL;
	if (token->type == TOKEN_EXPANSER)
	{
		if (ft_strncmp(token->lexeme, "$(", 3) == 0)
			res->type = PAREN;
		else
			res->type = SIMPLE_VAR;
	}
	else if (token->type == TOKEN_DQUOTE)
		res->type = QUOTED;
	else if (token->type == TOKEN_WORD && ft_strchr(token->lexeme, '*'))
		res->type = WILDCARD;
	res->processed = NULL;
	res->raw = ft_strdup(token->lexeme);
	if (!res->raw)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

t_ast_node	*create_node(int type)
{
	t_ast_node	*res;

	res = ft_calloc(1, sizeof(t_ast_node));
	if (!res)
		return (NULL);
	res->type = type;
	res->u_data.cmd.argc = 0;
	res->u_data.cmd.redirect_count = 0;
	res->u_data.cmd.cmd = NULL;
	return (res);
}
