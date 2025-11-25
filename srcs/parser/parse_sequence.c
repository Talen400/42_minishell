/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:42:57 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/24 20:46:20 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast_node	*parse_sequence(t_parser *parser)
{
	t_parser_rule	rule;

	rule.node_type = NODE_SEQ;
	rule.token_type = TOKEN_SQUOTE; // deveria ser ;
	rule.next_function = parse_logical;
	return (parse_generic(parser, &rule, parse_logical));
}
