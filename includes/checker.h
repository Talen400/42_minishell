/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:39:51 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/14 19:39:54 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "lexer.h"

// checker_syntax.c
int	print_syntax_error(char *token);

// helpers.c
int	is_word(int type);
int	is_logical_or_pipe(int type);
int	is_redirect(int type);

// utils.c
int	check_operator_syntax(t_token *tmp);
int	check_subshell_syntax(t_token *tmp, t_token *prev);
int	update_depth(int type, int *depth);
#endif
