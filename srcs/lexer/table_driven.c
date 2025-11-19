/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_driven.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:59:14 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 18:06:45 by tlavared         ###   ########.fr       */
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

int	(*get_table(void))[NUM_TYPES]
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
			||  (c >= '0' && c <= '9') || c == '-' || c == '.'
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
