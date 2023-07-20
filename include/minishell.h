/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:10:39 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/19 18:57:25 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "include.h"
# include "messages.h"
# include "color.h"
# include "lexer.h"
# include "../libft/libft.h"
# include "parsing.h"
# include "execution.h"

//**********************FUNCTIONS************************//

//////////////////////////BUILT_INS/////////////////////////
void	my_pwd(void);
void	my_exit(char **arg);
void	my_echo(char **arg);
void	my_env(t_env **lst);
void	my_export(t_env ***lst, char **args);
void	unset_variable(t_env ***lst, char *arg);
int		my_cd(t_simple_cmd *cmnd, t_env **env);
/******************************EXECUTION*********************/
void	free_lst_of_cmd(t_simple_cmd **cmds);
void	new_pwd(t_env **env);
void	old_pwd(t_env **env);

#endif