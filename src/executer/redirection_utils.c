/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:20:00 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/24 17:25:56 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redirection(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("minishell "), 1);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (0);
}

int	in_redirection(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("minishell "), 1);
	dup2(fd, STDIN_FILENO);
	close (fd);
	return (0);
}

int	append_redirection(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (perror("minishell"), 1);
	dup2(fd, 1);
	close (fd);
	return (0);
}
