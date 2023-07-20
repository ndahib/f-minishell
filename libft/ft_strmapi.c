/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:09:13 by ndahib            #+#    #+#             */
/*   Updated: 2022/10/20 17:21:41 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*p;

	i = 0;
	if (!s)
		return (0);
	p = (char *)ft_calloc((ft_strlen((char *)s) + 1), sizeof(char));
	if (!p)
		return (0);
	while (s[i] != '\0')
	{
		p[i] = f(i, s[i]);
		i++;
	}
	return (p);
}
