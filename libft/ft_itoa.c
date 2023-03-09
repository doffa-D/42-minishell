/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:11:45 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 16:35:26 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counte(long int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*dst;
	long int	nb;
	int			len;

	nb = n;
	len = ft_counte(nb);
	dst = malloc(len +1);
	if (!dst)
		return (0);
	if (nb < 0)
	{
		dst[0] = '-';
		nb *= -1;
	}
	dst[len] = 0;
	if (nb == 0)
		dst[0] = '0';
	while (nb != 0)
	{
		dst[--len] = (nb % 10) + 48;
		nb /= 10;
	}
	return (dst);
}
