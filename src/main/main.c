/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:42:32 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 20:20:21 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		ft_putstr_fd("minishell-> ", 1);
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_herdoc(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

void	parse_and_execute(t_env **env_lst, char **tokens, char *cmd_line)
{
	t_simple_cmd	*parse_cmd;

	parse_cmd = NULL;
	parse_cmd = parse_simple_cmd(*env_lst, tokens);
	free_double_pointer(tokens);
	free(cmd_line);
	execute_commands(parse_cmd, env_lst);
	free_lst_of_cmd(&parse_cmd);
}

void	free_all(char **tokens, char *cmd_line)
{	
	g_exit_status = 2;
	free_double_pointer(tokens);
	free(cmd_line);
}

void	minishell_loop(t_env **env_lst)
{
	char	**tokens;
	char	*cmd_line;

	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_sig);
		cmd_line = readline("minishell-> ");
		if (!cmd_line)
			exit(g_exit_status);
		if (!ft_strlen(cmd_line))
		{
			free(cmd_line);
			continue ;
		}
		else
			add_history(cmd_line);
		tokens = tokeniser(cmd_line);
		if (check_syntax_err(tokens) == 1)
		{
			free_all(tokens, cmd_line);
			continue ;
		}
		parse_and_execute(env_lst, tokens, cmd_line);
		mini_error = 0;
		system("leaks minishell");
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_lst;

	(void)ac;
	(void)av;
	env_lst = handle_env(env);
	minishell_loop(&env_lst);
	return (0);
}
