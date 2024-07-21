/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:27:40 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/21 18:28:54 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	first_check(char *file)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd == -0x1)
		error_reading_map(0x1);
	str = get_next_line(fd);
	close (fd);
	if (!str)
		return (error_reading_map(0x2));
}

void	check_during_read(char *str, int mode)
{
	if (mode == 0)
	{
		if ((str[0] == '\n' && str[1] == '\0') || str[0] == '\0')
			return (error_reading_map(0x2));
		if (str[ft_strlen(str)] == '\n')
			return (error_reading_map(0x2));
	}
	if (mode == 1)
		if (str[ft_strlen(str) - 1] == '\n')
			return (error_reading_map(0x2));
}

char	**read_map_from_file(char *map_1d)
{
	int		fd;
	char	*s_read;
	char	*str;
	char	**s;

	first_check(map_1d);
	str = ft_malloc(0x1,0x1);
	fd = open(map_1d, O_RDONLY);
	while (0x1)
	{
		s_read = get_next_line(fd);
		if (s_read == NULL)
			break ;
		str = ft_strjoin(str, s_read);
		if (!str)
			return (NULL);
	}
	close (fd);
	return (s = ft_split(str, '\n'), s);
}
