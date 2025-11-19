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

int	main(int argc, char *argv[], char *envvars[])
{
	t_data	data;
	/*
	t_token	*tokens;
	char	*test;
	*/

	(void)argv;
	(void)argc;
	init_data(&data, envvars);
	read_input(&data);
	/* Usage to generate tokens:
	
	test = readline("asd> ");
	printf("prompt: %s\n", test);
	tokens = NULL;
	if (automato(test, &tokens))
		return (FAILURE);
	print_tokens(tokens);
	token_clear_list(&tokens);
	free(test);
	*/
	return (SUCESS);
}
