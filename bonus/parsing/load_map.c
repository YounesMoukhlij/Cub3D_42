/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:27:40 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 11:07:00 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	first_check(char *file)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd == -0x1)
		error_reading_map(0x1);
	str = get_next_line(fd);
	close(fd);
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

int	small_check(char *s, int i, int flag)
{
	char	*str;

	if (ft_strlen(s) >= 0x2)
	{
		str = ft_substr(s, 0x0, 0x2);
		if (!ft_strcmp(str, "SO") || !ft_strcmp(str, "NO") || !ft_strcmp(str,
				"F ") || !ft_strcmp(str, "C ") || !ft_strcmp(str, "EA")
			|| !ft_strcmp(str, "WE"))
			return (0x0);
	}
	if (ft_strlen(s) >= 0x1)
	{
		while (s[i])
		{
			if (s[i] == '1' || s[i] == '0' || s[i] == 'S' || s[i] == 'N'
				|| s[i] == 'E' || s[i] == 'W')
				flag++;
			i++;
		}
	}
	if ((flag == ft_strlen(s) - 1) && ft_strcmp(s, "\n"))
		return (0x1);
	return (0x0);
}

char	**read_map_from_file(char *map_1d, int fd, int is_map)
{
	char	*s_read;
	char	*str;

	first_check(map_1d);
	str = malloc(1);
	fd = open(map_1d, O_RDONLY);
	while (0x1)
	{
		s_read = get_next_line(fd);
		if (s_read == NULL)
			break ;
		if (!is_map)
		{
			if (small_check(ft_strtrim(s_read, " "), 0x0, 0x0))
				is_map = 0x1;
		}
		if (is_map && s_read[0x0] == '\n')
			return (close(fd), NULL);
		str = ft_strjoin(str, s_read);
		if (!str)
			return (close(fd), NULL);
	}
	close(fd);
	return (ft_split(str, '\n'));
}
