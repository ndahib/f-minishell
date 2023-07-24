/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:09:52 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/23 19:45:54 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//==========ft_strjoin_line====================================================
char	*ft_strjoin_line(char *s1, char *s2, int len2)
{
	char	*joined;
	int		len1;

	len1 = ft_strlen(s1);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1, 0, len1);
	ft_strcpy(joined + len1, s2, 0, len2);
	free(s1);
	return (joined);
}

//==========ft_split_save()====================================================
char	*ft_split_save(const char *stash)
{
	int		len;
	int		start;
	char	*save;

	start = len_of_word(stash, '\n');
	len = len_of_word(stash, '\0') - start;
	save = malloc(len + 1);
	if (!save)
		return (NULL);
	ft_strcpy(save, stash, start, len);
	if (ft_strlen(save) == 0)
		return (free(save), NULL);
	return (save);
}

//==========ft_split_line()====================================================
char	*ft_split_line(const char *stash)
{
	int		len;
	char	*line;

	len = len_of_word(stash, '\n');
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strcpy(line, stash, 0, len);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

//==========ft_read_line=======================================================
static char	*ft_readline(int fd, char *line)
{
	char	buff[100];
	int		r;

	r = 1;
	while (r != 0 && !ft_strchr(line, '\0'))
	{
		r = read(fd, buff, 100);
		if (r == -1 || (r == 0 && !(line)))
			return (free(line), NULL);
		line = ft_strjoin_line(line, buff, r);
	}
	return (line);
}

//==========get_next_line======================================================
char	*get_next_line(int fd)
{
	char		*line;
	char		*stash;
	static char	*save;

	line = NULL;
	if (fd < 0)
		return (NULL);
	stash = ft_readline(fd, save);
	if (!stash)
		return (NULL);
	line = ft_split_line(stash);
	save = ft_split_save(stash);
	free(stash);
	return (line);
}
