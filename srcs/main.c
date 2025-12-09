/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:30:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/06 17:20:54 by tlavared         ###   ########.fr       */
/*   Updated: 2025/11/19 20:26:02 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/expander.h"

static char	*create_str(t_expandable_value *value)
{
	if (!value->processed)
		return (ft_strdup(value->raw));
	return (ft_strdup(value->processed));
}

static void	exec_test(t_ast_node *node, t_data *data)
{
	char	**args;
	int		i;
	t_builtin_cmd	builtin_func;

	if (node->type != NODE_CMD)
		return ;
	i = 0;
	while (node->u_data.cmd.args[i])
		i++;
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (node->u_data.cmd.args[i])
	{
		args[i] = create_str(node->u_data.cmd.args[i]);
		i++;
	}
	builtin_func = get_builtin(args[0]);
	if (builtin_func)
		builtin_func(args, data);
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
		print_ast(ast, 0);
		clear_ast(ast);
		clear_parser(parser);
		free(test);
	}
	free(test);
	return (SUCESS);
}
