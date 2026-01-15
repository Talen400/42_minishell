/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:02:01 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/15 17:55:00 by fbenini-         ###   ########.fr       */
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
 *		 		SP	LET	|	&	<	>	(	)	'	"	$	{	}	\0
 * state 0	=	0	1	2	2	2	2	2	2	4	5	8	0	0	0
 * state 1	=	0	1	0	0	0	0	0	0	4	5	8	0	0	0
 * state 2	=	0	0	3	3	3	3	0	0	0	0	0	0	0	0
 * state 3	=	0	0	0	0	0	0	0	0	0	0	0	0	0	0
 * state 4	=	4	4	4	4	4	4	4	4	6	4	4	4	4	0
 * state 5	=	5	5	5	5	5	5	5	5	5	7	5	5	5	0
 * state 6  =	0	1	0	0	0	0	0	0	4	5	8	0	0	0
 * state 7  =	0	1	0	0	0	0	0	0	4	5	8	0	0	0
 * state 8  =	0	8	0	0	0	0	9	0	4	5	9	9	0	0
 * state 9	=	0	1	0	0	0	0	0	0	4	5	8	0	0	0
 */

static int	(*get_table(void))[NUM_TYPES]
{
	static int	table[NUM_STATE][NUM_TYPES] = {
	{0, 1, 2, 2, 2, 2, 2, 2, 4, 5, 8, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 4, 5, 8, 0, 0, 0},
	{0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{4, 4, 4, 4, 4, 4, 4, 4, 6, 4, 4, 4, 5, 0},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 5, 4, 5, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 4, 5, 8, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 4, 5, 8, 0, 0, 0},
	{0, 8, 0, 0, 0, 0, 9, 0, 4, 5, 9, 9, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 4, 5, 8, 0, 0, 0}
	};

	return (table);
}

int	state_final(t_automato *aut, char *str, t_token **tokens)
{
	int	type_token;

	aut->lexeme = ft_substr(str, aut->i - aut->lexeme_len, aut->lexeme_len);
	type_token = get_type_token(aut->prev_state, aut->lexeme);
	add_front_token(tokens, aut->lexeme, type_token);
	aut->lexeme_len = 0;
	aut->lexeme = NULL;
	return (SUCESS);
}

static void	handle_parens(t_automato *aut, char *str, t_token **tokens)
{
	int	depth;

	depth = 0;
	while (str[aut->i])
	{
		if (str[aut->i] == '(')
			depth++;
		else if (str[aut->i] == ')')
			depth--;
		aut->lexeme_len++;
		aut->i++;
		if (depth == 0)
			break ;
	}
	aut->lexeme = ft_substr(str, aut->i - aut->lexeme_len, aut->lexeme_len);
	add_front_token(tokens, aut->lexeme, TOKEN_SUB_CMD);
	aut->lexeme_len = 0;
	aut->state = 0;
	aut->prev_state = 0;
}

static int	handle_special_cases(t_automato *aut, char *str, t_token **tokens)
{
	if (aut->state != 4 && str[aut->i] == '$' && str[aut->i + 1] == '(')
	{
		if (aut->state == 0 && aut->prev_state != 0)
			handle_state_final(aut, str, tokens);
		handle_subshell(aut, str);
		return (1);
	}
	if ((aut->state != 4 && aut->state != 5) && str[aut->i] == '(')
	{
		if (aut->lexeme_len > 0)
		{
			aut->prev_state = aut->state;
			state_final(aut, str, tokens);
		}
		handle_parens(aut, str, tokens);
		return (1);
	}
	return (0);
}

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
		if (handle_special_cases(&aut, str, tokens))
			continue ;
		if (update_state(&aut, str[aut.i]))
			return (FAILURE);
		if (aut.state == 0 && aut.prev_state != 0)
			handle_state_final(&aut, str, tokens);
		aut.i++;
	}
	return (SUCESS);
}
