/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:18:30 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/24 00:42:32 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_cursor(char **new_arg, char *cursor)
{
	while (*cursor != 0)
	{
		if ((*cursor == ' ' || *cursor == '\t') && *cursor++)
			*new_arg = ft_joinchar(*new_arg, '\2');
		else
			*new_arg = ft_joinchar(*new_arg, *cursor++);
	}
}

void	join_and_increment(char **new_arg, char **arg)
{
	while (**arg != '\0')
	{
		*new_arg = ft_joinchar(*new_arg, **arg);
		(*arg) += 1;
	}
}

void	expande_inside_quotes(char **new_arg, char **arg, t_env *env)
{
	char	*cursor;
	char	*value;

	cursor = my_getenv(env, ft_substr(*arg, 1, len_of_var(*arg + 1)));
	value = ft_strjoin("", cursor);
	free(cursor);
	cursor = ft_strdup(value);
	if (ft_strlen(cursor) != 0)
	{
		*new_arg = ft_strjoin(*new_arg, ft_strdup(cursor));
		free(cursor);
	}
	else if (*(*arg + 1) == '?')
	{
		*new_arg = ft_strjoin(*new_arg, ft_itoa(g_exit_status));
		(*arg) += 2;
	}
	else
		*new_arg = ft_joinchar(*new_arg, **arg);
	if (*arg != 0)
		*arg += len_of_var(*arg + 1) + 1;
	if (ft_strlen(value) != 0)
		free (value);
}
