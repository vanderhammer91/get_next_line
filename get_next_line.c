/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:47:02 by ivanderw          #+#    #+#             */
/*   Updated: 2023/04/04 13:48:02 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	char	*get_next_line(int fd);

PARAMETERS
	fd:	The file descriptor to read from

RETURN VALUE
	Read line:	correct behaviour
	
	NULL: there is nothing else to read, or an error occured.

EXTERNAL FUNCTIONS:
	read, malloc, free

DESCRIPTION:
	Write a function that returns a line read from a file descriptor.
*/
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static char	*buffer_copy[100];
	char	*output;
	char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	if (!buffer_copy[fd])
		buffer_copy[fd] = ft_strdup("");
	output	= get_line(fd, &buffer, &buffer_copy[fd]);
	free_ptr(&buffer);
	return (output);
}


/*
int main(void) 
{
	int fd1;

  	fd1 = open("test.txt", O_RDONLY);
	read_and_print_100(fd1);
	close(fd1);
	return 0;
}
*/
