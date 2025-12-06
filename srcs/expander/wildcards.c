/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:02:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/06 15:42:41 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char ) s1[i] - (unsigned char ) s2[i]);
}

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = -1;
		while (split[++i])
			free(split[i]);
		free(split);
	}
}

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
/*
 
 *
 * 
 * Previuos version:
 *

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
		{
			ft_printf("%s \n", dir_entry->d_name);
			len++;
		}
		dir_entry = readdir(dir);
	}
	ft_printf("%d \n", len);
	closedir(dir);
	res = ft_calloc(len + 1, sizeof(char *));
	return (res);
}
*/

/*
 *  
 *  It recursively the patterns separated by "/"
 *	
 *
 */

void	*get_wildcards_value_recursive(char *path, char **parts)
{
	struct dirent	*dir_entry;
	struct stat		st;
	DIR				*dir;
	char			*sub_path;
	char			*tmp;
	char			*match_path;

	dir = opendir(path);
	while ((dir_entry = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(dir_entry->d_name, ".")
				|| !ft_strcmp(dir_entry->d_name, ".."))
			continue ;
		if (match_pattern(dir_entry->d_name, parts[0]))
		{
			if (parts[1] == NULL)
			{
				match_path = ft_strjoin(path, "/");
				tmp = ft_strjoin(match_path, dir_entry->d_name);
				free(match_path);
				ft_printf("%s\n", tmp);
				free(tmp);
			}
			else
			{
				sub_path = ft_strjoin(path, "/");
				tmp = ft_strjoin(sub_path, dir_entry->d_name);
				free(sub_path);
				sub_path = tmp;
				if (stat(sub_path, &st) == 0 && S_ISDIR(st.st_mode))
					get_wildcards_value_recursive(sub_path, parts + 1);
				free(sub_path);
			}
		}
	}
	closedir(dir);
	return (NULL);
}

void	*wildcard(char *pattern)
{
	char	**parts;

	parts = ft_split(pattern, '/');
	get_wildcards_value_recursive(".", parts);
	free_split(parts);
	return (NULL);
}
