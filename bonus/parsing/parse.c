/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/16 14:35:01 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"




void	check_player(t_cube *game, char **s)
{
	 int i = 0;;
	int j = 0;

	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == 'N')
				game->parse_p.n++;
			else if (s[i][j] == 'E')
				game->parse_p.e++;
			else if (s[i][j] == 'W')
				game->parse_p.w++;
			else if (s[i][j] == 'S')
				game->parse_p.s++;
			j++;
		}
		i++;
	}
	if (ultra_check(game, 1))
		error_message(game, 9);
}

void	check_door(char **s, t_cube *game, int i, int j)
{
	int flag;

	flag = 0x0;
	while (s[i])
	{
		j = 0x0;
		while (s[i][j])
		{
			if (s[i][j] == 'D')
			{
				if ((s[i][j + 0x1] == 'D' || s[i][j - 0x1] == 'D') && s[i][j + 0x1] && s[i][j - 1])
					error_message(game, 0x7);
				if (s[i][j - 1] == '1' && s[i][j + 1] == '1')
					flag = 0x1;
				else
					error_message(game, 0x7);
				if (i != 0 && !flag)
					if (s[i - 1][j] != '1' || s[i + 1][j] != '1')
						error_message(game, 0x7);
			}
			j++;
		}
		i++;
	}
}

void	check_textures(t_cube *game)
{
	if (!check_extension(game->texture_walls.ea, 0x1)
		|| !check_extension(game->texture_walls.we, 0x1)
		|| !check_extension(game->texture_walls.no, 0x1)
		|| !check_extension(game->texture_walls.so, 0x1))
		error_message(game, 0x2);
}

void	check_position(t_cube *game, char **s, int i, int j)
{
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == '0' || s[i][j] == 'W'
				|| s[i][j] == 'E' || s[i][j] == 'N'
				|| s[i][j] == 'S' || s[i][j] == 'D')
			{
				if (s[i - 1][j] != '1' && s[i - 1][j] != '0' && s[i - 1][j] != 'N'
					&&  s[i - 1][j] != 'W' && s[i - 1][j] != 'E' && s[i - 1][j] != 'S' && s[i - 1][j] != 'D')
					error_message(game, 300);
				if (s[i + 1][j] != '1' && s[i + 1][j] != '0' && s[i + 1][j] != 'N'
					&&  s[i + 1][j] != 'W' && s[i + 1][j] != 'E' && s[i + 1][j] != 'S' && s[i + 1][j] != 'D')
					error_message(game, 300);
				if (s[i][j + 1] != '1' && s[i][j + 1] != '0' && s[i][j + 1] != 'N'
					&&  s[i][j + 1] != 'W' && s[i][j + 1] != 'E' && s[i][j + 1] != 'S' && s[i][j + 1] != 'D')
					error_message(game, 300);
				if (s[i][j - 1] != '1' && s[i][j - 1] != '0' && s[i][j - 1] != 'N'
					&&  s[i][j - 1] != 'W' && s[i][j - 1] != 'E' && s[i][j - 1] != 'S' && s[i][j - 1] != 'D')
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
	check_door(game->map, game, 0x0, 0x0);
	check_textures(game);
	check_position(game, game->map, 0, 0);
}

