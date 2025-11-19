/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:30:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 14:19:03 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

/*
 * table-driven :
 * 			SPACE	LETTER	DIGIT	OTHER
 * state 0		0		1		2		3
 * state 1		0		1		1		0
 * state 2		0		0		2		0
 * state 3		3		3		3		3
 *
 */

static int	(*get_table(void))[NUM_TYPES]
{
	static int	table[NUM_STATE][NUM_TYPES] = {
	{0, 1, 2, 3},
	{0, 1, 1, 0},
	{0, 0, 2, 0},
	{3, 3, 3, 3}
	};

	return (table);
}

t_char_type	get_char_type(char c)
{
	if (c == ' ')
		return (SPACE);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (LETTER);
	if (c >= '0' && c <= '9')
		return (DIGIT);
	return (OTHER);
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

int	state_final(t_automato *aut, char *str)
{
	aut->lexeme = ft_substr(str, aut->i - aut->lexeme_len, aut->lexeme_len);
	printf("Lexemer: '%s' len: %d position(str): %d \n", aut->lexeme,
		aut->lexeme_len, aut->i);
	aut->lexeme_len = 0;
	free(aut->lexeme);
	aut->lexeme = NULL;
	return (1);
}

int	state_is_final(int state)
{
	return (state == 0);
}

int	automato(char *str)
{
	t_automato	aut;

	if (!str)
		return (FAILURE);
	ft_memset(&aut, 0, sizeof(aut));
	aut.state = 1;
	aut.str_len = ft_strlen(str);
	aut.table = get_table();
	while (aut.i <= aut.str_len)
	{
		aut.state = get_state(&aut, str[aut.i]);
		printf("estado: %d\n", aut.state);
		if (aut.state != 0 && aut.state != 3)
			aut.lexeme_len += 1;
		printf("lexeme_len: %d\n", aut.lexeme_len);
		if (aut.state == 3)
		{
			printf("Error lexer\n");
			break ;
		}
		if (state_is_final(aut.state))
			state_final(&aut, str);
		aut.i++;
	}
	return (SUCESS);
}

int	main(void)
{
	char	*test;

	test = readline("asd> ");
	printf("prompt: %s\n", test);
	if (automato(test))
		return (FAILURE);
	free(test);
	return (SUCESS);
}
