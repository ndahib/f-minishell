/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:50:38 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 14:32:49 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_check(char *split_path, char *command)
{
	char	*cursor;
	char	*right_path;

	right_path = ft_joinchar(ft_strdup(split_path), '/');
	cursor = ft_strjoin(right_path, command);
	if (access(cursor, X_OK) != -1)
	{
		free(cursor);
		cursor = ft_joinchar(ft_strdup(split_path), '/');
		cursor = ft_strjoin(cursor, command);
		return (cursor);
	}
	else if (access(command, X_OK) != -1)
	{
		free(cursor);
		return (command);
	}
	free(cursor);
	return (NULL);
}

char	*obtain_path(char *command, t_env *env_list)
{
	char	**split_paths;
	char	*cursor;
	int		i;

	i = 0;
	if (command == NULL)
		return (NULL);
	cursor = my_getenv(env_list, "PATH");
	if (cursor == NULL)
		return (free(cursor), NULL);
	split_paths = ft_split(cursor, ':');
	free(cursor);
	while (split_paths[i] != NULL)
	{
		cursor = join_and_check(split_paths[i], command);
		if (cursor != NULL)
		{
			free_double_pointer(split_paths);
			return (cursor);
		}
		i++;
	}
	free_double_pointer(split_paths);
	return (NULL);
}

char	*name_of_file(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '"'))
		return (NULL);
	else
		return (ft_strdup(token));
}
