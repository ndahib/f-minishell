/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:04:04 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/22 10:29:52 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_with_par(char *args)
{
	int	j;

	j = 0;
	if (args== NULL)
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

void my_echo(char **ptr)
{
	int i;
	int on;

	i = 1;
	on = 0;
	if (*ptr == NULL)
	{
		printf("\n");
		return ;
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
	
}

//free before exeting in exit
void	my_exit(char **arg)
{
	int	i;
	int	nbr;

	i = 0;
	while (arg[i] != NULL)
		i++;
	if (i > 2)
		return ;
	if (check_is_nbr(arg[1]) == 1)
	{
		printf(OUT_OF_RANGE, arg[1]);
		exit(255); // sauvegarde that and d'ont exit
		return ;
	}
	if (arg[1] == NULL)
		exit(0);
	nbr = ft_atoi(arg[1]);
	if (nbr < 0 || nbr > 255)
		exit(nbr % 256);
	exit(nbr);
}

void	my_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return ;
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
}

int	my_cd(t_simple_cmd *cmnd, t_env **env)
{
	old_pwd(env);
	if (cmnd->arg[1] == NULL)
	{
		if (!chdir(getenv("HOME")))
			return (new_pwd(env), 1);
		else
			return (perror("minishell :"), 0);
	}
	if (!chdir(cmnd->arg[1]))
		return (new_pwd(env), 1);
	else
		return (perror("minishell :"), 0);
}

int	check_is_built_ins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (0);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (0);
	return (1);
}

int	is_built_ins(t_env **lst, t_simple_cmd *cmd)
{
	int	i;
	int	std_fd[2];

	i = 1;
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (cmd->cmd == NULL)
		return (1);
	if (redirections(cmd->files) == 1)
		exit(EXIT_FAILURE);
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		my_echo(cmd->arg);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		my_cd(cmd, lst);
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		my_env(lst);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		my_pwd();
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
	{
		while ((cmd->arg[i]) != NULL)
		{
			unset_variable(&lst, cmd->arg[i]);
			i++;
		}
	}
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		my_export(&lst, cmd->arg + 1);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		my_exit(cmd->arg);
	else
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		close(std_fd[1]);
		close(std_fd[0]);
		return (1);
	}
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	close(std_fd[1]);
	close(std_fd[0]);
	return (0);
}
