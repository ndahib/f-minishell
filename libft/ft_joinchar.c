/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:04:10 by ndahib            #+#    #+#             */
/*   Updated: 2023/06/22 16:32:15 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinchar(char *str, char c)
{
	char	*str2;
	int		i;

	i = -1;
	str2 = malloc(ft_strlen(str) + 2);
	if (!str2)
		return (NULL);
	while (str[++i])
		str2[i] = str[i];
	str2[i++] = c;
	str2[i] = '\0';
	if (ft_strlen(str) != 0)
		free(str);
	return (str2);
}
