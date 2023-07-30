/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:04:00 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 14:25:30 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	obtain_name_and_type(t_files **files, t_files *node)
{
	t_files	*tmp;

	tmp = *files;
	if (*files == NULL || files == NULL)
		*files = node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_files	*create_node_files(char ***token)
{
	int		i;
	t_files	*node;
	char	redir[4][3];

	i = 0;
	ft_strlcpy(redir[0], "<", 2);
	ft_strlcpy(redir[1], ">", 2);
	ft_strlcpy(redir[2], ">>", 3);
	while (i < 3)
	{
		if (ft_strcmp(**token, redir[i]) == 0)
		{
			node = malloc(sizeof(t_files));
			if (node == NULL)
				return (NULL);
			(*token)++;
			node->file = name_of_file(**token);
			node->type = i + 3;
			node->next = NULL;
			return (node);
		}
		i++;
	}
	return (NULL);
}

t_files	*obtain_files(char ***token, t_simple_cmd **simple, t_env *env)
{
	t_files	*file_node;
	t_files	*file;

	file_node = NULL;
	file = NULL;
	while (**token != NULL && ***token != '|')
	{
		if (ft_strncmp(**token, "<<", 2) == 0)
		{
			if ((*simple)->fd != -1)
				close((*simple)->fd);
			(*simple)->fd = her_doc(*(*token + 1), env);
		}
		else if (***token == '>' || ***token == '<')
		{
			file = create_node_files(token);
			if (file == NULL)
				return (NULL);
			obtain_name_and_type(&file_node, file);
		}
		(*token)++;
	}
	return (file_node);
}
