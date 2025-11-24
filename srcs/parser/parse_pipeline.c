/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:40:37 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/24 19:42:37 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_parser_rule	rule;

	rule.node_type = NODE_PIPE;
	rule.token_type = TOKEN_PIPE;
	rule.next_function = parse_command;
	return (parse_generic(parser, &rule, parse_command));
}
