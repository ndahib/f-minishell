/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:26:21 by ndahib            #+#    #+#             */
/*   Updated: 2023/06/17 18:34:59 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s1, unsigned int start, size_t len)
{
	char			*sub;
	size_t			slen;

	if (!s1)
		return (0);
	if (len == 0)
		return (0);
	slen = ft_strlen(s1);
	if (start > slen)
		return (ft_strdup(""));
	if (slen < len)
		len = slen;
	sub = (char *)ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (0);
	s1 += start;
	ft_strlcpy(sub, s1, len + 1);
	return (sub);
}
