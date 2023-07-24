/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:06:13 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/24 10:17:38 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_fd(int *pipe, int fd)
{
	if (fd > -1 && pipe[0] > -1)
		dup2(pipe[0], fd);
	close(pipe[0]);
	pipe[0] = -1;
}

int	execute_compound_cmnd(t_simple_cmd *cmd, t_env **env, int nbr)
{
	int		i;
	int		pipe_fd[2];
	int		input_fd;
	char	**env_arr;

	i = -1;
	input_fd = -1;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (++i < nbr)
	{
		if (i != nbr - 1)
			pipe(pipe_fd);
		create_childs(cmd, env, pipe_fd, &input_fd, i);
		dup_fd(&input_fd, -1);
		copy_input_to_fd(&input_fd, pipe_fd);
		dup_fd(&pipe_fd[1], -1);
		dup_fd(&pipe_fd[0], -1);
		cmd = cmd->next;
	}
	wait_childs(nbr);
	return (g_exit_status);
}

int	execute_one_simple_cmd(t_simple_cmd *one_cmd, t_env **env)
{
	char	**env_array;

	if (check_is_built_ins(one_cmd->cmd) == 0)
		return (run_built_ins(env, one_cmd));
	env_array = convert_env_to_array(*env);
	create_child(one_cmd, env_array);
	free_double_pointer(env_array);
	return (g_exit_status);
}

int	execute_commands(t_simple_cmd *cmnd, t_env **env)
{
	int		nbr;
	int		status;

	nbr = get_number_of_cmds(cmnd);
	if (nbr == 1)
		status = execute_one_simple_cmd(cmnd, env);
	else
		status = execute_compound_cmnd(cmnd, env, nbr);
	return (status);
}
