/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:54:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/09 21:18:47 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "data.h"
# include "parser.h"

void	expand_ast(t_ast_node *root, t_data *data);
/*
char	**get_wildcards_value(char *pattern);
*/
/*
void	*wildcard(char *pattern);
*/
char	*wildcard(char *pattern);

// quote.c
char	*quote(char *raw);

#endif
