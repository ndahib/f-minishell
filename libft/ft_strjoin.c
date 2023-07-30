/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:58:30 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/29 21:46:27 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*joined;
	size_t	totalen;

	i = 0;
	if (s2 == 0 || *s2 == 0)
		return ((char *)s1);
	totalen = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)ft_calloc(totalen, sizeof(char));
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	if (ft_strlen(s1) != 0)
		free((char *)s1);
	return (joined);
}
