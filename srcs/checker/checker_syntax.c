/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:45:59 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/20 17:04:28 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checker.h"

int	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}

int	check_list(t_token *tokens)
{
	t_token	*tmp;
	t_token	*prev;
	int		depth;

	tmp = tokens;
	prev = NULL;
	depth = 0;
	while (tmp)
	{
		if (tmp->type == -1)
			return (print_syntax_error(tmp->lexeme));
		if (update_depth(tmp->type, &depth) == 1)
			return (-1);
		if (check_operator_syntax(tmp) == -1)
			return (-1);
		if (check_subshell_syntax(tmp, prev) == -1)
			return (-1);
		prev = tmp;
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
	if (depth == -1)
		return (FAILURE);
	return (SUCESS);
}
