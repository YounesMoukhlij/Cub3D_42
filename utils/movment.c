/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:04 by abechcha          #+#    #+#             */
/*   Updated: 2024/07/27 14:20:57 by abechcha         ###   ########.fr       */
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
		while(pixel1< box_size-1){
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
    while(game->map_2d[i])
    {
        j = 0;
        while(game->map_2d[i][j])
        {
            if (game->map_2d[i][j] == 'N' || game->map_2d[i][j] == 'S' || game->map_2d[i][j] == 'W' ||game->map_2d[i][j] == 'E')
            {
                game->player_x = i * box_size;
                game->player_y = j * box_size;

                return ;
            }
            j++;
        }
        i++;
    }
}