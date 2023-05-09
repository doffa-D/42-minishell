/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:26:28 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:00 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

char	*variables_parceen_utils(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->index_j + 1])
		|| whotout_expande[variables->index_j + 1] == '_')
	{
		if (whotout_expande[variables->index_j + 1])
		{
			variables->start++;
			my_string = variables_parceen(variables, whotout_expande,
					my_string);
			variables->start = variables->index_j;
		}
	}
	else
		my_string = _not_alphanum_after_dolar(whotout_expande, my_string, \
		variables);
	return (my_string);
}
