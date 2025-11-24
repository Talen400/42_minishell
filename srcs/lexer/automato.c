/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:02:01 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/24 19:17:53 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/*
 * TABLE DRIVE :
 *
 * ======================================
 *
 * states (complet tokens)
 * 0: SPACE
 * 1: WORD
 * 2: OPERATOR
 * 3: D_OPERATOR
 * 4: S_QUOTE
 * 5: D_QUOTE
 * 6: END S_QUOTE
 * 7: END D_QUOTE
 * 8: EXPANSER
 * 9: END EXPANSER
 *
 *		 		SP	LET	|	&	<	>	(	)	'	"	$	{	}
 * state 0	=	0	1	2	2	2	2	2	2	4	5	8	0	0
 * state 1	=	0	1	0	0	0	0	0	0	4	5	8	0	0
 * state 2	=	0	0	3	3	3	3	0	0	0	0	0	0	0
 * state 3	=	0	0	0	0	0	0	0	0	0	0	0	0	0
 * state 4	=	4	4	4	4	4	4	4	4	6	4	4	4	4
 * state 5	=	5	5	5	5	5	5	5	5	5	7	5	5	5
 * state 6  =	0	0	0	0	0	0	0	0	0	0	0	0	0
 * state 7  =	0	0	0	0	0	0	0	0	0	0	0	0	0
 * state 8  =	0	8	0	0	0	0	9	0	0	0	9	9	0
 * state 9	=	0	0	0	0	0	0	0	0	0	0	0	0	0
 */

static int	(*get_table(void))[NUM_TYPES]
{
	static int	table[NUM_STATE][NUM_TYPES] = {
	{0, 1, 2, 2, 2, 2, 2, 2, 4, 5, 8, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0},
	{0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{4, 4, 4, 4, 4, 4, 4, 4, 6, 4, 4, 4, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 5, 4, 5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 8, 0, 0, 0, 0, 9, 0, 0, 0, 9, 9, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	return (table);
}

int	state_final(t_automato *aut, char *str, t_token **tokens)
{
	int	type_token;

	aut->lexeme = ft_substr(str, aut->i - aut->lexeme_len, aut->lexeme_len);
	type_token = get_type_token(aut->prev_state, aut->lexeme);
	printf("Lexeme formado! state: %d\n", aut->prev_state);
	add_front_token(tokens, aut->lexeme, type_token);
	aut->lexeme_len = 0;
	aut->lexeme = NULL;
	return (SUCESS);
}

int	ft_handler(const char *str)
{
	printf("%s", str);
	return (FAILURE);
}

/*
 * test : 
 * ((echo << "here" && (cat Makefile | wc -l)) >> code.txt) || ( echo ":>" > teste.txt)
 */

int	automato(char *str, t_token **tokens)
{
	t_automato	aut;

	if (!str)
		return (FAILURE);
	ft_memset(&aut, 0, sizeof(aut));
	aut.str_len = ft_strlen(str);
	aut.table = get_table();
	while (aut.i <= aut.str_len)
	{
		aut.prev_state = aut.state;
		aut.state = get_state(&aut, str[aut.i]);
		printf("state: %d, str[i]: %c\n", aut.state, str[aut.i]);
		if (aut.state == -1)
			return (ft_handler("Error lexer \n"));
		else if (aut.state != 0)
			aut.lexeme_len += 1;
		if (aut.state == 0 && aut.prev_state != 0)
		{
			printf("Fecohou!\n");
			state_final(&aut, str, tokens);
			if (get_char_type(str[aut.i] != WSPACE))
			{
				aut.i--;
				printf("volta!\n");
			}
		}
		aut.i++;
	}
	return (SUCESS);
}
