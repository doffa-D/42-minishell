/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:46:23 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/13 21:47:18 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_atoi(const char *str)
{
	long int	result;
	int			i;
	int			j;

	i = 0;
	j = 1;
	result = 0;
	while (str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) > 0)
	{
		result = (result * 10) + (str[i] - 48) * j;
		i++;
	}
	return (result);
}
