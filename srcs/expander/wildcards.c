/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:02:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/03 16:40:24 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/minishell.h"

static int	match_pattern(char *str, char *pattern)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		while (*str != '\0')
		{
			if (match_pattern(str, pattern + 1))
				return (1);
			str++;
		}
		return (match_pattern(str, pattern + 1));
	}
	if (*str == *pattern)
		return (match_pattern(str + 1, pattern + 1));
	return (0);
}

char	**get_wildcards_value(char *pattern)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	int				len;
	char			**res;
	
	dir = opendir(".");
	dir_entry = readdir(dir);
	len = 0;
	while (dir_entry)
	{
		if (match_pattern(dir_entry->d_name, pattern))
			len++;
		dir_entry = readdir(dir);
	}
	closedir(dir);
	res = ft_calloc(len + 1, sizeof(char *));
	return (res);
}
