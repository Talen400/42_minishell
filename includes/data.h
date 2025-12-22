/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:04:07 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/19 15:40:32 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_data {
	char	**envvars;
	char	*user;
	char	*prompt;
	int		is_running;
	int		exit_status;
}	t_data;

int		init_data(t_data *data, char **envvars);
void	delete_env(t_data *data, char *key);
void	update_env(t_data *data, char *key, char *new_value);
void	clear_data(t_data *data);
void	init_readline_completion(void);

#endif
