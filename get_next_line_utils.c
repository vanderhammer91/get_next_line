/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:30:09 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/23 15:09:39 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}	
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
			return ((char *)ptr);
		ptr++;
	}
	if (*ptr == (unsigned char)c)
		return ((char *)ptr);
	return (NULL);
}

char	*ft_strdup(char *src)
{
	char	*output;
	int		i;

	output = (char *) malloc(ft_strlen(src) + 1);
	if (!(output))
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		output[i] = src[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;
	size_t	s_len;

	if (!s)
		return ((char *)s);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	output = (char *) malloc(len + 1);
	if (!(output))
		return (NULL);
	i = 0;
	while (i < len)
	{
		output[i] = s[i + start];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	output = (char *) malloc(len);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		output[i + j] = s2[j];
		j++;
	}
	output[i + j] = '\0';
	return (output);
}
