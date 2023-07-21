/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:40:38 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/21 01:44:31 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_double_pointer(char **arr)
{
	if (arr == NULL)
		return ;
	while (*arr != NULL)
	{
		printf(RED"THE argument :%s\n", *arr);
		arr++;
	}
}

int	len_of_var(char *var)
{
	int	count;

	count = 0;

	if (*var == '$')
		return (0);
	while (*var)
	{
		if (ft_isdigit(*var) == 0 && ft_isalpha(*var) == 0 && *var != '_')
			break;
		count++;
		var++;
	}
	return (count);
}

void	print_lst(t_files *lst)
{
	t_files	*head;

	if (lst == NULL)
		return ;
	head = lst;
	while (head != NULL)
	{
		printf("name of file :%s--> type of file:%d\n", head->file, head->type);
		head = head->next;
	}
}

int	token_nbr(char **token)
{
	int	count;
	int	on;

	count = 0;
	on = 0;
	while (*token != NULL && **token != '|')
	{
		if (**token == '>' || **token == '<')
		{
			on += 1;
		}
		count++;
		token++;
	}
	return (count - on);
}

int	len_of_word(const char *line, char sep)
{
	int	count;

	count = 0;
	if (line == NULL)
		return (0);
	while (*line != '\0')
	{
		line++;
		count++;
		if (*line == '\0' || *line == sep)
			break ;
	}
	if (*line == sep)
		count++;
	return (count);
}

char	*skip_space(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

void	free_files(t_files *files)
{
	if (files == NULL)
		return ;
	else
	{
		while (files != NULL)
		{
			free(files->file);
			files = files->next;
		}
	}
}

void	free_lst_of_cmd(t_simple_cmd **head)
{
	while (*head != NULL)
	{
		free((*head)->cmd);
		free((*head)->path);
		free_double_pointer((*head)->arg);
		free_files((*head)->files);
		(*head) = (*head)->next;		
	}
}
