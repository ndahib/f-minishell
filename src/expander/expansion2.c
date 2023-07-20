/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:08:56 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/20 22:33:40 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	obtain_value(t_env *env, char **new_arg, char **arg)
{
	char	*value;
	char	*cursor;

	if (ft_isalpha(*(*arg + 1)) == 1 || *(*arg + 1) == '_')
	{
		cursor = my_getenv(env, ft_substr(*arg, 1, len_of_var(*arg + 1)));
		value = ft_strjoin("", cursor);
		free (cursor);
		cursor = value;
		if (ft_strlen(cursor) != 0)
		{
			while (*cursor != 0)
			{
				if ((*cursor == ' ' || *cursor == '\t') && *cursor++)
					*new_arg = ft_joinchar(*new_arg, '\2');
				else
					*new_arg = ft_joinchar(*new_arg, *cursor++);
			}
			free(value);
		}
		*arg += len_of_var(*arg + 1) + 1;
	}
	else if (*(*arg + 1) == '?')
	{
		*new_arg = ft_strjoin(*new_arg, ft_itoa(exit_status));
		(*arg) += 2;
	}
	else if (*arg + 1 != NULL)
	{
		while (**arg != '\0')
		{
			*new_arg = ft_joinchar(*new_arg, **arg);
			(*arg) += 1;
		}
	}
}

void	print_inside_dquotes(t_env *env, char **new_arg, char **arg)
{
	char	*value;
	char	*cursor;

	while (**arg != '"' && *(*arg + 1) != '\0')
	{
		if (**arg == '$')
		{
			cursor = my_getenv(env, ft_substr(*arg, 1, len_of_var(*arg + 1)));
			value = ft_strjoin("", cursor);
			free(cursor);
			cursor = value;
			if (ft_strlen(cursor) != 0)
			{
				while (*cursor != 0)
					*new_arg = ft_joinchar(*new_arg, *cursor++);
			}
			// else if (*(*arg + 1) == '?')
			// {
			// 	(*arg)++;
			// 	printf("%d", exit_status);
			// }
			else
				*new_arg = ft_joinchar(*new_arg, **arg);
			if (*arg != '\0')
				*arg += len_of_var(*arg + 1) + 1;
			if (ft_strlen(value) != 0)
				free (value);
		}
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
	char	**splited;
	char	*tmp;
	char	**tmp_for_arg;

	one_line = "";
	tmp_for_arg = arg;
	while (*arg != NULL)
	{
		one_line = ft_strjoin(one_line, *arg);
		one_line = ft_joinchar(one_line, ' ');
		arg++;
	}
	tmp = one_line;
	one_line = expand_line(env, one_line);
	// free(tmp);
	free_double_pointer(tmp_for_arg);
	splited = ft_split(one_line, '\2');
	// free(one_line);
	return (splited);
}
