/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:30:56 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/23 18:40:09 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node(char *env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->env = env;
	node->next = NULL;
	return (node);
}

void	add_at_end_env(t_env **head, t_env *node)
{
	t_env	*tmp;

	tmp = *head;
	if (*head == NULL || head == NULL)
		*head = node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	add_at_end_export(t_env ***head, t_env *node)
{
	t_env	*tmp;

	tmp = **head;
	if (**head == NULL || *head == NULL)
		**head = node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_env	*handle_env(char **env)
{
	t_env	*lst_of_env;

	lst_of_env = NULL;
	while (*env != NULL)
	{
		add_at_end_env(&lst_of_env, create_node(*env));
		env++;
	}
	return (lst_of_env);
}
