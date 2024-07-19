/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:27:40 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/01 15:49:27 by youmoukh         ###   ########.fr       */
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
		return (free (str), error_reading_map(0x2));
	free (str);
}

void	check_during_read(char *str, int mode)
{
	if (mode == 0)
	{
		if ((str[0] == '\n' && str[1] == '\0') || str[0] == '\0')
			return (free(str), error_reading_map(0x2));
		if (str[ft_strlen(str)] == '\n')
			return (free(str), error_reading_map(0x2));
	}
	if (mode == 1)
		if (str[ft_strlen(str) - 1] == '\n')
			return (free(str), error_reading_map(0x2));
}

char	**read_map_from_file(char *map_1d)
{
	int		fd;
	char	*s_read;
	char	*final_tmp;
	char	**final;

	first_check(map_1d);
	final_tmp = ft_strdup("");
	fd = open(map_1d, O_RDONLY);
	while (0x1)
	{
		s_read = get_next_line(fd);
		if (s_read == NULL)
			break ;
		final_tmp = ft_strjoin(final_tmp, s_read);
		if (!final_tmp)
			return (free (final_tmp), free (s_read), NULL);
		free (s_read);
	}
	close (fd);
	return (final = ft_split(final_tmp, '\n'), free (final_tmp), final);
}
