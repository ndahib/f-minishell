/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:06:13 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/25 15:27:45 by ndahib           ###   ########.fr       */
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
	t_pipe_files	var;

	var.i = -1;
	var.input_fd = -1;
	var.pipe_fd[0] = -1;
	var.pipe_fd[1] = -1;
	while (++(var.i) < nbr)
	{
		if (var.i != nbr - 1)
			pipe(var.pipe_fd);
		create_childs(cmd, env, &var);
		dup_fd(&(var.input_fd), -1);
		copy_input_to_fd(&(var.input_fd), (var.pipe_fd));
		dup_fd(&(var.pipe_fd[1]), -1);
		dup_fd(&(var.pipe_fd[0]), -1);
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
