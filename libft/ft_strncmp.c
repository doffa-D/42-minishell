/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:09:22 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/14 00:16:13 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *frst, const char *scnd, size_t length)
{
	size_t			i;
	unsigned char	*ferst;
	unsigned char	*secnd;

	i = 0;
	ferst = (unsigned char *)frst;
	secnd = (unsigned char *)scnd;
	while ((ferst[i] || secnd[i]) && i < length)
	{
		if (ferst[i] == secnd[i])
			i++;
		else if (ferst[i] < secnd[i])
			return (-1);
		else if (ferst[i] > secnd[i])
			return (1);
	}
	return (0);
}
