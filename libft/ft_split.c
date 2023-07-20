/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:43:17 by ndahib            #+#    #+#             */
/*   Updated: 2023/06/17 18:27:22 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbrwords(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		count++;
		while (*s != c && *s)
			s++;
		s++;
	}
	return (count);
}

int	lenwrd(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
	{
		s++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	char	*s1;
	char	*s2;
	int		i;

	i = 0;
	str = ft_calloc((nbrwords((char *)s, c) + 1), sizeof(char *));
	if (!str)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		s1 = ft_calloc((lenwrd((char *)s, c) + 1), sizeof(char));
		s2 = s1;
		while (*s != c && *s)
			*s2++ = *s++;
		str[i++] = s1;
	}
	return (str);
}
