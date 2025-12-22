/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:28:15 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 11:22:23 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/expander.h"
#include "../includes/autocomplete.h"
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
	init_readline();
	while (data.is_running)
	{
		line = ft_readline(&data);
		parser = init_parser(line);
		ast = parse_sequence(parser);
		expand_ast(ast, &data);
		exec_ast(ast, &data);
		clear_ast(ast);
		clear_parser(parser);
		free(line);
	}
	clear_data(&data);
	return (data.exit_status);
}
