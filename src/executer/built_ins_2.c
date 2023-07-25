/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:04:04 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/25 15:25:31 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_with_par(char *args)
{
	int	j;

	j = 0;
	if (args == NULL)
		return (0);
	if (args[j] == '-')
	{
		j++;
		while (args[j])
		{
			if (args[j] != 'n')
				return (0);
			j++;
		}
	}
	else
		return (0);
	return (1);
}

int	my_echo(char **ptr)
{
	int	i;
	int	on;

	i = 1;
	on = 0;
	if (*ptr == NULL)
	{
		printf("\n");
		return (0);
	}
	while (echo_with_par(ptr[i]))
	{
		on = 1;
		i++;
	}
	while (ptr[i])
	{
		printf("%s", ptr[i]);
		if (ptr[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (on == 0)
		printf("\n");
	return (0);
}

/// freee before exit 
void	my_exit(char **arg)
{
	int	i;
	int	nbr;

	i = 1;
	while (arg[i])
		i++;
	if (i < 2)
		exit(g_exit_status);
	if (check_is_nbr(arg[1]) == 1)
	{
		printf(OUT_OF_RANGE, arg[1]);
		g_exit_status = 255;
		exit(g_exit_status);
	}
	else if (i > 2)
	{
		g_exit_status = 1;
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	nbr = ft_atoi(arg[1]);
	if (nbr < 0 || nbr > 255)
		exit(nbr % 256);
	exit(nbr);
}

int	my_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (1);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	return (0);
}

int	my_cd(t_simple_cmd *cmnd, t_env **env)
{
	char	*home;

	old_pwd(env);
	if (cmnd->arg[1] == NULL)
	{
		home = my_getenv(*env, "HOME");
		if (home == NULL)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		if (!chdir(home))
			return (new_pwd(env), 0);
		else
			return (perror("minishell :"), 1);
	}
	if (!chdir(cmnd->arg[1]))
		return (new_pwd(env), 0);
	else
		return (perror("minishell :"), 1);
}
