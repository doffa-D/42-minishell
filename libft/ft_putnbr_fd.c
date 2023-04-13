/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:54:46 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/12 20:15:49 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	chek_len(int n)
{
	int	i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i = i * 10;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	i;
	long int	nb;

	nb = n;
	i = chek_len(nb);
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar_fd('-', fd);
	}
	while (i)
	{
		ft_putchar_fd((nb / i) + '0', fd);
		nb = nb % i;
		i /= 10;
	}
}
