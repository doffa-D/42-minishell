/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:44 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/02 15:56:54 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>
char	*ft_strdup(const char *s1)
{
	int		i;
	char	*b;
	i = 0;
	b = malloc(ft_strlen((char *) s1) + 1);
	if (!b)
		return (0);
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	b[i] = 0;
	return (b);
}

