/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:21:46 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/08 12:17:32 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "data.h"

int					pwd(char **args, t_data *data);
typedef int			(*t_builtin_cmd)(char **args, t_data *data);
t_builtin_cmd		get_builtin(char *cmd);
int					echo(char **args, t_data *data);
int					cd(char **args, t_data *data);

typedef struct s_dict_builtin {
	char			*id;
	t_builtin_cmd	function;
}					t_dict_builtin;

#endif
