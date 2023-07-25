/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:04:04 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/25 21:07:00 by ndahib           ###   ########.fr       */
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

void	my_exit(char **arg, t_simple_cmd *cmd, t_env **lst)
{
	int	count;

	count = 0;
	while (arg && arg[count])
		count++;
	if (arg[1] && check_is_nbr(arg[1]) == 1)
	{
		printf(OUT_OF_RANGE, arg[1]);
		g_exit_status = 255;
	}
	else if (count > 2)
	{
		g_exit_status = 1;
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	else
		g_exit_status = ft_atoi(arg[1]);
	free_lst_of_cmd(&cmd);
	free_lst_env(lst);
	exit(g_exit_status);
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
		{
			free(home);
			return (new_pwd(env), 0);
		}
		else
		{
			free(home);
			return (perror("minishell :"), 1);
		}
	}
	if (!chdir(cmnd->arg[1]))
		return (new_pwd(env), 0);
	else
		return (perror("minishell :"), 1);
}
