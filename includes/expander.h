/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:54:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/17 15:23:12 by tlavared         ###   ########.fr       */
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

/*
 * i = pointer of str;
 * j = num temp;
 */

typedef struct s_automato_expander
{
	char	*str;
	char	*tmp;
	int		i;
	int		j;
	int		state;
	int		prev_state;
	int		(*table)[NUM_TYPE_EXPANDER];
}	t_automato_expander;

enum e_char_type_expanser
{
	LETTER_EXPANSER,
	D_QUOTE_EXPANSER, // "
	S_QUOTE_EXPANSER, // '
	DOLLAR_EXPANSER, // $
	OPEN_PAR_EXPANSER,
	CLOSE_PAR_EXPANSER,
	WILDCARD_EXPANSER, // *
	NUl,
};

// expander.c
void	expand_ast(t_ast_node *root, t_data *data);

// wilcard.c
char	*wildcard(char *pattern);

// table_driven_expander.c
int	get_char_type_expander(char c);

// automato_expander.c
int	ft_is_expander(t_expandable_value *value, t_data *data);

// table_driven_expander.c
int	get_state_expander(t_automato_expander *aut, char character);

#endif
