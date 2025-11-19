/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_driven.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:59:14 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 18:27:32 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_char_type	get_char_type(char c)
{
	if (c == ' ')
		return (WHITE_SPACE);
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (REDIRECT_INPUT);
	if (c == '>')
		return (REDIRECT_OUTPUT);
	if (c == '&')
		return (AND);
	if (c == '(')
		return (OPEN_P);
	if (c == ')')
		return (CLOSE_P);
	if (c == '\'')
		return (QUOTE);
	if (c == '"')
		return (DOUBLE_QUOTE);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9') || c == '-' || c == '.'
		|| c == '$')
		return (WORD);
	return (-1);
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
