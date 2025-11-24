/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:30:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 20:43:12 by tlavared         ###   ########.fr       */
/*   Updated: 2025/11/19 20:26:02 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int	main(void)
{
	t_token	*tokens;
	char	*test;

	while (1)
	{
		test = readline("> ");
		if (!ft_strncmp(test, "exit", 4))
			break ;
		tokens = NULL;
		if (automato(test, &tokens))
			return (FAILURE);
		print_tokens(tokens);
		token_clear_list(&tokens);
		free(test);
	}
	free(test);
	return (SUCESS);
}
