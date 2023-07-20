/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:03:39 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/20 22:14:59 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char **tokens, char *fix)
{
	if (ft_strncmp(fix, "|", 1) == 0
		|| (*(tokens + 1) && ft_strncmp(*tokens, *(tokens + 1), 1) == 0)
		|| *(tokens + 1) == NULL)
		{
			printf(RED PARSE_ERR"`%s'\n", *tokens);
			return (1);
		}
	return (0);
}

int	check_redirection(char **tokens)
{
	if (ft_strncmp(">", *tokens, 1) == 0)
	{
		if (*(tokens + 1) != 0
			&& (ft_strncmp("<", *(tokens + 1), 1) == 0
				|| ft_strncmp("|", *(tokens + 1), 1) == 0))
		{
			printf(RED PARSE_ERR"`%s'\n", *tokens);
			return (1);
		}
	}
	else if (ft_strncmp("<", *tokens, 1) == 0)
	{
		if (*(tokens + 1) != 0
			&& (ft_strncmp(">", *(tokens + 1), 1) == 0
				|| ft_strncmp("|", *(tokens + 1), 1) == 0))
		{
			printf(RED PARSE_ERR"`%s'\n", *tokens);
			return (1);
		}
	}
	return (0);
}

int	check_quotes(char **tokens)
{
	int	i;

	i = 0;
	if ((*tokens)[0] == '"')
	{
		while ((*tokens)[i + 1] != '\0')
			i++;
		if ((*tokens)[i] != '"')
		{
			printf(RED PARSE_ERR"`\"'\n");
			return (1);
		}
	}
	else if ((*tokens)[0] == '\'')
	{
		while ((*tokens)[i + 1] != '\0')
			i++;
		if ((*tokens)[i] != '\'')
		{
			printf(RED PARSE_ERR"`'`\n");
			return (1);
		}
	}
	return (0);
}

int	check_syntax_err(char **tokens)
{
	char	*first_token;

	first_token = tokens[0];
	while (*tokens)
	{
		if (ft_strncmp(*tokens, "|", 1) == 0)
		{
			if (check_pipe(tokens, first_token) == 1)
				return (1);
		}
		else if (ft_strncmp(*tokens, ">", 1) == 0
			|| ft_strncmp(*tokens, "<", 1) == 0)
			{
				check_redirection(tokens);
				return (1);
			}
		else if ((*tokens)[0] == '"' || (*tokens)[0] == '\'')
		{
			check_quotes(tokens);
			return (1);
		}
		tokens++;
	}
	return (0);
}
