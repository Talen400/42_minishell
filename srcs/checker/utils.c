/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:36:38 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/14 19:39:05 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checker.h"

int	check_operator_syntax(t_token *tmp)
{
	if (is_logical_or_pipe(tmp->type))
	{
		if (!tmp->next || is_logical_or_pipe(tmp->next->type))
			return (print_syntax_error(tmp->lexeme));
	}
	return (0);
}

int	check_subshell_syntax(t_token *tmp, t_token *prev)
{
	int	len;

	if (tmp->type != TOKEN_SUB_CMD)
		return (0);
	len = ft_strlen(tmp->lexeme);
	if (len > 0 && tmp->lexeme[len - 1] != ')')
		return (print_syntax_error("unclosed parenthesis"));
	if (prev && is_word(prev->type))
		return (print_syntax_error(tmp->lexeme));
	if (tmp->next && !is_logical_or_pipe(tmp->next->type)
		&& !is_redirect(tmp->next->type))
		return (print_syntax_error(tmp->next->lexeme));
	return (0);
}

int	update_depth(int type, int *depth)
{
	if (type == TOKEN_OPEN_PAR)
		(*depth)++;
	else if (type == TOKEN_CLOSE_PAR)
	{
		(*depth)--;
		if (*depth < 0)
			return (print_syntax_error(")"));
	}
	return (0);
}
