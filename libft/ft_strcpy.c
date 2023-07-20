/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:08:11 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/18 01:14:26 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strcpy(char *dst, const char *stash, int start, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = stash[start];
		i++;
		start++;
	}
	dst[i] = '\0';
}
