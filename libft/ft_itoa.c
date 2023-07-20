/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:22:24 by ndahib            #+#    #+#             */
/*   Updated: 2022/10/18 17:21:06 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbrofdigit(long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*create_arr(long long number, int nbrofdigit, int is_neg)
{
	char	*string_num;

	string_num = (char *) ft_calloc(nbrofdigit + 1, sizeof(char));
	if (string_num == NULL)
		return (0);
	if (is_neg)
	{
		string_num[0] = '-';
	}
	while (nbrofdigit > is_neg)
	{
		string_num[nbrofdigit - 1] = (number % 10) + '0';
		number /= 10;
		nbrofdigit--;
	}
	return (string_num);
}

char	*ft_itoa(int n)
{
	int			chars_len;
	char		*string_num;
	long long	k;

	k = (long long)n;
	if (k < 0)
	{
		chars_len = nbrofdigit(k * -1);
		string_num = create_arr(k * -1, chars_len + 1, 1);
	}
	else if (k > 0)
	{
		chars_len = nbrofdigit(k);
		string_num = create_arr(k, chars_len, 0);
	}
	else
	{
		string_num = (char *) ft_calloc(2, sizeof(char));
		string_num[0] = '0';
	}
	return (string_num);
}
