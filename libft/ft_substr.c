/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:13:46 by nouakhro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/11 16:00:12 by nouakhro         ###   ########.fr       */
=======
/*   Updated: 2023/03/21 17:28:46 by hdagdagu         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
<<<<<<< HEAD
#include"../minishell.h"
=======
>>>>>>> main

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
	b[i] = 0;
	return (b);
}
