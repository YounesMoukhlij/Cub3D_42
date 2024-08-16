/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:48:17 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/16 14:43:39 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_calcule_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	clear_player(t_cube *game)
{
	int	pixel;
	int	pixel1;

	pixel	= 0;
	pixel1	= 0;
	while (pixel < PLAYER_SIZE)
	{
		pixel1 = 0;
		while (pixel1 < PLAYER_SIZE)
		{
			mlx_put_pixel(game->img, game->player_y + pixel1, game->player_x
					+ pixel, 0xFFFFFF);
			pixel1++;
		}
		pixel++;
	}
}

int	check_colesion(t_cube *game, int x, int y)
{
	int	y1;
	int	x1;
	int	i;

	{
		if (x / BOX_SIZE > game->map_widht || y / BOX_SIZE > game->map_height)
			return (0);
		i = 0;
		while (i < 360)
		{
			x1 = (x + sin(i * (PI / 180)) * 40);
			y1 = (y + cos(i * (PI / 180)) * 40);
			if (game->map[y1 / BOX_SIZE][x1 / BOX_SIZE])
			{
				if (game->map[y1 / BOX_SIZE][x1 / BOX_SIZE] == '1')
					return (0);
			}
			i += 2;
		}
		return (1);
	}
}

int	ft_check_walls(t_cube *game, int x, int y)
{
	int	test;

	x = x / BOX_SIZE;
	y = y / BOX_SIZE;
	test = ft_strlen(game->map[y]);
	if (x > test || y > game->map_height / BOX_SIZE)
		return (0);
	if (game->map[y][x])
	{
		if (game->map[y][x] != '1')
			return (1);
	}
	return (0);
}

