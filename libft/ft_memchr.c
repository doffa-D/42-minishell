/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:53:24 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/08 13:18:50 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char *) str;
	while (i < n)
	{
		if (*s != (char )c)
			s++;
		else
			return (s);
		i++;
	}
	return (0);
}
