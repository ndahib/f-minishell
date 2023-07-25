/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yraiss <yraiss@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:40:56 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/25 01:53:15 by yraiss           ###   ########.fr       */
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
	int	i;
	
	i = 0;
	if (arg == NULL)
		return (1);
	if (arg[0] == '-')
		i++;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
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
