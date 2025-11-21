/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_driven.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:59:14 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/20 21:16:54 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	get_char_type(char c)
{
	if (c == ' ' || c == '\t')
		return (WSPACE);
	if (c == '|')
		return (PIPE);
	if (c == '&')
		return (AND);
	if (c == '<')
		return (LESS);
	if (c == '>')
		return (GREATER);
	if (c == '(')
		return (OPEN_PAR);
	if (c == ')')
		return (CLOSE_PAR);
	if (c == '\'')
		return (S_QUOTE);
	if (c == '"')
		return (D_QUOTE);
	if (c == '$')
		return (DOLLAR);
	if (c == '\0')
		return (NUL);
	return (LETTER);
}

int	get_state(t_automato *aut, char character)
{
	int	char_type;
	int	state;

	state = aut->state;
	if (state < 0 || state >= NUM_STATE)
		return (-1);
	char_type = get_char_type(character);
	return (aut->table[state][char_type]);
}
