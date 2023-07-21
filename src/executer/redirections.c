/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:28:31 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/21 23:21:28 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_buffer(char *del)
{
	char	*line;
	char	*final;

	line = NULL;
	final = "";
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, del, ft_strlen(del)) == 0)
			break ;
		final = ft_strjoin(final, line);
	}
	return (final);
}

int	her_doc(char *del)
{
	int		fd[2];
	int		len;
	char	*buff;
	int		pid;

	if (pipe(fd) == -1)
		perror("pipe : ");
	pid = fork();
	if (pid == -1)
	{
		perror("fork in herdoc : \n");
		return (-1);
	}
	else if (!pid)
	{
		close(fd[0]);
		buff = get_buffer(del);
		ft_putstr_fd(buff, fd[1]);
		free(buff);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	wait(NULL);
	return fd[0];
}

// int	check_and_dup(fd, duplicated_file)
// {
// 	if (fd == -1)
// 		return (1);
// 	dup2(fd, duplicated_file);
// 	close (fd);
// 	return (0);
// }

int	redirections(t_files *files)
{
	int		fd;
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			fd = open(tmp->file, O_RDWR | O_CREAT | O_TRUNC,  0644);
			if (fd == -1)
				return (perror("OPEN : "), 1);
			dup2(fd, STDOUT_FILENO);
			close (fd);
		}
		else if (tmp->type == 3)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
				return (perror("OPEN : "), 1);
			dup2(fd, 0);
			close (fd);
		}
		else if (tmp->type == 5)
		{
			fd = open(tmp->file, O_RDWR | O_CREAT | O_APPEND, 0777);
			if (fd == -1)
				return (perror("OPEN : "), 1);
			dup2(fd, 1);
			close (fd);
		}
		else if (tmp->type == 6)
		{
			fd = her_doc(tmp->file);
			if (fd == -1)
				return (perror("herdoc : "), 1);
			dup2(fd, 0);
			close (fd);
		}
		tmp = tmp->next;
	}
	return (0);
}