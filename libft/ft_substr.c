/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:13:46 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/27 19:54:11 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"stdio.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*b;

	if (!s)
		return (0);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	i = 0;
	b = malloc(sizeof(char) * (len + 1));
	if (!b)
		return (0);
	while (i < len && start < ft_strlen(s))
	{
		b[i] = s[start];
		i++;
		start++;
	}
	// printf("hhhhhhhhhhhhhhhh\n");
	b[i] = 0;
	// if(!ft_strlen(b))
	// 	return 0;
	return (b);
}
