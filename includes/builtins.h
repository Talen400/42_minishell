/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:21:46 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/11 13:20:22 by fbenini-         ###   ########.fr       */
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
int					env(char **args, t_data *data);
int					unset(char **args, t_data *data);
int					ft_export(char **args, t_data *data);
int					ft_exit(char **args, t_data *data);

typedef struct s_dict_builtin {
	char			*id;
	t_builtin_cmd	function;
}					t_dict_builtin;

#endif
