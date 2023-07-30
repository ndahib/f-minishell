/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:10:39 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 20:10:50 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "include.h"

//************************EXIT_STATUS_GLOBAL***********************************
int	g_exit_status;
int mini_error;
//**********************FUNCTIONS**********************************************

////////////////////////UTILS//////////////////////////////////////////////////
t_env	*handle_env(char **env);
t_env	*create_node(char *env);
int		main(int ac, char **av, char **env);

///////////////////////FREE_UTILS//////////////////////////////////////////////
void	free_node(t_env *head);
void	free_lst_env(t_env **lst);
void	free_double_pointer(char **pointer);
void	free_lst_of_cmd(t_simple_cmd **cmds);

#endif