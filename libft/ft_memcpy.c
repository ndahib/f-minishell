/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:50:06 by ndahib            #+#    #+#             */
/*   Updated: 2022/10/11 22:37:54 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ldst;
	unsigned char	*lsrc;

	i = 0;
	ldst = (unsigned char *)dst;
	lsrc = (unsigned char *)src;
	while (i < n)
	{
		ldst[i] = lsrc[i];
		i++;
	}
	return (dst);
}
