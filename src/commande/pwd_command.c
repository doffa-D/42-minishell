/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:19:18 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/14 04:11:00 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	_max_path_file(t_list *new_1, \
t_list *old_list, char *str, t_list *list)
{
	if (new_1)
	{
		free(new_1->content);
		str = getcwd(NULL, 0);
		if (!str)
			perror("PATH_MAX");
		new_1->content = ft_strjoin_v2(ft_strdup("PWD="), str);
		free_excution_part_after_error(new_1->content);
		list = old_list;
	}
}

void	pwd_command(void)
{
	char	*wd;

	wd = getcwd(0, 0);
	if (wd != NULL)
		printf("%s\n", wd);
}
