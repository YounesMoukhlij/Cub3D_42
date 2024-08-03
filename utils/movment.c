/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:04 by abechcha          #+#    #+#             */
/*   Updated: 2024/08/01 11:09:29 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void ft_draw_square(t_cube *game, int x , int y)
{
    int pixel;
	pixel = 0;
	int pixel1 = 0;
	while(pixel < box_size -1)
	{
		pixel1 = 0;
		while(pixel1< box_size-1)
		{
			mlx_put_pixel(game->img , y + pixel1 , x + pixel, 0xFF0000FF);
			pixel1++;
		}
		pixel++;
	}
}

void ft_draw_floor(t_cube *game, int x , int y)
{
    int pixel;
	pixel = 0;
	int pixel1 = 0;
	while(pixel < box_size)
	{
		pixel1 = 0;
		while(pixel1< box_size){
			mlx_put_pixel(game->img , y + pixel1 , x + pixel, 0xFFFFFFFF);
			pixel1++;
		}
		pixel++;
	}
}

void ft_get_player_position(t_cube *game)
{
    int i = 0;
    int j;

    while(game->map[i])
    {
        j = 0;
        while(game->map[i][j])
        {
            if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' ||game->map[i][j] == 'E')
            {
                game->player_x = i * box_size;
                game->player_y = j * box_size;
                game->player_x_mini_map = i * box_size_mini_map;
                game->player_y_mini_map = j * box_size_mini_map;
                return ;
            }
            j++;
        }
        i++;
    }
}
