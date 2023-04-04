/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:04:13 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/23 15:13:03 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
#endif

char	*get_next_line(int fd);

// Utility functions.
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *string, int searchedChar);
char	*ft_strdup(const char *s1);
char	*ft_substr(char	const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
