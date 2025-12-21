/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:30:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/21 15:38:05 by tlavared         ###   ########.fr       */
/*   Updated: 2025/11/19 20:26:02 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/expander.h"
#include "../includes/exec.h"

int	main(int argc, char *argv[], char *envvars[])
{
	char		*line;
	t_parser	*parser;
	t_ast_node	*ast;
	t_data		data;

	(void)argc;
	(void)argv;
	init_data(&data, envvars);
	while (data.is_running)
	{
		line = ft_readline(&data);
		parser = init_parser(line);
		ast = parse_sequence(parser);
		expand_ast(ast, &data);
		exec_ast(ast, &data);
		//print_ast(ast, 0);
		clear_ast(ast);
		clear_parser(parser);
		free(line);
	}
	clear_data(&data);
	return (data.exit_status);
}
