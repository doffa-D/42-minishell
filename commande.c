/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/23 21:57:31 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exicut_commande(t_all *my_struct, int i, int c_of_s, int *pipe_n)
{
	(void)pipe_n;
	if(my_struct->each_cmd[c_of_s].files)
			check_rediractions(my_struct, c_of_s);
	if(my_struct->number_of_pipes == 1)
	{
		if(builtins(my_struct, c_of_s))
			exit(0);
	}
	execve(my_struct->my_path[i], my_struct->each_cmd[c_of_s].cmd, NULL);
}