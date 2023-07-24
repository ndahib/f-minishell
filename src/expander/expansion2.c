/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:08:56 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/24 17:26:11 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	obtain_value(t_env *env, char **new_arg, char **arg)
{
	char	*value;
	char	*cursor;
	char	*sub;

	if (ft_isalpha(*(*arg + 1)) == 1 || *(*arg + 1) == '_')
	{
		sub = ft_substr(*arg, 1, len_of_var(*arg + 1));
		cursor = my_getenv(env, sub);
		free(sub);
		value = ft_strjoin("", cursor);
		free (cursor);
		cursor = value;
		if (ft_strlen(cursor) != 0)
		{
			join_cursor(new_arg, cursor);
			free(value);
		}
		*arg += len_of_var(*arg + 1) + 1;
	}
	else if (*(*arg + 1) == '?')
	{
		char	*exit;
		exit = ft_itoa(g_exit_status);
		*new_arg = ft_strjoin(*new_arg, exit);
		free(exit);
		(*arg) += 2;
	}
	else if (*arg + 1 != NULL)
		join_and_increment(new_arg, arg);
}

void	print_inside_dquotes(t_env *env, char **new_arg, char **arg)
{
	while (**arg != '"' && *(*arg + 1) != '\0')
	{
		if (**arg == '$')
			expande_inside_quotes(new_arg, arg, env);
		else
			*new_arg = ft_joinchar(*new_arg, *(*arg)++);
	}
	(*arg)++;
}

char	*single_quotes(char **line)
{
	char	*quotes;
	int		len;
	int		i;

	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\'')
			break ;
		i++ ;
	}
	len = i + 1;
	quotes = malloc(len);
	if (!quotes)
		return (NULL);
	i = -1;
	while (++i < len - 1)
	{
		quotes[i] = **line;
		(*line)++;
	}
	quotes[i] = '\0';
	return (quotes);
}

char	*expand_line(t_env *env, char *arg)
{
	char	*new_arg;
	char	*s_quotes;

	new_arg = "";
	while (*arg != '\0')
	{
		if ((*arg == ' ' || *arg == '\t') && *arg++)
			new_arg = ft_joinchar(new_arg, 2);
		else if (*arg == '\'' && *arg++)
		{
			s_quotes = single_quotes(&arg);
			new_arg = ft_strjoin(new_arg, s_quotes);
			free (s_quotes);
			arg++;
		}
		else if (*arg == '$' && *(arg + 1) != '\0')
			obtain_value(env, &new_arg, &arg);
		else if (*arg == '"' && *(arg + 1) != '\0' && *arg++)
			print_inside_dquotes(env, &new_arg, &arg);
		else
			new_arg = ft_joinchar(new_arg, *arg++);
	}
	return (new_arg);
}

char	**expander(t_env *env, char **arg)
{
	char	*one_line;
	char	*new_line;
	char	**splited;
	char	**tmp_for_arg;

	one_line = "";
	tmp_for_arg = arg;
	while (*arg != NULL)
	{
		one_line = ft_strjoin(one_line, *arg);
		one_line = ft_joinchar(one_line, '\2');
		arg++;
	}
	new_line = expand_line(env, one_line);
	free(one_line);
	splited = ft_split(new_line, '\2');
	free(new_line);
	free_double_pointer(tmp_for_arg);
	return (splited);
}
