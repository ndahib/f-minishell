/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:37:37 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/29 19:26:24 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_built_ins(char *cmd)
{
	if (cmd == NULL)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd, "env", 4) == 0)
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

void	dup_and_close(int *std_fd)
{
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	close(std_fd[1]);
	close(std_fd[0]);
}

int	other_built(t_env **lst, t_simple_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
	{
		if (my_echo(cmd->arg) == 1)
			return (1);
	}
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
	{
		if (my_cd(cmd, lst))
			return (1);
	}
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
	{
		if (my_env(lst) == 1)
			return (1);
	}
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
	{
		if (my_pwd() == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

int	builtins_exec(t_env ***lst, t_simple_cmd *cmd)
{
	int	i;

	i = 1;
	if (other_built(*lst, cmd) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
	{
		while ((cmd->arg[i]) != NULL)
		{
			unset_variable(lst, cmd->arg[i]);
			i++;
		}
	}
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
	{
		if (my_export(lst, cmd->arg + 1) == 1)
			return (1);
		else
			return (0);
	}
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		my_exit(cmd->arg, cmd, *lst);
	else
		return (1);
	return (0);
}

int	is_built_ins(t_env **lst, t_simple_cmd *cmd)
{
	int	std_fd[2];

	if (cmd->cmd == NULL)
		return (EXIT_FAILURE);
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (redirections(cmd->files) == 1)
		return (1);
	if (builtins_exec(&lst, cmd) == 1)
	{
		dup_and_close(std_fd);
		return (1);
	}
	dup_and_close(std_fd);
	return (0);
}
