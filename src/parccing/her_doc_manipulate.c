/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_manipulate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:06:06 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/14 15:34:48 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*what_insied_herdoc(t_var *indes, char *buffer, char *herdoc)
{
	if ((buffer[indes->index_i] == '$' && buffer[indes->index_i + 1]
			&& buffer[indes->index_i + 1] != ' '))
	{
		herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, indes->start,
					indes->index_i - indes->start));
		free_parccing_part_after_error(herdoc);
		indes->index_i++;
		if (buffer[indes->index_i] == '?')
		{
			herdoc = ft_strjoin_v2(herdoc, ft_itoa(g_struct.exit_status));
			free_parccing_part_after_error(herdoc);
			indes->index_i++;
			indes->start = indes->index_i;
		}
		else
		{
			herdoc = expande_variables_insied_herdoc(indes, buffer, herdoc);
			free_parccing_part_after_error(herdoc);
		}
		indes->index_i--;
	}
	return (herdoc);
}

char	*fill_herdoc(char *buffer, t_var *indes, char *herdoc)
{
	indes->index_i = -1;
	indes->start = 0;
	while (buffer[++indes->index_i])
	{
		herdoc = what_insied_herdoc(indes, buffer, herdoc);
		if (!buffer[indes->index_i])
			break ;
	}
	herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, indes->start,
				indes->index_i - indes->start));
	free_parccing_part_after_error(herdoc);
	return (herdoc);
}

int	break_while(char *buffer, int c_of_s, t_var *variables)
{
	if (!buffer || !ft_strncmp(buffer, g_struct.each_cmd \
	[variables->index_i].files[c_of_s].files, ft_strlen(buffer) + 1))
	{
		if (buffer)
			free(buffer);
		return (1);
	}
	return (0);
}

char	*read_line_herdoc(int c_of_s, t_var *variables, char *herdoc)
{
	char	*buffer;
	t_var	indes;

	buffer = 0;
	indes.index_i = 0;
	indes.start = 0;
	while (1)
	{
		buffer = readline("> ");
		if (break_while(buffer, c_of_s, variables))
			break ;
		if (ft_strchr(buffer, '$')
			&& g_struct.each_cmd[c_of_s].files[c_of_s].herdoc_option == 0)
			herdoc = fill_herdoc(buffer, &indes, herdoc);
		else
		{
			herdoc = ft_strjoin(herdoc, buffer);
			free_parccing_part_after_error(herdoc);
		}
		herdoc = ft_strjoin(herdoc, "\n");
		free_parccing_part_after_error(herdoc);
		free(buffer);
	}
	return (herdoc);
}

void	parrcing_of_insied_herdoc(t_var *variables, int c_of_s, int i)
{
	int		fd_by_pipe[2];
	char	*herdoc;

	if (g_struct.fils_descreprot != 0)
		close(g_struct.fils_descreprot);
	herdoc = ft_strdup("");
	free_parccing_part_after_error(herdoc);
	pipe(fd_by_pipe);
	signal(SIGINT, SIG_IGN);
	i = fork();
	error_fork(i, 0);
	if (i == 0)
	{
		signal(SIGINT, SIG_DFL);
		herdoc = read_line_herdoc(c_of_s, variables, herdoc);
		ft_putstr_fd(herdoc, fd_by_pipe[1]);
		close(fd_by_pipe[1]);
		exit(0);
	}
	else
		wait(&i);
	signal(SIGINT, &handler);
	close(fd_by_pipe[1]);
	free(herdoc);
	g_struct.fils_descreprot = fd_by_pipe[0];
}
