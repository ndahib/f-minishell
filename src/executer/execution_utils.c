/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:52:52 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 19:50:11 by ndahib           ###   ########.fr       */
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
			env_arr[i] = ft_strdup(env->env);
		i++;
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	wait_childs(int nbr)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbr)
	{
		wait(&status);
		if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status) + 128;
		else if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}

int	check_redir(t_files *files)
{
	if (files != NULL)
	{
		if (redirections(files) == 1)
		{
			g_exit_status = 1;
			return (g_exit_status);
		}
	}
	return (EXIT_SUCCESS);
}

void	dup_close(int fd)
{
	dup2(fd, 0);
	close(fd);
}
