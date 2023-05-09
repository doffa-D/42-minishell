/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:24:06 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/14 00:24:47 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	len(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	j;
	char		*m;

	j = n;
	i = len(j);
	m = malloc((i + 1) * sizeof(char));
	if (!m)
		return (0);
	m[i] = 0;
	if (j == 0)
		m[i - 1] = '0';
	if (j < 0)
	{
		m[0] = '-';
		j = j * -1;
	}
	while (j > 0 && i--)
	{
		m[i] = j % 10 + 48;
		j = j / 10;
	}
	return (m);
}
