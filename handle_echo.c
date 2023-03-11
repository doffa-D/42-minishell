/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:00:54 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/03/11 14:31:55 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check(t_all *my_struct, int i, int j, char *buff)
{
	if (my_struct->my_command[j][i - 1] == 34
		&& my_struct->my_command[j][ft_strlen(my_struct->my_command[j])
		- 1] == 34)
		printf("%s", getenv(buff));
	else if (my_struct->my_command[j][i - 1] == 39
			&& my_struct->my_command[j][ft_strlen(my_struct->my_command[j])
			- 1] == 39)
		printf("$%s", buff);
	else if (!my_struct->my_command[j][i - 1]
			&& !my_struct->my_command[j][ft_strlen(my_struct->my_command[j])])
		if (getenv(buff) != NULL)
			printf("%s", getenv(buff));
}

void	handle_dollar(t_all *my_struct, int i, int j)
{
	int		x;
	int		z;
	char	*buff;

	x = i + 1;
	z = 0;
	buff = malloc(ft_strlen(my_struct->my_command[j]));
	if (!buff)
		return ;
	while (my_struct->my_command[j][x])
	{
		if (my_struct->my_command[j][x] != 34
			&& my_struct->my_command[j][x] != '$'
			&& my_struct->my_command[j][x] != 39
			&& my_struct->my_command[j][x] != ' ')
			buff[z++] = my_struct->my_command[j][x];
		x++;
	}
	check(my_struct, i, j, buff);
	free(buff);
	i++;
}

void	check_dollar(t_all *my_struct, int i, int j)
{
	while ((size_t)i < ft_strlen(my_struct->my_command[j]))
	{
		if (my_struct->my_command[j][i] == 34)
			i++;
		else if (my_struct->my_command[j][i] == '$')
		{
			handle_dollar(my_struct, i, j);
			break ;
		}
		else
		{
			if (my_struct->my_command[j][i] != 39)
				printf("%c", my_struct->my_command[j][i]);
			i++;
		}
	}
}

void	exicut_echo(t_all *my_struct)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	while (my_struct->my_command[len])
		len++;
	my_struct->command_len = len;
	i = 0;
	j = 1;
	if (!ft_strncmp(my_struct->my_command[1], "-n", ft_strlen("-n")))
		j++;
	while (my_struct->my_command[j])
	{
		i = 0;
		check_dollar(my_struct, i, j);
		if (my_struct->my_command[j + 1])
			printf(" ");
		j++;
	}
	if (ft_strncmp(my_struct->my_command[1], "-n", ft_strlen("-n")))
		printf("\n");
}

int	quote_check(t_all *my_struct)
{
	int	i;
	int	j;
	int	count_1;
	int	count;

	i = -1;
	count_1 = 0;
	count = 0;
	while (my_struct->my_command[++i])
	{
		j = -1;
		while (my_struct->my_command[i][++j])
		{
			if (my_struct->my_command[i][j] == 34)
				count_1++;
			else if (my_struct->my_command[i][j] == 39)
				count++;
		}
	}
	if (count_1 % 2 == 1 && count_1 > 0)
		return (0);
	if (count % 2 == 1 && count > 0)
		return (0);
	return (1);
}
