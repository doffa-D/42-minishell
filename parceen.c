/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parceen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 00:39:18 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/26 00:41:13 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
void parccen(t_all *my_struct)
{
    int		i;
	int		j;
	int		checker;
	char	splite_char;
    my_struct->tmp_cmd = 0;
	my_struct->tmp_cmd = ft_strdup(my_struct->cmd);
	my_struct->the_commande = 0;
	while (my_struct->tmp_cmd[i])
	{
		splite_char = ' ';
		checker = 0;
		while (my_struct->tmp_cmd[i] && my_struct->tmp_cmd[i] != splite_char)
		{
			if (my_struct->tmp_cmd[i] == 34 && !checker)
			{
				splite_char = 34;
				checker = 1;
			}
			if (my_struct->tmp_cmd[i] == 39 && !checker)
			{
				splite_char = 39;
				checker = 1;
			}
			i++;
		}
		if (splite_char != ' ' && my_struct->tmp_cmd[i])
			i++;
		if (my_struct->tmp_cmd[i] == ' ')
		{
			if (!my_struct->the_commande)
				my_struct->the_commande = ft_calloc(1, 1);
			my_struct->tmp_cmd[i] = 3;
			i++;
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
					ft_substr(my_struct->tmp_cmd, j, i - j));
			j = i;
		}
		if (!my_struct->tmp_cmd[i])
		{
			if (!my_struct->the_commande)
				my_struct->the_commande = ft_calloc(1, 1);
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
					ft_substr(my_struct->tmp_cmd, j, i - j));
			break ;
		}
	}

}