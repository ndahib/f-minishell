/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 08:07:55 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 14:32:36 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_pointer(char **pointer)
{
	int	i;

	i = 0;
	if (pointer == NULL)
		return ;
	while (pointer[i] != NULL)
	{
		free(pointer[i]);
		pointer[i] = NULL;
		i++;
	}
	free (pointer);
}

void	free_files(t_files **files)
{
	t_files	*tmp;
	t_files	*tmp2;

	tmp = *files;
	if (files == NULL || *files == NULL)
		return ;
	while (tmp != NULL)
	{
		free(tmp->file);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}

void	free_lst_of_cmd(t_simple_cmd **head)
{
	t_simple_cmd	*tmp;
	t_simple_cmd	*tmp2;

	tmp = *head;
	while (tmp != NULL)
	{
		free(tmp->cmd);
		if (tmp->cmd != tmp->path)
			free(tmp->path);
		free_double_pointer(tmp->arg);
		free_files(&tmp->files);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}

void	free_lst_env(t_env **lst)
{
	while (*lst)
	{
		free((*lst)->env);
		(*lst) = (*lst)->next;
	}
}

void	free_node(t_env *head)
{
	if (head == NULL)
		return ;
	free(head->env);
	free(head);
}
