/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:59:43 by ndahib            #+#    #+#             */
/*   Updated: 2022/10/12 13:12:56 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lendst;

	i = 0;
	j = 0;
	lendst = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen((char *)src));
	if (!src && !dst)
		return (0);
	if (lendst > dstsize)
		return (dstsize + ft_strlen((char *)src));
	else
	{
		while (dst[i] != '\0')
			i++;
		while ((i + j) < dstsize - 1 && src[j] != '\0')
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	return (lendst + ft_strlen((char *)src));
}
