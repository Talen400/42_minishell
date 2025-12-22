/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:13:51 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/22 01:36:20 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*get_env_expander(t_data *data, char *str)
{
	int		i;
	char	*res;
	size_t	len;

	i = 0;
	res = NULL;
	len = ft_strlen(str);
	while (data->envvars[i])
	{
		if (ft_strncmp(str, data->envvars[i], len) == 0
			&& data->envvars[i][len] == '=')
		{
			res = ft_strdup(data->envvars[i] + len + 1);
			return (res);
		}
		i++;
	}
	res = ft_strdup("");
	return (res);
}

char	*join_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*append_char(char *str, char character)
{
	char	*ptr;

	ptr = ft_substr(&character, 0, 1);
	return (join_free(str, ptr));
}

char	*handle_dollar(t_automato_expander *aut, t_data *data)
{
	int		start;
	int		len;
	char	*tmp;
	char	*result;

	aut->i++;
	start = aut->i;
	len = 0;
	while (aut->word[aut->i] && ((ft_isalnum(aut->word[aut->i])
				|| aut->word[aut->i] == '_')))
	{
		aut->i++;
		len++;
	}
	tmp = ft_substr(aut->word, start, len);
	if (*tmp == '\0')
		result = ft_strdup("$");
	else
		result = get_env_expander(data, tmp);
	free(tmp);
	return (result);
}
