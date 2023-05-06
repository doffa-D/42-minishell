/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:00:54 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/06 20:47:57 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_n(char *str)
{
	int	i;
	int	x;

	x = ft_strlen(str);
	i = 0;
	if(str && str[0] == '-' && str[1])
	{
		i++;
		while (str[i])
		{
			if (str[i] == 'n')
				i++;
			else
				break ;
		}
	}
	if (i == x && *str)
		return (1);
	return (0);
}

void	echo_command(int c_of_s)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 0;
	i = 1;
	while (g_struct.each_cmd[c_of_s].cmd[i])
	{
		if (check_n(g_struct.each_cmd[c_of_s].cmd[i]) == 1 && x == 0)
		{
			j = 1;
		}
		else
		{
			printf("%s", g_struct.each_cmd[c_of_s].cmd[i]);
			x = 1;
		}
		if (i < len_2(g_struct.each_cmd[c_of_s].cmd) - 1 && x == 1)
			printf(" ");
		i++;
	}
	if (j == 0)
		printf("\n");
}
