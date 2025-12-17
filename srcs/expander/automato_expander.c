/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:03:57 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/17 13:11:02 by tlavared         ###   ########.fr       */
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
 * state 1	=	0	1	0	0	0	0	0	0
 * state 2	=	0	0	3	3	3	3	0	0
 * state 3	=	0	0	0	0	0	0	0	0
 * state 4	=	4	4	4	4	4	4	4	0
 * state 5	=	5	5	5	5	5	5	5	0
 */

static int	(*get_table_expanser(void))[NUM_TYPE_EXPANDER]
{
	static int	table[NUM_STATE_EXPANDER][NUM_TYPE_EXPANDER] = {
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
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

int	ft_is_expanser(t_expandable_value *value, t_data *data)
{
	char	*str;
	char	*ptr;
	int		j;
	int		i;
	int		is_expand;
	int		(*table)[NUM_TYPE_EXPANSER];
	
	str = value->raw;
	is_expand = FALSE;
	j = 0;
	value->processed = ft_strdup("");
	table = get_table_expanser();
	while (str[j])
	{
		ft_printf("str[%d]: %c \n", j, str[j]);
		i = 0;
		if (str[j] == '"')
		{
			while (str[i] != '"')
				i++;
			ptr = ft_substr(str, j, i + 1);
			value->processed = join_free(value->processed, ptr);
			j += i;
			is_expand = TRUE;
		}
		else if (str[j] == '\'')
			is_expand = TRUE;
		else if (str[j] == '$')
			is_expand = TRUE;
		else if (str[j] == '*')
			is_expand = TRUE;
		else if (str[j] && str[j + 1] == '$' && str[1] == '(')
			is_expand = TRUE;
		j++;
	}
	if (is_expand == TRUE)
	{
		ft_printf("Yes! %s \n", value->raw);
	}
	(void ) data;
	return (FALSE);
}
