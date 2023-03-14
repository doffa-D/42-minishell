/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:46:44 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/15 16:31:13 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	char	*s1;
	char	*s2;

	s1 = (char *)str1;
	s2 = (char *) str2;
	if (!str1 && !str2)
		return (0);
	if (str1 < str2)
		return (ft_memcpy(s1, s2, n));
	while (n)
	{
		n--;
		s1[n] = s2[n];
	}
	return (str1);
}
