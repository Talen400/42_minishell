/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:28:15 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/26 04:33:25 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/expander.h"
#include "../includes/autocomplete.h"
#include "../includes/exec.h"
#include "../includes/signals.h"

int	minishell(char *line, t_data *data)
{
	t_parser	*parser;
	t_ast_node	*ast;

	if (!line || !*line)
		return (0);
	parser = init_parser(line);
	if (!parser)
		return (1);
	ast = parse_sequence(parser);
	if (!ast)
	{
		clear_parser(parser);
		return (1);
	}
	expand_ast(ast, data);
	data->exit_status = exec_ast(ast, data);
	clear_ast(ast);
	clear_parser(parser);
	return (data->exit_status);
}

int	main(int argc, char *argv[], char *envvars[])
{
	char		*line;
	t_data		data;

	init_data(&data, envvars);
	setup_signals();
	init_readline();
	while (data.is_running)
	{
		line = ft_readline(&data);
		if (!line)
			break ;
		data.exit_status = minishell(line, &data);
		free(line);
	}
	clear_data(&data);
	(void) argc;
	(void) argv;
	return (data.exit_status);
}
