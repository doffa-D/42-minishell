/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:00:54 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/04 14:43:42 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_2(char **str)
{
	int i;
	i = 0;
	while(str[i])
		i++;
	return i;
}
int check_n(char *str)
{
	int i;
	int x;
	x = ft_strlen(str);
	i = 0;
	if(str[0] == '-')
	{
		i++;
		while(str[i])
		{
			if(str[i] == 'n')
				i++;
			else
				break;
		}
	}
	if(i == x && *str)
		return 1;
	return 0;
}

void	echo_command(t_all *my_struct, int c_of_s)
{
	int		i;
	int		j;
	int x = 0;

	j = 0;
	i = 1;
	while (my_struct->each_cmd[c_of_s].cmd[i])
	{
		if (check_n(my_struct->each_cmd[c_of_s].cmd[i]) == 1 && x == 0)
		{
			j = 1;
		}
		else
		{
			printf("%s", my_struct->each_cmd[c_of_s].cmd[i]);
			x = 1;
		}
		if(i < len_2(my_struct->each_cmd[c_of_s].cmd) - 1 && x == 1)
			printf(" ");
		i++;
	}
	if(j == 0)
		printf("\n");
}

// void	echo_command(t_all *my_struct, int c_of_s)
// {
// 	int i;
// 	int j;
// 	int x;
// 	int z;
// 	i = 0;
// 	j = 0;
// 	x = 0;
// 	z = 0;

// 	while(my_struct->each_cmd[c_of_s].cmd[i])
// 	{
// 		j = 0;
// 		if(ft_strncmp(my_struct->each_cmd[c_of_s].cmd[i],"-n",ft_strlen) && x == 0)
// 		{
// 			z = 1;
// 		}
// 		else
// 		{
// 			x = 1;
// 			while(my_struct->each_cmd[c_of_s].cmd[i][j])
// 			{
// 				printf("%c",my_struct->each_cmd[c_of_s].cmd[i][j]);
// 				j++;
// 			}
// 		}		
// 	}
// }
