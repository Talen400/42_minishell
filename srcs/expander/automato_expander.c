/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:10:39 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/23 14:27:06 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/*
 * TABLE DRIVE :
 *
 * ======================================
 *
 * states
 * 0: INIT
 * 1: D_QUOTE
 * 2: S_QUOTE
 * 3: subshell
 *
 *		 		LET	"	'	$	(	)	*	\0
 * state 0	=	0	1	2	0	0	0	0	0
 * state 1	=	1	0	1	3	1	1	1	0
 * state 2	=	2	2	0	2	2	2	2	0
 * state 2	=	3	3	3	3	3	0	3	0
 */

static int	(*get_table_expander(void))[NUM_TYPE_EXPANDER]
{
	static int	table[NUM_STATE_EXPANDER][NUM_TYPE_EXPANDER] = {
	{0, 1, 2, 0, 0, 0, 0, 0},
	{1, 0, 1, 1, 1, 1, 1, 0},
	{2, 2, 0, 2, 2, 2, 2, 0},
	{3, 3, 3, 3, 3, 0, 3, 0}
	};

	return (table);
}

static void	get_state_helper(t_automato_expander *aut)
{
	aut->prev_state = aut->state;
	aut->state = get_state_expander(aut, aut->word[aut->i]);
}

/*
 * echo test'test'"test""$USER"'$USER'"$(echo $USER)" 
 *
 * ft_printf("[%d] prev: %d, state: %d, str: %c \n",
 * 		aut->i, aut->prev_state, aut->state, aut->word[aut->i]);
*/

void	automato_expander(t_expandable_value *value, t_data *data,
		t_automato_expander*aut)
{
	while (aut->word[aut->i])
	{
		get_state_helper(aut);
		if (skip_quote(aut))
		{
			aut->i++;
			continue ;
		}
		if (is_subshell(aut))
		{
			aut->subshell_cmd = extract_subshell(aut);
			aut->tmp = execute_subshell(aut->subshell_cmd, data);
			value->processed = join_free(value->processed, aut->tmp);
			continue ;
		}
		if (is_dollar_expansion(aut))
		{
			aut->tmp = handle_dollar(aut, data);
			value->processed = join_free(value->processed, aut->tmp);
			continue ;
		}
		value->processed = append_char(value->processed, aut->word[aut->i]);
		aut->i++;
	}
}

int	is_expander(t_expandable_value *value, t_data *data)
{
	t_automato_expander	aut;

	ft_memset(&aut, 0, sizeof(t_automato_expander));
	aut.word = value->raw;
	value->processed = ft_strdup("");
	aut.table = get_table_expander();
	automato_expander(value, data, &aut);
	if (aut.word[aut.i] == '\0')
		return (TRUE);
	return (FALSE);
}
