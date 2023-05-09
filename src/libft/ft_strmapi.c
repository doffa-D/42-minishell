/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:47:59 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/12 20:32:55 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dest;

	if (s == 0)
		return (0);
	dest = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	i = 0;
	while (s[i] && dest)
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	return (dest);
}
