/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:49:44 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/03 18:50:06 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int ft_check_door(t_cube *game , int next_horizontal_x , int next_horizontal_y )
{
	int y = next_horizontal_y - (int)game->player_x;
	int x = next_horizontal_x - (int)game->player_y;
	x = abs(x);
	y = abs(y);
	if (next_horizontal_y / BOX_SIZE > game->map_widht || next_horizontal_x / BOX_SIZE > game->map_height)
		return 0;
	if (game->map[(next_horizontal_y / BOX_SIZE)][(next_horizontal_x / BOX_SIZE)] == 'D' && (x > BOX_SIZE / 2 && y > BOX_SIZE / 2))
		return 1;
	return 0;
}

void ft_put_player(t_cube *game)
{
	int pixel;
	pixel = 0;
	int pixel1;
	while(pixel <= player_size_mini_map)
	{
		pixel1 = 0;
		while(pixel1 <= player_size_mini_map)
		{
			mlx_put_pixel(game->img_mini_map,  100 + pixel1, 100 + pixel, 0xFF0000FF);
			pixel1++;
		}
		pixel++;
	}
}


void ft_drawing_map(t_cube *game)
{
	ft_drawing_map_element(game);
	ft_put_player(game);
}