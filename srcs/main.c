/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:30:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/09 20:57:43 by tlavared         ###   ########.fr       */
/*   Updated: 2025/11/19 20:26:02 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../includes/expander.h"
#include "../includes/exec.h"

static void	exec_test(t_ast_node *node, t_data *data)
{
	if (node->type == NODE_CMD)
		exec_cmd(node, data);
}

int	main(int argc, char *argv[], char *envvars[])
{
	char		*test;
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
		ast = parse_sequence(parser);
		expand_ast(ast, &data);
		exec_test(ast, &data);
		clear_ast(ast);
		clear_parser(parser);
		free(test);
	}
	clear_data(&data);
	free(test);
	return (SUCESS);
}
