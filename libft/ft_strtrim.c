/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:21:05 by ndahib            #+#    #+#             */
/*   Updated: 2022/10/14 18:32:20 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	check(char c, char *s);

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	i;
	size_t	len;
	char	*trimed;

	i = 0;
	len = ft_strlen(s);
	while (check(s[i], (char *)set))
		i++;
	if (!s[i])
		return (ft_calloc(1, sizeof(char)));
	len = ft_strlen(s + i);
	while (check(s[len + i - 1], (char *)set))
		len--;
	trimed = (char *)ft_calloc(len + 1, sizeof(char));
	if (!trimed)
		return (0);
	ft_memmove(trimed, s + i, len);
	return (trimed);
}

static int	check(char c, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
