/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:02:01 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 18:09:44 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
