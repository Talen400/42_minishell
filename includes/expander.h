/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:54:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/17 13:10:38 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "data.h"
# include "parser.h"

/*
 *
 *
 * Here is experimental automato expanser
 *
 *
 */

# define NUM_TYPE_EXPANDER 8
# define NUM_STATE_EXPANDER 6

typedef struct s_automato_expander
{
	int	i;
	int	state;
	int	prev_state;
	int	str_len;
	int	(*table)[NUM_TYPE_EXPANDER];
	int	is_expand;
}	t_automato_expander;

enum e_char_type_expanser
{
	LETTER_EXPANSER,
	D_QUOTE_EXPANSER, // "
	S_QUOTE_EXPANSER, // '
	SIMPLE_VAR_EXPANSER, // $
	OPEN_PAR_EXPANSER,
	CLOSE_PAR_EXPANSER,
	WILDCARD_EXPANSER, // *
	DOLLAR_EXPANSER // $( )
};

// expander.c
void	expand_ast(t_ast_node *root, t_data *data);

// wilcard.c
char	*wildcard(char *pattern);

// table_driven_expander.c
int	get_char_type_expander(char c);

// automato_expander.c
int	ft_is_expanser(t_expandable_value *value, t_data *data);

// table_driven_expander.c
int	get_state_expander(t_automato_expander *aut, char character);

#endif
