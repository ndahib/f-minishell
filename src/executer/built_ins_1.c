/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:10:46 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/23 19:33:03 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//====================ENVIRENMENT VARIABLE BUILT_INS=========================//
///////////////////////////////////////////////////////////////////////////////
//==================================EXPORT===================================//
void	print_export_lst(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->env, EXPORT_VAR, 47) != 0)
			printf("declare -x %s\n", tmp->env);
		tmp = tmp->next;
	}	
}

void	my_export(t_env ***lst, char **args)
{
	char	**splited_args;

	if (*args == NULL)
	{
		print_export_lst(**lst);
		return ;
	}
	while (*args != NULL)
	{
		splited_args = ft_split(*args, '=');
		if (check_if_quotes_exist(args) != 0)
		{
			printf("minshell: not a valid identifier\n");
			return ;
		}
		if (check_if_exist(*lst, splited_args) == 0)
		{
			add_at_end_export(lst, create_node(*args));
			free_double_pointer(splited_args);
		}
		args++;
	}
}

//==================================UNSET====================================//
void	unset_variable(t_env ***lst, char *arg)
{
	t_env	*head;
	t_env	*freed;

	head = **lst;
	if (**lst == NULL || *lst == NULL)
		return ;
	if (ft_strncmp(head->env, arg, ft_strlen(arg)) == 0)
	{
		**lst = head->next;
		free(head);
		return ;
	}
	while (head != NULL)
	{
		if (head->next != NULL
			&& ft_strncmp(head->next->env, arg, ft_strlen(arg)) == 0)
		{
			freed = head->next;
			head->next = head->next->next;
			free(freed);
		}
		head = head->next;
	}
}

//==================================ENV======================================//
void	my_env(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->env, '=') != NULL)
			printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
}
