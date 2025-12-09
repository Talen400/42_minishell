/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:26:15 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/09 17:02:39 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"

int		exec_cmd(t_ast_node *node, t_data *data);
char	**convert_expandable(t_expandable_value **values);
void	free_splitted(char **splitted);

#endif
