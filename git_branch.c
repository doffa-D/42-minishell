/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:06 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/08 17:24:15 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"


char	*get_next_line(int fd)
{
	char	buffer;
	char	line[7000000];
	int		b;
	int		i;

	if (fd < 0 || 5 <= 0)
		return (NULL);
	i = 0;
	b = read(fd, &buffer, 1);
	while (b > 0)
	{
		line[i++] = buffer;
		if (buffer == '\n')
			break ;
		b = read(fd, &buffer, 1);
	}
	line[i] = '\0';
	if (b <= 0 && i == 0)
		return (NULL);
	return (ft_strdup(line));
}

char* get_git_branch_name()
{
    int fd ;
    char *str1;
    char *l;
    char **str;
    l = ft_strjoin(getcwd(NULL,554),"/.git/HEAD");
    fd = open(l,O_RDONLY);
    printf("%s\n",l);
    free(l);
    l = get_next_line(fd);
    if (l == NULL)
    {
        close(fd);
        return NULL;
    }
    str = ft_split(l,'/');
    printf("%p\t%d\n",l,fd);
    free(l);
    int i;
    i = 0;
        // printf("===== %s\n", str[i]);
    while(str[i])
    {
        i++;
    }
    if(str[i-1])
    {
        str1 = ft_strdup(str[i-1]);
        free_split(str);
        l = ft_strtrim(str1,"\n");
        free(str1);
    }
    
    close(fd);
    return l;
}
