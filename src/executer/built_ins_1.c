/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:10:46 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 17:40:10 by ndahib           ###   ########.fr       */
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
		arr = ft_split(tmp->env, '=');
		if (ft_strcmp(arr[0], "_") != 0)
		{
			if (arr[1] == NULL)
				printf("declare -x %s\n", arr[0]);
			else
				printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		}
		tmp = tmp->next;
		free_double_pointer(arr);
	}
}

int	my_export(t_env ***lst, char **args)
{
	char	**splited_args;
	int		check;
	int		i;

	i = 0;
	if (args[0] == NULL)
		return (print_export_lst(**lst), 0);
	while (args[i] != NULL)
	{
		splited_args = ft_split(args[i], '=');
		if (check_if_quotes_exist(&args[i]) != 0)
		{
			ft_putstr_fd("minshell: not a valid identifier\n", 2);
			free_double_pointer(splited_args);
			return (1);
		}
		check = check_if_exist(*lst, splited_args);
		if (check == 0)
			add_at_end_export(lst, create_node(args[i]));
		free_double_pointer(splited_args);
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
		free_node(head);
		return ;
	}
	while (head != NULL)
	{
		if (head->next != NULL
			&& ft_strncmp(head->next->env, arg, ft_strlen(arg)) == 0
			&& len_of_var(head->next->env) == (int)ft_strlen(arg))
		{
			freed = head->next;
			head->next = head->next->next;
			free_node(freed);
			break ;
		}
		head = head->next;
	}
}

int	search(char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//==================================ENV======================================//
int	my_env(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (search(tmp->env, '='))
			printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
	return (0);
}
