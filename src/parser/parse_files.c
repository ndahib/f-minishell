/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:04:00 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/19 10:58:12 by ndahib           ###   ########.fr       */
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
	ft_strlcpy(redir[3], "<<", 4);
	while (i < 4)
	{
		if (ft_strncmp(**token, redir[i], ft_strlen(**token)) == 0
			&& ft_strlen(**token) == ft_strlen(redir[i]))
		{
			node = malloc(sizeof(t_files));
			if (node == NULL)
				return (NULL);
			(*token)++;
			node->file = **token;
			node->type = i + 3;
			node->next = NULL;
			return (node);
		}
		i++;
	}
	return (NULL);
}

t_files	*obtain_files(char ***token)
{
	t_files	*file_node;
	t_files	*file;

	file_node = NULL;
	file = NULL;
	while (**token != NULL && ***token != '|')
	{
		if (***token == '>' || ***token == '<')
		{
			file = create_node_files(token);
			obtain_name_and_type(&file_node, file);
		}
		(*token)++;
	}
	return (file_node);
}
