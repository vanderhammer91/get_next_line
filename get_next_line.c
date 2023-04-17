/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:47:02 by ivanderw          #+#    #+#             */
/*   Updated: 2023/04/17 17:29:26 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 
 * 	PROTOTYPE
 *		char	*get_next_line(int fd);
 *
 *	PARAMETERS
 *		fd:	The file descriptor to read from
 *
 *	RETURN VALUE
 *		Read line:	correct behaviour
 *	
 *	NULL: there is nothing else to read, or an error occured.
 *
 *	EXTERNAL FUNCTIONS:
 *		read, malloc, free
 *
 *	DESCRIPTION:
 *		Write a function that returns a line read from a file descriptor.
 *
 *	-------------------------------------------------------------------------
 *
 *	FUNCTION NAME: FT_GET_REMAINING
 *
 *		The function ft_get_remaining extracts the remainder of the line that 
 *		comes after the first occurrence of the newline character. It returns 
 *		this as a newly allocated string.
 *
 *	-------------------------------------------------------------------------
 *
 * 	STEPS
 *	Iterate through `line` until either a newline or the end of the 
 *	string is encountered
 *
 *	If the function encountered either the end of string or a 
 *	single newline, return `NULL`
 *
 *	Extract everything after the newline character into `remaining`
 *
 *	If the `remaining` string is empty, free and set it to `NULL`
 *
 *	Terminate `line` at the newline character
 *
 *	Return `remaining`, which contains everything after the newline 
 *	character
*/
#include "get_next_line.h"

static char	*ft_get_remaining(char *line)
{
	char	*remaining;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	remaining = ft_substr(line, i + 1, (ft_strlen(line) - i));
	if (*remaining == '\0')
	{
		free(remaining);
		remaining = NULL;
	}
	line[i + 1] = '\0';
	return (remaining);
}

/* 	FUNCTION NAME: FT_FIND_NEWLINE:
 *
 *	The function ft_find_newline reads from the file descriptor until it 
 *	finds a newline character. It keeps track of any leftover characters 
 *	from previous reads and appends them to the current buffer. It returns
 *	the resulting string containing the next line in the file.
 *  The function takes a file descriptor (fd), a buffer (buffer),
 *  and a string (to_read) as input.
 *
 *	-------------------------------------------------------------------------
 *
 * 	STEPS
 *	It reads data from fd and stores it in buffer.
 *
 *	The data in buffer is appended to to_read.
 *
 *	The function continues to read data from fd and append it to
 *	to_read until it finds a newlinecharacter (\n) in buffer.
 *
 *	Once a newline character is found, the function stops reading
 *	from fd and returns to_read.
*/
static char	*ft_find_newline(int fd, char *buffer, char *to_read)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!to_read)
			to_read = ft_strdup("");
		temp = to_read;
		to_read = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (to_read);
}

/*	FUNCTION NAME: GET_NEXT_LINE
 *
 * 	The code provided is an implementation of the function get_next_line
 *  that reads a file line by line. The function takes a file descriptor 
 *  as input and returns a string containing the next line in the file. 
 *  It also handles cases where the line is longer than the buffer size,
 *  and any remaining characters are stored in a static variable and 
 *  appended to the next read. The function allocates memory as needed 
 *  and frees any memory it uses.
 *
 *	The function get_next_line initializes a buffer and calls ft_find_newline
 *	to get the next line, this will probably be untrimmed and contain
 *	part of the following line often.
 *	
 *	It then calls ft_get_remaining to extract any remaining characters and 
 *	stores them in a static variable for use in the next function call. 
 *	Finally, it returns the resulting string containing 
 *	the next line in the file (it trims the string by adding a null terminator)
 *	
 *	-------------------------------------------------------------------------
 *
 * 	STEPS
 * 	
 *   The function get_next_line takes a file descriptor and BUFFER_SIZE as 
 *	input.
 *
 *   It allocates memory for a buffer based on the value of BUFFER_SIZE.
 *
 *   The function find_new_line reads from the file descriptor until it 
 *	finds a newline character.
 *
 *   If there is leftover data from a previous read, it is appended to 
 *	the current buffer.
 *
 *   The untrimmed line is sent to ft_find_newline to extract the current 
 *	whole line.
 *
 *   The trimmed line is pointed to by 'my_line' and returned by get_next_line.
 *
 *   Any leftover characters are stored in a static char pointer called 
 *	'to_read' and retained for the next function call.
 */
char	*get_next_line(int fd)
{
	char		*my_line;
	char		*buffer;
	static char	*to_read;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buffer)
		return (NULL);
	my_line = ft_find_newline(fd, buffer, to_read);
	free(buffer);
	buffer = NULL;
	if (!my_line)
	{
		free(to_read);
		to_read = NULL;
		return (my_line);
	}
	to_read = ft_get_remaining(my_line);
	return (my_line);
}

#ifdef _MAIN_

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("testfile.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
#endif
