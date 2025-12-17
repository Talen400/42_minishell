/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:03:57 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/17 15:29:07 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/*
 * TABLE DRIVE :
 *
 * ======================================
 *
 * states (complet tokens)
 * 0: S_QUOTE
 * 1: D_QUOTE
 * 2: END S_QUOTE
 * 3: END D_QUOTE
 * 4: EXPANSER
 * 5: END EXPANSER
 *
 *		 		LET	"	'	$	(	)	*	\0
 * state 0	=	0	1	2	2	2	2	2	0
 * state 1	=	1	0	1	1	1	1	1	0
 * state 2	=	0	0	0	0	0	0	0	0
 * state 3	=	0	0	0	0	0	0	0	0
 * state 4	=	0	0	0	0	0	0	0	0
 * state 5	=	0	0	0	0	0	0	0	0
 */

static int	(*get_table_expander(void))[NUM_TYPE_EXPANDER]
{
	static int	table[NUM_STATE_EXPANDER][NUM_TYPE_EXPANDER] = {
		{0, 1, 2, 2, 2, 2, 2, 0},
		{1, 0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};

	return (table);
}

char	*join_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

int	ft_is_expander(t_expandable_value *value, t_data *data)
{
	t_automato_expander	aut;
	int					is_expand;

	ft_memset(&aut, 0, sizeof(t_automato_expander ));
	aut.str = value->raw;
	value->processed = ft_strdup("");
	aut.table = get_table_expander();
	ft_printf("\n maquina de estado da expansão! \n");
	while (aut.str[aut.i])
	{
		ft_printf("str[%d]: %c \n", aut.i, aut.str[aut.i]);
		aut.prev_state = aut.state;
		aut.state = get_state_expander(&aut, aut.str[aut.i]);
		ft_printf("[%d] prev: %d, state: %d, str: %c \n", aut.i, aut.prev_state, aut.state, aut.str[aut.i]);
		if (aut.state == 1)
		{

		}
		aut.i++;
	}
	if (is_expand == TRUE)
	{
		ft_printf("Yes! %s \n", value->raw);
	}
	(void ) data;
	return (FALSE);
}
