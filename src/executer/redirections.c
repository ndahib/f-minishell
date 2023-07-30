/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:28:31 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/30 17:25:47 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_final(char *final, t_env *env)
{
	char	*tmp;
	char	*new_final;

	tmp = ft_strdup(final);
	new_final = expand_her_doc(final, env);
	free(tmp);
	return (new_final);
}

char	*herdoc_line(char *new_del)
{
	char	*final;
	char	*line;

	final = "";
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, new_del) == 0)
		{
			free(line);
			break ;
		}
		final = ft_strjoin(final, ft_joinchar(line, '\n'));
	}
	return (final);
}

char	*get_buffer(char *del, t_env *env)
{
	char	*final;
	char	*new_del;
	int		check;

	final = "";
	new_del = NULL;
	check = check_del(del);
	if (check == 1)
		new_del = remove_quotes(del);
	else
		new_del = del;
	final = herdoc_line(new_del);
	if (check == 0)
		return (new_final(final, env));
	free(del);
	free(new_del);
	return (final);
}

int	her_doc(char *del, t_env *env)
{
	int		fd[2];
	char	*buff;
	pid_t	pid;

	buff = "";
	if (pipe(fd) == -1)
		return (perror("minishell : "), -1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	pid = fork();
	if (pid == -1)
		return (perror("fork in heredoc : \n"), -1);
	else if (!pid)
	{
		close(fd[0]);
		buff = get_buffer(del, env);
		ft_putstr_fd(buff, fd[1]);
		if (ft_strlen(buff) != 0)
			free(buff);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	wait(NULL);
	return (fd[0]);
}

int	redirections(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			if (out_redirection(tmp->file) == 1)
				return (1);
		}
		else if (tmp->type == 3)
		{
			if (in_redirection(tmp->file) == 1)
				return (1);
		}
		else if (tmp->type == 5)
		{
			if (append_redirection(tmp->file) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
