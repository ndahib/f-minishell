/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:10:39 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/23 18:23:51 by ndahib           ###   ########.fr       */
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
void	free_lst_of_cmd(t_simple_cmd **cmds);

#endif