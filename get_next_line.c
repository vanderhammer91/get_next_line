/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:47:02 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/28 16:52:34 by ivanderw         ###   ########.fr       */
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

/*
void	read_and_print_100(int fd)
{
	char	buf[BUFFER_SIZE];	// store the read characters
	int	nb_read;	// store read's return value

//	Read 100 characters from the file descriptor
	nb_read = read(fd, buf, BUFFER_SIZE);
//	Stop everything in case of error
	if (nb_read == -1)
	{
		printf("Read error!\n");
		return ;
	}
//	Add \0 to the end of the buffer
	buf[nb_read] = '\0';
//	Print the file descriptor and then the buffer contents
	printf("\e[36mfd %d : [\e[0m%s\e[36m]\e[0m\n", fd, buf);
	return ;
}
*/

//SOURCE 1: STACK OVERFLOW ARTICLE
/*
int     get_next_line(int const fd, char **line)
{
    char buffer[BUFF_SIZE + 1];
    size_t i;
    size_t size;

    if (!(*line = malloc(BUFF_SIZE)))
        return (-1);
    *line[0] = '\0';
    while (read(fd, buffer, BUFF_SIZE) > 0)
    {
        buffer[BUFF_SIZE + 1] = '\0';
        if (buffer[0] == '\n')
            return (1);
        if (ft_strchr(buffer, '\n') != NULL)
        {
            i = 0;
            size = ft_strlen(*line);
            buffer[BUFF_SIZE + 1] = '\0';
            while (buffer[i] != '\0')
            {
                if (buffer[i] == '\n')
                {
                    if (!(*line = realloc(*line, i + size)))
                        return (-1);
                    buffer[i] = '\0';
                    ft_strncat(*line, buffer, i);
                    return (1);
                }
                i++;
            }
        }
        if (!(*line = realloc(*line, BUFF_SIZE)))
            return (-1);
        ft_strncat(*line, buffer, BUFF_SIZE);
    }
    return (0);
}

*/


//SOURCE 2: GITHUB STUDENT #1
/*
int			get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*s[FD_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (output(s, line, ret, fd));
}
*/


char	*get_next_line(int fd)
{
	static char	*buffer_copy[100];
	char	*output;
	char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!buffer_copy[fd])
		buffer_copy[fd] = ft_strdup("");
	output	= get_line(fd, &buffer, &buffer_copy[fd]);
	free_ptr(&buffer);
	return (output);
}
i/*
int main(void) 
{
	int fd1;

  	fd1 = open("test.txt", O_RDONLY);
	read_and_print_100(fd1);
	close(fd1);
	return 0;
}
*/
