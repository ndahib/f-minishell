/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraiss <yraiss@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:03:39 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/25 23:54:48 by yraiss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char **tokens, char *fix)
{
	if (ft_strncmp(fix, "|", 1) == 0
		|| (*(tokens + 1) && ft_strncmp(*tokens, *(tokens + 1), 1) == 0)
		|| *(tokens + 1) == NULL)
	{
		ft_putstr_fd(PARSE_ERR, 2);
		ft_putstr_fd(*tokens, 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}

int	check_redirection(char **tokens)
{
	if (*(tokens + 1) == NULL)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (1);
	}
	else if (*(tokens + 1) != NULL)
	{
		if (check_file_name(*tokens, *(tokens + 1)) == 1)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (1);
		}
	}
	return (0);
}

int	check_quotes(char **tokens)
{
	int	i;

	i = 0;
	if (*tokens[i] == '"')
	{
		if (check_syntax_error(tokens, '"') == 1)
			return (1);
	}
	else if (*tokens[i] == '\'')
	{
		if (check_syntax_error(tokens, '\'') == 1)
			return (1);
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
			if (check_redirection(tokens) == 1)
				return (1);
		}
		else if ((*tokens)[0] == '"' || (*tokens)[0] == '\'')
		{
			if (check_quotes(tokens) == 1)
				return (1);
		}
		tokens++;
	}
	return (0);
}
