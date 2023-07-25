/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:40:56 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/25 19:59:46 by ndahib           ###   ########.fr       */
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
	char	*oldpwd;
	t_env	*head;
	char	*tmp;

	head = *env;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return ;
	while (head)
	{
		if (ft_strncmp("OLDPWD", head->env, 6) == 0)
		{
			free(head->env);
			head->env = NULL;
			tmp = ft_strdup("OLDPWD=");
			head->env = ft_strjoin(tmp, oldpwd);
			free(oldpwd);
			break ;
		}
		head = head->next;
	}
}

void	new_pwd(t_env **env)
{
	char	*newpwd;
	t_env	*head;
	char	*tmp;

	head = *env;
	newpwd = getcwd(NULL, 0);
	while (head)
	{
		if (ft_strncmp("PWD", head->env, 3) == 0)
		{
			free(head->env);
			head->env = NULL;
			tmp = ft_strdup("PWD=");
			head->env = ft_strjoin(tmp, newpwd);
			free(newpwd);
			break ;
		}
		head = head->next;
	}
}
