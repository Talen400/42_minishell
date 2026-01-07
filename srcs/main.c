/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:28:15 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/06 19:03:48 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/expander.h"
#include "../includes/autocomplete.h"
#include "../includes/exec.h"
#include "../includes/signals.h"

static void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->envvars[i])
	{
		free(data->envvars[i]);
		i++;
	}
	free(data->envvars);
	free(data->user);
}

int	minishell(char *line, t_data *data)
{
	t_parser	*parser;
	t_ast_node	*ast;

	if (!line || !*line)
		return (1);
	parser = init_parser(line);
	if (!parser)
		return (2);
	ast = parse_sequence(parser);
	if (!ast)
	{
		clear_parser(parser);
		return (2);
	}
	expand_ast(ast, data);
	print_ast(ast, 0);
	data->last_status = exec_ast(ast, data);
	clear_ast(ast);
	clear_parser(parser);
	return (data->last_status);
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
		data.last_status = minishell(line, &data);
		free(line);
	}
	clear_data(&data);
	(void) argc;
	(void) argv;
	return (data.exit_status / 256);
}
