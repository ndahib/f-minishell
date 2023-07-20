/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:02:42 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/19 12:29:41 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quotes(char **line, char sep)
{
	char	*quotes;
	int		len;
	int		i;

	i = -1;
	len = len_of_word(*line, sep) + 1;
	quotes = malloc(len);
	if (!quotes)
		return (NULL);
	while (++i < len - 1)
	{
		quotes[i] = **line;
		(*line)++;
	}
	quotes[i] = '\0';
	return (quotes);
}

void	handle_redir(char **split_line, char **line)
{
	if (*(*line)++ == '<')
	{
		if (**line == '<')
		{
			*split_line = ft_strjoin(*split_line, "\2<<\2");
			(*line)++;
		}
		else
			*split_line = ft_strjoin(*split_line, "\2<\2");
	}
	else
	{
		if (**line == '>')
		{
			*split_line = ft_strjoin(*split_line, "\2>>\2");
				(*line)++;
		}
		else
			*split_line = ft_strjoin(*split_line, "\2>\2");
	}
}

void	handle_quotes(char **split_line, char **line)
{
	char	*inside_quotes;

	inside_quotes = quotes(line, **line);
	*split_line = ft_strjoin(*split_line, inside_quotes);
	free (inside_quotes);
}

char	*handler(char *line)
{
	char	*split_line;

	split_line = "";
	while (*line != '\0')
	{
		if (*line == ' ' || *line == '\t')
		{
			split_line = ft_joinchar(split_line, 2);
			line = skip_space(line);
		}
		else if (*line == '|' && line++)
			split_line = ft_strjoin(split_line, "\2|\2");
		else if ((*line == '>' || *line == '<'))
			handle_redir(&split_line, &line);
		else if ((*line == '"' || *line == '\''))
		{
			handle_quotes(&split_line, &line);
			if (*line != ' ' && *line != '\t' && *line != 0)
				continue ;
			split_line = ft_joinchar(split_line, 2);
		}
		else
			split_line = ft_joinchar(split_line, *line++);
	}
	return (split_line);
}

char	**tokeniser(char *line)
{
	char	**tokens;

	line = handler(line);
	tokens = ft_split(line, 2);
	free(line);
	return (tokens);
}
