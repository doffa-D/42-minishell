/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttttttttttt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:53:09 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/17 20:10:21 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>

int main()
{
    char *str = malloc(1);
    str[0] = 'J';
    int i = 0;
    printf("parent%p\n", str);
    i = fork();
    if(i == 0)
    {
        str[0]= 'K';
        printf("chiled%p\n", str);
        free(str);
        sleep(5);
        exit(0);
    }
    waitpid(-1, &i, 0);
    free(str);
    printf("%s\n", str);
}