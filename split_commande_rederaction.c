/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commande_rederaction.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:02:03 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 15:02:13 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	commande_and_rederaction_parceen(t_var *variables,
		int c_of_s)
{
	int	i;

	if (g_struct.tmp_cmd[variables->index_j] && \
		g_struct.tmp_cmd[variables->index_j] == 2)
	{
		initialisaion(variables, c_of_s);
		rediraction_calculate_output(variables, c_of_s);
		i = inistialisation_output(variables, c_of_s);
		if (i != 0)
			return (i);
		c_of_s++;
	}
	else if (g_struct.tmp_cmd[variables->index_j] \
		&& g_struct.tmp_cmd[variables->index_j] == 5)
	{
		initialisaion(variables, c_of_s);
		rediraction_calculate_input(variables, c_of_s);
		i = inistialisation_input(variables, c_of_s);
		if (i != 0)
			return (i);
		c_of_s++;
	}
	else
		commande_and_args(variables);
	return (c_of_s);
}