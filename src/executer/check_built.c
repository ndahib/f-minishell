/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:37:37 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/23 19:43:05 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	dup_and_close(int *std_fd)
{
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	close(std_fd[1]);
	close(std_fd[0]);
}

int	is_built_ins(t_env **lst, t_simple_cmd *cmd)
{
	int	i;
	int	std_fd[2];

	i = 1;
	if (cmd->cmd == NULL)
		return (1);
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
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
		dup_and_close(std_fd);
		return (1);
	}
	dup_and_close(std_fd);
	return (0);
}
