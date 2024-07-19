/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/01 17:16:14 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_extension(char *file)
{
	int	i;

	i = 0x0;
	while (file[i])
	{
		if (file[i] == '.' && file[i + 0x1] == 'c'
			&& file[i + 0x2] == 'u' && file[i + 0x3] == 'b' && file[i + 0x4] == '\0')
			return (0x1);
		i++;
	}
	return (0x0);
}

char	*fix_the_map(char *s, int i, int flag, int j)
{
	char	*str;
	char	*tmp;

	tmp = ft_strtrim(s, " ");
	while (tmp[i++])
	{
		if (tmp[i] == 32 || tmp[i] == 9)
			flag = 0x1;
	}
	if (flag == 0x1)
	{
		i = 0x0;
		str = ft_calloc(0x1, ft_strlen(s) + 0x1);
		if (!str)
			return (NULL);
		while (tmp[i++])
		{
			if (!(tmp[i] == 32 || tmp[i] == 9))
				str[j++] = tmp[i];
		}
	}
	if (flag)
		return (str);
	return (tmp);
}

int	get_length_heigth(char **str, int mode, int i)
{
	if (!mode)
	{
		while (str[i])
			i++;
	}
	if (mode)
	{
		while (str[mode][i])
			i++;
	}
	return (i);
}

int	check_walls(char *s, int i, int length)
{
	int	j;

	j = 0x0;
	if (s[0x0] != '1' || s[ft_strlen(s) - 0x1] != '1')
		return (0x1);
	if (i == 0x6 || i == (length - 0x1))
	{
		while (s[j])
			if (s[j++] != '1')
				return (0x1);
	}
	return (0x0);
}

void	check_valid_members(t_cube *game, int i, int j)
{
	char	*str;

	while (game->map_2d[i])
	{
		j = 0;
		if (i > 5)
		{
			str = fix_the_map(game->map_2d[i], 0x0, 0x0, 0x0);
			if (check_walls(str, i, get_length_heigth(game->map_2d, 0x0, 0x0)))
					error_message(game, 0x4);
			while (str[j])
			{
				if (!(str[j] == '0'
					|| str[j] == '1'
					|| str[j] == 'N'
					|| str[j] == 'S'
					|| str[j] == 'W'
					|| str[j] == 'E'))
					error_message(game, 0x4);
				j++;
			}
			free (str);
		}
		i++;
	}
}

void	check_texture_intra(t_cube *game, int i, int count)
{
	char	*str;

	while (game->map_2d[i] && i < 0x6)
	{
		str = ft_substr(game->map_2d[i], 0x0,  2);
		if (!ft_strcmp(str, "NO")
			|| !ft_strcmp(str, "SO")
			|| !ft_strcmp(str, "EA")
			|| !ft_strcmp(str, "C ")
			|| !ft_strcmp(str, "F ")
			|| !ft_strcmp(str, "WE"))
			count++;
		free (str);
		i++;
	}
	if (count != 0x6)
		error_message(game, 0x4);
}

void	parse(int ac, char *file, t_cube *game)
{
	if (ac <= 1 || ac >= 3)
		error_message(game, 0x1);
	if (check_extension(file) == 0)
		error_message(game, 0x2);
	game->map_2d = read_map_from_file(file);
	if (!game->map_2d)
		error_message(game, 0x3);


	// check_texture_intra(game, 0x0, 0x0);
	// check_valid_members(game, 0x0, 0x0);


	int i  = 0;
	puts("\n\n\n--the map--\n\n\n");
	while (game->map_2d[i])
		printf("%s\n", game->map_2d[i++]);
	puts("good\n");
}

