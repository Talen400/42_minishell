/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:24:02 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/23 14:28:18 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

int	skip_quote(t_automato_expander *aut)
{
	return ((aut->word[aut->i] == '\'' && (aut->state == 2
				|| aut->prev_state == 2))
		|| (aut->word[aut->i] == '\"' && (aut->state == 1
				|| aut->prev_state == 1)));
}

int	is_subshell(t_automato_expander *aut)
{
	return (aut->word[aut->i + 1] && aut->word[aut->i] == '$'
		&& aut->word[aut->i + 1] == '(' && aut->state != 2);
}

int	is_dollar_expansion(t_automato_expander *aut)
{
	return (aut->word[aut->i] == '$' && aut->state != 2);
}
