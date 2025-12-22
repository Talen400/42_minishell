/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:02:26 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 11:07:23 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/autocomplete.h"
#include <stdlib.h>

t_autocomplete	*init_autocomplete(void)
{
	t_autocomplete	*res;

	res = (t_autocomplete *)malloc(sizeof(t_autocomplete));
	if (!res)
		return (NULL);
	res->capacity = 50;
	res->matches = malloc(sizeof(char *) * res->capacity);
	if (!res->matches)
	{
		free(res);
		return (NULL);
	}
	res->count = 0;
	return (res);
}

void	init_readline(void)
{
	rl_attempted_completion_function = command_completion;
}

void	free_autocomplete(t_autocomplete *ac)
{
	int	i;

	if (!ac)
		return ;
	i = 0;
	while (i < ac->count)
		free(ac->matches[i++]);
	free(ac->matches);
	free(ac);
}
