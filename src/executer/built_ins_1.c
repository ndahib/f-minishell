/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:10:46 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/25 12:26:30 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//====================ENVIRENMENT VARIABLE BUILT_INS=========================//
///////////////////////////////////////////////////////////////////////////////
//==================================EXPORT===================================//
void	print_export_lst(t_env *lst)
{
	t_env	*tmp;
	char	**arr;

	tmp = lst;
	while (tmp != NULL)
	{
		arr = ft_split(tmp->env,'=');
		if (ft_strncmp(tmp->env, EXPORT_VAR, 50) != 0)
			printf("declare -x %s =\"%s\"\n", arr[0], arr[1]);
		tmp = tmp->next;
	}
	//free arr
}

int	my_export(t_env ***lst, char **args)
{
	char	**splited_args;
	int		i;

	i = 0;
	if (args[0] == NULL)
	{
		print_export_lst(**lst);
		return (0);
	}
	while (args[i] != NULL)
	{
		splited_args = ft_split(args[i], '=');
		if (check_if_quotes_exist(args) != 0)
		{
			printf("minshell: not a valid identifier\n");
			return (1);
		}
		if (check_if_exist(*lst, splited_args) == 0)
		{
			add_at_end_export(lst, create_node(args[i]));
			free_double_pointer(splited_args);
		}
		i++;
	}
	return (0);
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
int	my_env(t_env **lst)
{
	t_env	*tmp;
	char	**splited;

	tmp = *lst;
	while (tmp != NULL)
	{
		splited = ft_split(tmp->env, '=');
		if (splited[1] != NULL)
			printf("%s\n", tmp->env);
		tmp = tmp->next;
		free_double_pointer(splited);
	}
	return (0);
}
