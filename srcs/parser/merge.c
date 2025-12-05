/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:33:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/26 19:37:57 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

static int	is_expander(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_EXPANSER)
	{
		if (ft_strncmp(token->lexeme, "$(", 3) == 0)
			return (1);
	}
	if (token->type == TOKEN_OPEN_PAR)
		return (1);
	return (0);
}

static int	find_matching_parenthesis(t_token *start)
{
	t_token	*curr;
	int		depth;
	int		count;

	depth = 1;
	count = 0;
	curr = start;
	if (!is_expander(start))
		return (1);
	while (curr && depth > 0)
	{
		if ((curr->type == TOKEN_OPEN_PAR || curr->type == TOKEN_EXPANSER)
			&& count != 0)
			depth++;
		if (curr->type == TOKEN_CLOSE_PAR)
			depth--;
		if (depth > 0)
			count++;
		curr = curr->next;
	}
	return (count + 1);
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	return (res);
}

t_token	*merge_expander_token(t_parser *parser)
{
	t_token	*res;
	t_token	*curr;
	char	*combined;
	int		i;
	int		count;

	curr = *parser->tokens;
	if (!curr || !is_expander(curr))
		return (curr);
	combined = ft_strdup(curr->lexeme);
	count = find_matching_parenthesis(curr);
	curr = curr->next;
	i = 0;
	while (curr && i < count - 1)
	{
		if (i > 0 && i < count - 2)
			combined = join_and_free(combined, " ");
		combined = join_and_free(combined, curr->lexeme);
		curr = curr->next;
		i++;
	}
	res = create_node_token(combined, TOKEN_EXPANSER);
	return (res);
}

void	skip_matching_parens(t_parser *parser)
{
	int		count;
	t_token	*token;
	int		i;

	token = *parser->tokens;
	count = find_matching_parenthesis(token);
	i = 0;
	while (token && i < count)
	{
		token = token->next;
		i++;
	}
	*parser->tokens = token;
	parser->pos += i;
}
