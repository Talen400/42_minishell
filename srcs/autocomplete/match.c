/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:28:18 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 11:26:51 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/autocomplete.h"

static void	*realloc_safe(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	copy_size = new_size;
	if (old_size < new_size)
		copy_size = old_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

void	add_match(t_autocomplete *ac, const char *match)
{
	char	**new_matches;
	size_t	old_size;

	if (!ac || !match)
		return ;
	if (ac->count >= ac->capacity)
	{
		old_size = ac->capacity * sizeof(char *);
		ac->capacity *= 2;
		new_matches = realloc_safe(ac->matches, old_size,
				ac->capacity * sizeof(char *));
		ac->matches = new_matches;
	}
	ac->matches[ac->count] = ft_strdup(match);
	if (ac->matches[ac->count])
		ac->count++;
}

int	match_exists(t_autocomplete *ac, const char *cmd)
{
	int		i;
	size_t	len;

	if (!ac || !cmd)
		return (0);
	i = 0;
	while (i < ac->count)
	{
		len = ft_strlen(ac->matches[i]);
		if (ac->matches[i] && ft_strncmp(cmd, ac->matches[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}
