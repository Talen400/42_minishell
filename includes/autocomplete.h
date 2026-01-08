/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:01:01 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 11:21:49 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H
# include "minishell.h"

typedef struct s_autocomplete
{
	char	**matches;
	int		count;
	int		capacity;
}	t_autocomplete;

void			init_readline(void);
t_autocomplete	*init_autocomplete(void);
void			free_autocomplete(t_autocomplete *ac);

int				match_exists(t_autocomplete *ac, const char *cmd);
void			add_match(t_autocomplete *ac, const char *match);

char			**command_completion(const char *text, int start, int end);

void			scan_dir(t_autocomplete *ac, const char *dir,
					const char *text, int len);

void			add_builtins(t_autocomplete *ac, const char *text);
void			get_path_commands(t_autocomplete *ac, const char *text);

#endif
