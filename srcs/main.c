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

void print_ast(t_ast_node *node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    
    switch (node->type) {
        case NODE_CMD:
            printf("Command: %s", node->u_data.cmd.cmd);
            if (node->u_data.cmd.argc > 0) {
                printf(" [");
                for (size_t i = 0; i < node->u_data.cmd.argc; i++) {
                    printf("%s%s", node->u_data.cmd.args[i],
                           i < node->u_data.cmd.argc - 1 ? ", " : "");
                }
                printf("]");
            }
			if (node->u_data.cmd.redirect_count > 0) {
                printf("\n");
                for (size_t i = 0; i < node->u_data.cmd.redirect_count; i++) {
                    for (int j = 0; j < indent + 1; j++) printf("  ");
                    printf("Redirect: %s %s\n", 
                           node->u_data.cmd.redirects[i]->type,
							node->u_data.cmd.redirects[i]->target);
                }
            } else {
                printf("\n");
            }
            break;
        case NODE_PIPE:
            printf("Pipeline:\n");
            for (size_t i = 0; i < node->u_data.pipe.count; i++)
                print_ast(node->u_data.pipe.commands[i], indent + 1);
            break;
        case NODE_LOGICAL:
            printf("Logical:\n");
            print_ast(node->u_data.logical.left, indent + 1);
            print_ast(node->u_data.logical.right, indent + 1);
            break;
        case NODE_SEQ:
            printf("Sequence:\n");
            for (size_t i = 0; i < node->u_data.sequence.count; i++)
                print_ast(node->u_data.sequence.commands[i], indent + 1);
            break;
    }
}

int	main(void)
{
	// t_token	*tokens;
	char	*test;
	t_parser	*parser;
	t_ast_node	*ast;

	while (1)
	{
		test = readline("> ");
		if (!ft_strncmp(test, "exit", 4))
			break ;
		// tokens = NULL;
		// if (automato(test, &tokens))
		// 	return (FAILURE);
		parser = init_parser(test);
		ast = parse_sequence(parser);
		print_ast(ast, 0);
		// print_tokens(tokens);
		// token_clear_list(&tokens);
		free(test);
	}
	free(test);
	return (SUCESS);
}
