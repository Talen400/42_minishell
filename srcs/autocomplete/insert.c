/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:10:01 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 11:34:39 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/autocomplete.h"

void	get_path_commands(t_autocomplete *ac, const char *text)
{
	char	*path_env;
	char	**dir;
	int		len;
	int		i;

	path_env = getenv("PATH");
	if (!path_env || !ac || !text)
		return ;
	dir = ft_split(path_env, ':');
	len = ft_strlen(text);
	i = 0;
	while (dir[i])
	{
		scan_dir(ac, dir[i], text, len);
		i++;
	}
	i = 0;
	while (dir[i])
		free(dir[i++]);
	free(dir);
}

void	add_builtins(t_autocomplete *ac, const char *text)
{
	static char	*builtins[] = {
		"cd",
		"pwd",
		"export",
		"env",
		"exit",
		"unset"
	};
	size_t		max;
	size_t		i;
	int			len;

	if (!ac || !text)
		return ;
	max = sizeof(builtins) / sizeof(char *);
	len = ft_strlen(text);
	i = 0;
	while (i < max)
	{
		if (ft_strncmp(builtins[i], text, len) == 0)
			add_match(ac, builtins[i]);
		i++;
	}
}
