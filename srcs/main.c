/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:30:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/22 01:41:00 by tlavared         ###   ########.fr       */
/*   Updated: 2025/11/19 20:26:02 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/expander.h"
#include "../includes/exec.h"

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
	//print_ast(ast, 0);
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
