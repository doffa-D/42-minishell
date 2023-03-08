/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:08:29 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/07 18:59:01 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include <fcntl.h>
#include<pthread.h>
#include "libft/libft.h"
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
// int main() {
//     int fd = open("output.txt", O_WRONLY | O_CREAT, 0644); // open output file for writing
//     // int saved_stdout = dup(STDOUT_FILENO); // duplicate standard output

//     dup2(fd, STDOUT_FILENO); // redirect standard output to output file


//     printf("This message will be written to output.txt %d\n", 10);
//     // dup2(saved_stdout, STDOUT_FILENO); // restore standard output
//     // printf("This message will be written to output.txt\n");
//     close(fd); // close output file

//     return 0;
// }



int main() {
    int fd = open("tx.txt", O_WRONLY | O_TRUNC);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // if (truncate("myfile.txt", 0) == -1) {
    //     perror("truncate");
    //     return 1;
    // }
    
    close(fd);
    return 0;
}