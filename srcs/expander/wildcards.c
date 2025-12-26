/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:13:35 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/26 04:30:54 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	*get_wildcards_value_recursive(char *path, char **parts, char **value);

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
 *  It recursively the patterns separated by "/"
 *	
 *
 */

static void	handle_wildcard_match(char *path, char *name, char **parts,
		char **value)
{
	struct stat	st;
	char		*full_path;

	full_path = join_free(ft_strjoin(path, "/"), ft_strdup(name));
	if (!parts[1])
	{
		*value = join_free(*value, ft_strdup(" "));
		*value = join_free(*value, ft_strdup(full_path));
	}
	else if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode))
		get_wildcards_value_recursive(full_path, parts + 1, value);
	free(full_path);
}

void	*get_wildcards_value_recursive(char *path, char **parts, char **value)
{
	struct dirent	*dir_entry;
	DIR				*dir;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	dir_entry = readdir(dir);
	while (dir_entry != NULL)
	{
		if (ft_strcmp(dir_entry->d_name, ".") != 0
			|| ft_strcmp(dir_entry->d_name, "..") != 0)
		{
			if (match_pattern(dir_entry->d_name, parts[0]))
				handle_wildcard_match(path, dir_entry->d_name, parts, value);
		}
		dir_entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*get_path(char *pattern)
{
	char	*last_slash;
	char	*path;
	int		path_len;

	if (!pattern)
		return (ft_strdup(""));
	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (ft_strdup(""));
	path_len = last_slash - pattern + 1;
	path = ft_calloc(path_len + 1, sizeof(char));
	ft_memcpy(path, pattern, path_len);
	return (path);
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
