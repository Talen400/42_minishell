/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_driven_expander.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:00:57 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/17 13:09:56 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

int	get_char_type_expander(char c)
{
	if (c == '"')
		return (D_QUOTE_EXPANSER);
	if (c == '\'')
		return (S_QUOTE_EXPANSER);
	if (c == '$')
		return (DOLLAR_EXPANSER);
	if (c == '(')
		return (OPEN_PAR_EXPANSER);
	if (c == ')')
		return (CLOSE_PAR_EXPANSER);
	if (c == '*')
		return (WILDCARD_EXPANSER);
	return (LETTER_EXPANSER);
}

int	get_state_expander(t_automato_expander *aut, char character)
{
	int	char_type;
	int	state;

	state = aut->state;
	if (state < 0 || state >= NUM_STATE_EXPANDER)
		return (-1);
	char_type = get_char_type_expander(character);
	return (aut->table[state][char_type]);
}
