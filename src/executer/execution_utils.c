/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:52:52 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/22 12:30:04 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_number_of_cmds(t_simple_cmd *cmnd)
{
	int				count;
	t_simple_cmd	*head;

	head = cmnd;
	count = 0;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**convert_env_to_array(t_env *env)
{
	int		i;
	int		count;
	char	**env_arr;

	i = 0;
	count = count_env(env);
	env_arr = malloc((count + 1) * sizeof(char *));
	if (env_arr == NULL)
		return (NULL);
	while (env != NULL && i < count)
	{
		if (env->env != NULL)
			env_arr[i] = ft_strjoin("", env->env);
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
