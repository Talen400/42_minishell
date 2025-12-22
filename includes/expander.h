/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:54:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/21 19:55:17 by tlavared         ###   ########.fr       */
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
# define NUM_STATE_EXPANDER 4

/*
 * i = pointer of str;
 * j = num temp;
 */

typedef struct s_automato_expander
{
	char	*word;
	char	*tmp;
	int		len;
	int		i;
	int		j;
	int		state;
	int		prev_state;
	int		is_expand;
	int		(*table)[NUM_TYPE_EXPANDER];
}	t_automato_expander;

enum e_char_type_expanser
{
	LETTER_EXPANSER,
	D_QUOTE_EXPANSER, // "
	S_QUOTE_EXPANSER, // '
	DOLLAR_EXPANSER, // $
	OPEN_PAR_EXPANSER, // (
	CLOSE_PAR_EXPANSER, // )
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
int	is_expander(t_expandable_value *value, t_data *data);

// table_driven_expander.c
int	get_state_expander(t_automato_expander *aut, char character);

// utils_expander.c
char	*get_env_expander(t_data *data, char *str);
char	*join_free(char *s1, char *s2);
char	*append_char(char *str, char character);
char	*handle_dollar(t_automato_expander *aut, t_data *data);

// wildcard_utils.c
int	ft_strcmp(const char *s1, const char *s2);
void	free_split(char **split);

#endif
