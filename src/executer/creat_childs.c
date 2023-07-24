/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:15:45 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/24 10:17:03 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_input_to_fd(int *input_fd, int *pipe_fd)
{
	if (pipe_fd[0] != -1)
	{
		*input_fd = pipe_fd[0];
		pipe_fd[0] = -1;
	}
}

//***************create_child_forone_cmd***************************************
void	create_child(t_simple_cmd *one_cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork :");
	else if (!pid)
	{
		if (check_redir(one_cmd->files) == 1)
			return ;
		if (one_cmd->fd != -1)
			dup_close(one_cmd->fd);
		if (!one_cmd->path)
		{
			printf("minishell: command not found\n");
			exit(127);
		}
		else if (execve(one_cmd->path, one_cmd->arg, env) == -1)
		{
			perror("minishell: command not found\n");
			exit(127);
		}
		else
			exit(EXIT_SUCCESS);
	}
	wait_childs(1);
}

void	execute_cmd(t_simple_cmd *cmd, char **env_array)
{
	if (cmd->path == NULL)
	{
		printf("minishell : command not found\n");
		free_lst_of_cmd(&cmd);
		free_double_pointer(env_array);
		exit(127);
	}
	if (execve(cmd->path, cmd->arg, env_array) == -1)
	{
		perror("minishell:\n");
		free_lst_of_cmd(&cmd);
		free_double_pointer(env_array);
		exit(127);
	}
	exit(EXIT_SUCCESS);
}

//***************create_child_for_multiples_cmds*******************************
void	create_childs(t_simple_cmd *cmd, t_env **env, int *pipe_fd, int *fd, int i)
{
	pid_t		pid;
	char		**env_arr;

	env_arr = convert_env_to_array(*env);
	pid = fork();
	if (pid == -1)
		perror("fork :");
	if (pid == 0)
	{
		dup_fd(&pipe_fd[1], STDOUT_FILENO);
		if (i != 0)
			dup_fd(&pipe_fd[0], STDIN_FILENO);
		else
			close(pipe_fd[0]);
		dup_fd(fd, STDIN_FILENO);
		if (check_redir(cmd->files) == 1)
			exit(EXIT_FAILURE) ;
		if (cmd->fd != -1)
			dup_close(cmd->fd);
		if (is_built_ins(env, cmd) == 0)
			exit(EXIT_SUCCESS);
		else
			execute_cmd(cmd, env_arr);
		free_double_pointer(env_arr);
	}
}

int	run_built_ins(t_env **env, t_simple_cmd *cmd)
{
	if (is_built_ins(env, cmd) == 0)
	{
		g_exit_status = 0;
		return (0);
	}
	else
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
}
