/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 10:16:17 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
		i -= 6;
	}
	if (mode)
	{
		while (str[mode][i])
			i++;
	}
	return (i);
}

char	**final_map(t_cube *game, char **str)
{
	int		i;
	int		j;
	char	**s;

	i = 0x0;
	s = (char **)ft_malloc((game->real_map_heigth + 0x1) * 8, 1);
	if (!s)
		return (NULL);
	j = 0x0;
	while (str[i])
	{
		if (i > 0x5)
		{
			s[j] = fill_chars(game, str[i]);
			if (!s[j++])
				return (NULL);
		}
		i++;
	}
	s[j] = 0;
	return (s);
}

void	check_position(t_cube *game, char **s, int i, int j)
{
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == '0' || s[i][j] == 'W' || s[i][j] == 'E'
				|| s[i][j] == 'N' || s[i][j] == 'S')
			{
				if (s[i - 1][j] != '1' && s[i - 1][j] != '0' && s[i
					- 1][j] != 'N' && s[i - 1][j] != 'W' && s[i - 1][j] != 'E'
					&& s[i - 1][j] != 'S' && s[i - 1][j] != 'D')
					error_message(game, 300);
				if (s[i + 1][j] != '1' && s[i + 1][j] != '0' && s[i
					+ 1][j] != 'N' && s[i + 1][j] != 'W' && s[i + 1][j] != 'E'
					&& s[i + 1][j] != 'S' && s[i + 1][j] != 'D')
					error_message(game, 300);
				if (s[i][j + 1] != '1' && s[i][j + 1] != '0' && s[i][j
					+ 1] != 'N' && s[i][j + 1] != 'W' && s[i][j + 1] != 'E'
					&& s[i][j + 1] != 'S' && s[i][j + 1] != 'D')
					error_message(game, 300);
				if (s[i][j - 1] != '1' && s[i][j - 1] != '0' && s[i][j
					- 1] != 'N' && s[i][j - 1] != 'W' && s[i][j - 1] != 'E'
					&& s[i][j - 1] != 'S' && s[i][j - 1] != 'D')
					error_message(game, 300);
			}
			j++;
		}
		i++;
	}
}

void	parse(int ac, char *file, t_cube *game)
{
	if (ac <= 1 || ac >= 3)
		error_message(game, 0x1);
	if (check_extension(file, 0x0) == 0)
		error_message(game, 0x2);
	game->map_2d = read_map_from_file(file, 0x0, 0x0);
	if (!game->map_2d)
		error_message(game, 0x3);
	init_counter(game);
	heigth_width(game);
	check_texture_intra(game, 0x0);
	check_valid_members(game, 0x0, 0x0);
	player_vision(game->map_2d, game);
	parse_entry(game, 0x0);
	ft_load_textures(game);
	game->map = final_map(game, game->map_2d);
	check_player(game, game->map);
	check_textures(game);
	check_position(game, game->map, 0, 0);
//remove any condition that rolation of D 
//eleemnt on mandatory parsing and be man 
}
