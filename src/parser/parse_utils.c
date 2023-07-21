/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:50:38 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/21 16:57:54 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*obtain_path(char *command, t_env *env_list)
{
	char	**split_paths;
	char	*right_path;
	char	*cursor;
	int		i;

	i = 0;
	cursor = my_getenv(env_list, "PATH");
	if (cursor == NULL)	
		return (free(cursor), NULL);
	split_paths = ft_split(cursor, ':');
	free(cursor);
	while (split_paths[i] != NULL)
	{
		right_path = ft_joinchar(ft_strdup(split_paths[i]), '/');
		cursor = ft_strjoin(right_path, command);
		if (access(cursor, X_OK) != -1)
		{
			free(cursor);
			cursor = ft_joinchar(ft_strdup(split_paths[i]), '/');
			cursor = ft_strjoin(cursor, command);
			free_double_pointer(split_paths);
			return (cursor);
		}
		else if (access(command, X_OK) != -1)
		{
			free(cursor);
			free_double_pointer(split_paths);
			return (command);
		}
		free(cursor);
		i++;
	}
	free_double_pointer(split_paths);
	return (NULL);
}
