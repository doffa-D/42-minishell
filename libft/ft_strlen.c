/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:51:21 by nouakhro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/11 17:21:59 by nouakhro         ###   ########.fr       */
=======
/*   Updated: 2023/03/20 18:11:56 by nouakhro         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char	*str)
{
	int	i;
	if(!str && !*str)
		return 0;
	i = 0;
	while (str[i])
<<<<<<< HEAD
=======
	{
		// printf("====>%s\n", str);	
>>>>>>> main
		i++;

	}
	return (i);
}
