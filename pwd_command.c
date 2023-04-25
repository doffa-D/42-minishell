/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:19:18 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/25 18:09:35 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    pwd_command(void)
{
	// my_getenv(my_struct->list,"PWD");
	char wd[255];

	wd[255-1] = '\0';
	if (getcwd(wd, 255 - 1) != NULL)
		printf("%s\n", wd);
}