/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:30:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 18:05:21 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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
