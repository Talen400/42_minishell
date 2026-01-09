/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:00:24 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 11:34:05 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/autocomplete.h"
#include <readline/readline.h>

static char	*command_generator(const char *text, int state)
{
	static t_autocomplete	*ac = NULL;
	static int				idx;
	char					*match;

	if (state == 0)
	{
		if (ac)
			free_autocomplete(ac);
		ac = init_autocomplete();
		idx = 0;
		add_builtins(ac, text);
		get_path_commands(ac, text);
	}
	if (idx < ac->count)
	{
		match = ft_strdup(ac->matches[idx++]);
		return (match);
	}
	free_autocomplete(ac);
	ac = NULL;
	return (NULL);
}

char	**command_completion(const char *text, int start, int end)
{
	char	**matches;

	matches = NULL;
	(void)end;
	if (start == 0)
		matches = rl_completion_matches(text, command_generator);
	return (matches);
}
