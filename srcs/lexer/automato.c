/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:02:01 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 18:29:17 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/*
 * table-driven :
 * 			SPACE	WORD	|	&	<	>	(	)	'	"	_NULL   		
 * state 0		0		1	2	4	6	8	10	11	12	13	0
 * state 1		0		1	0	0	0	0	0	0	12	13	0
 * state 2		0		1	3	4	6	8	10	11	12	13	0	(| waiting)
 * state 3		0		1	2	4	6	8	10	11	12	13	0	(|| complet)
 * state 4		0		1	2	5	6	8	10	11	12	13	0	(& waiting)
 * state 5		0		1	2	4	6	8	10	11	12	13	0	(&& complet)
 * state 6		0		1	2	4	7	8	10	11	12	13	0	(< waiting)
 * state 7		0		1	2	4	6	8	10	11	12	13	0	(<< complet)
 * state 8		0		1	2	4	6	9	10	11	12	13	0	(< waiting)
 * state 9		0		1	2	4	6	8	10	11	12	13	0	(>> complet)
 * state 10		0		1	2	4	6	8	10	11	12	13	0	( '(' )
 * state 11		0		1	2	4	6	8	10	11	12	13	0	( ')' )
 * state 12		12		12	12	12	12	12	12	12	1	12	12	('...')
 * state 13		13		13	13	13	13	13	13	13	13	1	13	("...")
 */

static int	(*get_table(void))[NUM_TYPES]
{
	static int	table[NUM_STATE][NUM_TYPES] = {
	{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 12, 13, 0},
	{0, 1, 3, 4, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 5, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 7, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 6, 9, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 0},
	{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 0},
	{12, 12, 12, 12, 12, 12, 12, 12, 1, 12, 12},
	{13, 13, 13, 13, 13, 13, 13, 13, 13, 1, 13},
	};

	return (table);
}

int	state_final(t_automato *aut, char *str)
{
	aut->lexeme = ft_substr(str, aut->i - aut->lexeme_len, aut->lexeme_len);
	/* debug
	printf("Lexemer: '%s' len: %d position(str): %d \n", aut->lexeme,
		aut->lexeme_len, aut->i);
	*/
	aut->lexeme_len = 0;
	free(aut->lexeme);
	aut->lexeme = NULL;
	return (SUCESS);
}

int	state_is_final(int state)
{
	return (state == WHITE_SPACE);
}

int	automato(char *str)
{
	t_automato	aut;

	if (!str)
		return (FAILURE);
	ft_memset(&aut, 0, sizeof(aut));
	aut.str_len = ft_strlen(str);
	aut.table = get_table();
	while (aut.i <= aut.str_len)
	{
		aut.state = get_state(&aut, str[aut.i]);
		if (aut.state != WHITE_SPACE)
			aut.lexeme_len += 1;
		if (aut.state == -1)
		{
			printf("Error lexer\n");
			break ;
		}
		if (state_is_final(aut.state))
			if (state_final(&aut, str))
				return (FAILURE);
		aut.i++;
	}
	return (SUCESS);
}
