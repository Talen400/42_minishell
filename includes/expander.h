/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:54:13 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:15:37 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "data.h"
# include "parser.h"

# define NUM_TYPE_EXPANDER 8
# define NUM_STATE_EXPANDER 3

typedef struct s_automato_expander
{
	char	*word;
	char	*subshell_cmd;
	char	*tmp;
	int		len;
	int		i;
	int		state;
	int		prev_state;
	int		(*table)[NUM_TYPE_EXPANDER];
}	t_automato_expander;

enum e_char_type_expanser
{
	LETTER_EXPANSER,
	D_QUOTE_EXPANSER,
	S_QUOTE_EXPANSER,
	DOLLAR_EXPANSER,
	OPEN_PAR_EXPANSER,
	CLOSE_PAR_EXPANSER,
	WILDCARD_EXPANSER,
	NUl,
};

// expander.c
void	expand_ast(t_ast_node *root, t_data *data);

// wilcard.c
char	*wildcard(char *pattern);

// table_driven_expander.c
int		get_char_type_expander(char c);

// automato_expander.c
int		is_expander(t_expandable_value *value, t_data *data);

// table_driven_expander.c
int		get_state_expander(t_automato_expander *aut, char character);

// utils_expander.c
char	*get_env_expander(t_data *data, char *str);
char	*join_free(char *s1, char *s2);
char	*append_char(char *str, char character);
char	*handle_dollar(t_automato_expander *aut, t_data *data);

// wildcard_utils.c
void	free_split(char **split);

// subshell.c
char	*extract_subshell(t_automato_expander *aut);
char	*execute_subshell(char *cmd, t_data *data);

// helpers.c

int		skip_quote(t_automato_expander *aut);
int		is_subshell(t_automato_expander *aut);
int		is_dollar_expansion(t_automato_expander *aut);

#endif
