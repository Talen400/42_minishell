/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:39:04 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/23 14:46:39 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	handle_subshell_token(t_automato *aut, char *str)
{
	int	depth;

	depth = 1;
	aut->i++;
	while (str[aut->i] && depth > 0)
	{
		if (str[aut->i] == '(')
			depth++;
		else if (str[aut->i] == ')')
			depth--;
		aut->lexeme_len++;
		if (depth > 0)
			aut->i++;
	}
}

int	update_state(t_automato *aut, char c)
{
	aut->prev_state = aut->state;
	aut->state = get_state(aut, c);
	if (aut->state == -1)
		return (FAILURE);
	else if (aut->state != 0)
		aut->lexeme_len += 1;
	return (SUCESS);
}

void	handle_state_final(t_automato *aut, char *str, t_token **tokens)
{
	state_final(aut, str, tokens);
	if (get_char_type(str[aut->i] != WSPACE))
		aut->i--;
}

void	handle_subshell(t_automato *aut, char *str)
{
	handle_subshell_token(aut, str);
	aut->state = 1;
}
