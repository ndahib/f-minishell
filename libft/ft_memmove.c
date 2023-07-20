/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:47:16 by ndahib            #+#    #+#             */
/*   Updated: 2022/10/14 18:35:51 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ldst;
	char	*lsrc;

	ldst = (char *)dst;
	lsrc = (char *)src;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
			ldst[len] = lsrc[len];
	}
	return (dst);
}
