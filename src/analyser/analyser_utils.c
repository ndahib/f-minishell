/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:11:01 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/24 00:37:33 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_name(char *token, char *name)
{
	if (ft_strncmp(">", token, 2) == 0)
	{
		if (ft_strncmp(">>", name, 3) == 0 || ft_strncmp("<", name, 2) == 0
			|| ft_strncmp("|", name, 2) == 0)
			return (1);
	}
	if (ft_strncmp(">>", token, 3) == 0)
	{
		if (ft_strncmp(">", name, 2) == 0 || ft_strncmp("<", name, 2) == 0
			|| (ft_strncmp(">>", name, 3) == 0) || !ft_strncmp("|", name, 2))
			return (1);
	}
	if (ft_strncmp("<", token, 2) == 0)
	{
		if (ft_strncmp("<<", name, 2) == 0 || ft_strncmp(">", name, 2) == 0
			|| ft_strncmp("|", name, 2) == 0)
			return (1);
	}
	if (ft_strncmp("<<", token, 2) == 0)
	{
		if (ft_strncmp("<", name, 2) == 0 || ft_strncmp(">", name, 2) == 0
			|| ft_strncmp("<<", name, 3) == 0 || ft_strncmp("|", name, 2) == 0)
			return (1);
	}
	return (0);
}

int	nbr_of_quotes(char *token, char quote)
{
	int	i;

	i = 0;
	while (*token != '\0')
	{
		if (*token == quote)
			i++;
		token++;
	}
	return (i);
}

int	check(char *token, char quote)
{
	int	i;

	i = 0;
	while (token[i] != quote)
	{
		if (token[i + 1] == '\0' && token[i] == quote)
		{
			printf(RED PARSE_ERR"`'`\n");
			return (1);
		}
		i++;
	}
	return (i);
}

int	check_syntax_error(char **tokens, char quot)
{
	int	i;

	i = 0;
	i = check(*tokens, quot);
	if (*tokens[i] != '\0')
	i = check(*tokens + i, quot);
	if ((nbr_of_quotes(*tokens, quot) % 2 != 0))
	{
		printf(RED "syntax error\n");
		return (1);
	}
	return (0);
}
