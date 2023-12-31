/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 07:59:58 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 20:12:55 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_at_end_cmd(t_simple_cmd **head, t_simple_cmd *node)
{
	t_simple_cmd	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}

char	**obtain_args(char	**token, t_env *env_var)
{
	char	**args;
	int		len;
	int		j;

	j = 0;
	len = token_nbr(token);
	if (len == 0)
		return (NULL);
	args = malloc((len + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	while (j < len && token[j] != NULL)
	{
		while ((ft_strchr(token[j], '>') != NULL
				|| ft_strchr(token[j], '<') != NULL) && token[j + 1] != NULL)
			token += 2;
		if (token[j] == NULL || *token[j] == '|')
			return (NULL);
		args[j] = ft_strdup(token[j]);
		j++;
	}
	args[j] = NULL;
	args = expander(env_var, args);
	return (args);
}

char	*obtain_cmd(char **token)
{
	char	*cmd;

	cmd = NULL;
	if (token == NULL || *token == NULL)
		return (NULL);
	if ((**token == '>' || **token == '<')
		&& *(token + 1) == NULL)
		return (NULL);
	while ((**token == '>' || **token == '<')
		&& *(token + 1) != NULL)
	{
		if (*(token + 2) != NULL)
			token += 2;
		else
			return (NULL);
	}
	if (*token != NULL)
		cmd = ft_strdup(*token);
	return (cmd);
}

t_simple_cmd	*create_node_cmd(t_env *env_var, char ***token)
{
	t_simple_cmd	*node;

	node = malloc(1 * sizeof(t_simple_cmd));
	if (!node)
	{
		ft_putstr_fd(ALLOC_ERR, 2);
		return (NULL);
	}
	node->fd = -1;
	node->arg = obtain_args(*token, env_var);
	node->cmd = obtain_cmd(node->arg);
	node->path = obtain_path(node->cmd, env_var);
	node->files = obtain_files(token, &node, env_var);
	node->next = NULL;
	return (node);
}

t_simple_cmd	*parse_simple_cmd(t_env *env_lst, char **token)
{
	t_simple_cmd	*lst_of_cmd;
	t_simple_cmd	*node_cmd;

	lst_of_cmd = NULL;
	node_cmd = NULL;
	while (*token != NULL)
	{
		if (mini_error == 1)
			break ;
		if (strchr(*token, '|') == NULL)
		{
			node_cmd = create_node_cmd(env_lst, &token);
			if (node_cmd == NULL)
				return (NULL);
			add_at_end_cmd(&lst_of_cmd, node_cmd);
		}
		else
			token++;
	}
	return (lst_of_cmd);
}
