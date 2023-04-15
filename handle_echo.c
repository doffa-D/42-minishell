/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:00:54 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/14 18:24:38 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_dollar(char *cmd)
// {
// 	int		i;
// 	int		j;
// 	char	*buff;

// 	j = 0;
// 	i = 0;
// 	buff = malloc(sizeof(char) * ft_strlen(cmd));
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == 34)
// 			i++;
// 		else
// 		{
// 			i++;
// 			buff[j] = cmd[i];
// 			j++;
// 		}
// 	}
// 	buff[j - 1] = '\0';
// 	if (getenv(buff) != NULL)
// 		printf("%s", getenv(buff));
// }

// void	handle_echo(t_all *my_struct,int x,int i,int j)
// {
// 	printf("[%s]",my_struct->my_command[1]);
// 	while (my_struct->fix_cmd[i])
// 	{
// 		j = 0;
// 		if (ft_strchr(my_struct->fix_cmd[i], '$') && !ft_strchr(my_struct->fix_cmd[i], 39))
// 		{
// 			check_dollar(my_struct->fix_cmd[i]);
// 			x = 1;
// 		}
// 		while (my_struct->fix_cmd[i][j])
// 		{
// 			if (my_struct->fix_cmd[i][j] == 39 || my_struct->fix_cmd[i][j] == 34)
// 				j++;
// 			else if (x == 0)
// 			{
// 				if (ft_strchr(my_struct->fix_cmd[i], '$') && !ft_strchr(my_struct->fix_cmd[i], 39))
// 				{
// 					check_dollar(my_struct->fix_cmd[i]);
// 					x = 1;
// 					break;
// 				}
// 				else
// 					printf("%c", my_struct->fix_cmd[i][j]);
// 				j++;
// 			}
// 			else
// 				j++;
// 		}
// 		if (my_struct->fix_cmd[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// }

// void	exicut_echo(t_all *my_struct)
// {
// 	int i;
// 	int j;
// 	int x;
	
// 	j = 0;
// 	i = 1;
// 	x = 0;
// 	if (!ft_strncmp(my_struct->fix_cmd[1], "-n", ft_strlen("-n")))
// 		i++;
// 	handle_echo(my_struct,x,i,j);
// 	if (ft_strncmp(my_struct->fix_cmd[1], "-n", ft_strlen("-n")))
// 		printf("\n");
// }