/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:00:16 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 11:37:12 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "../../includes/autocomplete.h"

void	scan_dir(t_autocomplete *ac, const char *dir, const char *text,
			int len)
{
	DIR				*d;
	struct dirent	*entry;

	d = opendir(dir);
	if (!d)
		return ;
	entry = readdir(d);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, text, len) == 0)
		{
			if (!match_exists(ac, entry->d_name))
				add_match(ac, entry->d_name);
		}
		entry = readdir(d);
	}
	closedir(d);
}
