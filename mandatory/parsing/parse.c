/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 15:16:52 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_player(t_cube *game, char **s)
{
	int	i;
	int	j;

	i = 0;
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
			if (peter_csezsh(s, i, j))
			{
				if (game->player_vision == 1)
					if (case_1(s, i, j))
						error_message(game, 11);
				if (game->player_vision == 2)
					if (case_2(s, i, j))
						error_message(game, 11);
				if (game->player_vision == 3)
					if (case_3(s, i, j))
						error_message(game, 11);
				if (game->player_vision == 4)
					if (case_4(s, i, j))
						error_message(game, 11);
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
}
