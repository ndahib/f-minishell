/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:40:56 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/23 19:44:42 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_env(t_env *envr)
{
	t_env	*head;
	int		i;

	i = 0;
	head = envr;
	while (head != NULL)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	check_is_nbr(char *arg)
{
	if (arg == NULL)
		return (1);
	while (*arg != '\0')
	{
		if (ft_isdigit(*arg) == 0)
			return (1);
		arg++;
	}
	return (0);
}

void	my_free1(char *p, char **args)
{
	int	i;

	i = 0;
	free(p);
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	old_pwd(t_env **env)
{
	char	oldpwd[4096];
	t_env	*head;

	head = *env;
	getcwd(oldpwd, 4096);
	while (head)
	{
		if (ft_strncmp("OLDPWD", head->env, 6) == 0)
		{
			head->env = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(oldpwd));
			break ;
		}
		head = head->next;
	}
}

void	new_pwd(t_env **env)
{
	char	newpwd[4096];
	t_env	*head;

	head = *env;
	getcwd(newpwd, 4096);
	while (head)
	{
		if (ft_strncmp("PWD", head->env, 3) == 0)
		{
			head->env = ft_strjoin(ft_strdup("PWD="), ft_strdup(newpwd));
			break ;
		}
		head = head->next;
	}
}
