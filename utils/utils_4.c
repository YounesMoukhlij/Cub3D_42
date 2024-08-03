/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:48:17 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/03 18:49:10 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int ft_calcule_distance(float x1, float y1, float x2 , float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void clear_player(t_cube *game)
{
	int pixel;
	pixel = 0;
	int pixel1 = 0;
	while(pixel < player_size)
	{
		pixel1 = 0;
		while(pixel1< player_size){
			mlx_put_pixel(game->img, game->player_y + pixel1 , game->player_x + pixel, 0xFFFFFF);
			pixel1++;
		}
		pixel++;
	}
}
int ft_check_walls(t_cube *game , int x , int y)
{
	x = x / BOX_SIZE;
	y = y / BOX_SIZE;
	if (x > game->map_widht / BOX_SIZE || y > game->map_height / BOX_SIZE)
		return 0;
	if (game->map[y][x])
	{
		if (game->map[y][x] != '1' )
			return 1;
	}
	return 0;
}
void ft_test(t_cube *game)
{
	int i = 0;
	while(i < 1000)
	{
		int j = 0;
		while(j < 1500)
		{
			mlx_put_pixel(game->img, j  , i, ft_color(0, 0, 0, 255));
			j++; 
		}
		i++;
	}
}
void ft_test_1(t_cube *game)
{
	int i = 0;
	while(i < 200)
	{
		int j = 0;
		while(j < 200)
		{
			mlx_put_pixel(game->img_mini_map, j  , i, ft_color(0, 0, 0, 255));
			j++; 
		}
		i++;
	}
}