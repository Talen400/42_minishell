/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:02:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 15:12:23 by fbenini-         ###   ########.fr       */
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

void	*get_wildcards_value_recursive(char *path, char **parts, char **value)
{
	struct dirent	*dir_entry;
	struct stat		st;
	DIR				*dir;
	char			*sub_path;
	char			*tmp;
	char			*tmp_value;
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
				tmp_value = *value;
				*value = ft_strjoin(tmp_value, " ");
				free(tmp_value);
				tmp_value = *value;
				*value = ft_strjoin(tmp_value, tmp);
				free(tmp_value);
				free(tmp);
			}
			else
			{
				sub_path = ft_strjoin(path, "/");
				tmp = ft_strjoin(sub_path, dir_entry->d_name);
				free(sub_path);
				sub_path = tmp;
				if (stat(sub_path, &st) == 0 && S_ISDIR(st.st_mode))
					get_wildcards_value_recursive(sub_path, parts + 1, value);
				free(sub_path);
			}
		}
	}
	closedir(dir);
	return (NULL);
}

char	*get_path(char *pattern)
{
	int		path_len;
	char	*file;
	char	*res;
	int		i;

	file = ft_strchr(pattern, '*');
	if (!file)
		return (ft_strdup("."));
	path_len = ft_strlen(pattern) - ft_strlen(file);
	res = ft_calloc(path_len + 1, sizeof(char));
	i = 0;
	while (i < path_len - 1)
	{
		res[i] = pattern[i];
		i++;
	}
	return (res);
}

char	*wildcard(char *pattern)
{
	char	**parts;
	char	*value;
	char	*path;
	int		path_len;

	path = get_path(pattern);
	path_len = ft_strlen(path);
	parts = ft_split(pattern + path_len, '/');
	value = ft_strdup("");
	if (path_len == 0)
	{
		free(path);
		path = ft_strdup(".");
	}
	get_wildcards_value_recursive(path, parts, &value);
	free_split(parts);
	free(path);
	return (value);
}
