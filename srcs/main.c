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
#include "../includes/parser.h"
#include "../includes/expander.h"

int	main(int argc, char *argv[], char *envvars[])
{
	char	*test;
	t_parser	*parser;
	t_ast_node	*ast;
	t_data		data;

	(void)argc;
	(void)argv;
	init_data(&data, envvars);
	while (1)
	{
		test = readline("> ");
		if (!ft_strncmp(test, "exit", 4))
			break ;
		parser = init_parser(test);
		get_wildcards_value(test);
		ast = parse_sequence(parser);
		expand_ast(ast, &data);
		print_ast(ast, 0);
		clear_ast(ast);
		clear_parser(parser);
		free(test);
	}
	free(test);
	return (SUCESS);
}
