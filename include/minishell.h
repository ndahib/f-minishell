/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraiss <yraiss@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:10:39 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/25 01:08:07 by yraiss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "include.h"

//************************EXIT_STATUS_GLOBAL***********************************
int	g_exit_status;
//**********************FUNCTIONS**********************************************

////////////////////////UTILS//////////////////////////////////////////////////
t_env	*handle_env(char **env);
t_env	*create_node(char *env);
int		main(int ac, char **av, char **env);

///////////////////////FREE_UTILS//////////////////////////////////////////////
void	free_double_pointer(char **pointer);
void	free_lst_of_cmd(t_simple_cmd **cmds, int trigger);

#endif