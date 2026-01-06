/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:45:59 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/04 19:02:11 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (FAILURE);
}

static int	is_logical_or_pipe(int type)
{
	return (type == TOKEN_PIPE
		|| type == TOKEN_AND || type == TOKEN_OR);
}

int	check_list(t_token *tokens)
{
	t_token	*tmp;
	int		depth;

	tmp = tokens;
	depth = 0;
	while (tmp)
	{
		if (tmp->type == -1)
			return (print_syntax_error(tmp->lexeme));
		if (tmp->type == TOKEN_OPEN_PAR)
			depth++;
		else if (tmp->type == TOKEN_CLOSE_PAR)
		{
			depth--;
			if (depth < 0)
				return (print_syntax_error(")"));
		}
		if (is_logical_or_pipe(tmp->type))
		{
			if (!tmp->next || is_logical_or_pipe(tmp->next->type)
				|| tmp->next->type == TOKEN_OPEN_PAR)
				return (print_syntax_error(tmp->lexeme));
		}
		tmp = tmp->next;
	}
	return (depth);
}

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;
	int		depth;

	tmp = tokens;
	if (!tmp)
		return (SUCESS);
	if (tmp->type == TOKEN_PIPE
		|| tmp->type == TOKEN_AND || tmp->type == TOKEN_OR)
		return (print_syntax_error(tmp->lexeme));
	depth = check_list(tokens);
	if (depth != 0)
		return (print_syntax_error("unclosed parenthesis"));
	return (SUCESS);
}
