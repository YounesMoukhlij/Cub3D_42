/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:26 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/23 16:46:45 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_find_nl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
			return (i + 1);
		i++;
	}
	if ((char)c == s[i])
		return (i + 1);
	return (0);
}


static char	*ft_read_fd(int fd, char *rest)
{
	int		readed_bytes;
	char	*tmp;

	readed_bytes = 1;
	tmp = ft_malloc((sizeof(char) * BUFFER_SIZE) + 1, 1);
	if (!tmp)
		return (NULL);
	while (1)
	{
		if (ft_find_nl(rest, '\n'))
			break ;
		readed_bytes = read(fd, tmp, BUFFER_SIZE);
		if (readed_bytes == -1)
			return (NULL);
		tmp[readed_bytes] = 0;
		if (readed_bytes == 0)
			break ;
		rest = ft_strjoin(rest, tmp);
	}
	return (rest);
}

static char	*ft_line_extract(char *line, char *rest)
{
	int	i;
	int	j;

	j = 0;
	if (!rest || *rest == '\0')
		return (NULL);
	i = ft_find_nl(rest, '\n');
	if (!i)
		i = ft_strlen(rest);
	line = ft_malloc(i + 1, 1);
	while (j < i)
	{
		line[j] = rest[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_buckup(char *rest)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	tmp = NULL;
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	if (rest[i] == '\0')
		return (NULL);
	tmp = ft_malloc((ft_strlen(&rest[i])) + 1, 1);
	while (rest[i])
		tmp[j++] = rest[i++];
	tmp[j] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
 	if (!rest)
	{
		rest = ft_malloc(1, 1);
		if (!rest)
			return (NULL);
		rest[0] = '\0';
	}
	rest = ft_read_fd(fd, rest);
	if (rest == NULL)
		return (NULL);
	line = ft_line_extract(line, rest);
	if (!line)
		return (NULL);
	rest = ft_buckup(rest);
	return (line);
}
