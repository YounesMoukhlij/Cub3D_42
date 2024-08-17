/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:04 by abechcha          #+#    #+#             */
/*   Updated: 2024/08/13 16:30:03 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_draw_square(t_cube *game, int x, int y)
{
	int	pixel;
	int	pixel1;

	pixel = 0;
	pixel1 = 0;
	while (pixel < BOX_SIZE - 1)
	{
		pixel1 = 0;
		while (pixel1 < BOX_SIZE - 1)
		{
			mlx_put_pixel(game->img, y + pixel1, x + pixel, 0xFF0000FF);
			pixel1++;
		}
		pixel++;
	}
}

void	ft_draw_floor(t_cube *game, int x, int y)
{
	int	pixel;
	int	pixel1;

	pixel = 0;
	pixel1 = 0;
	while (pixel < BOX_SIZE)
	{
		pixel1 = 0;
		while (pixel1 < BOX_SIZE)
		{
			mlx_put_pixel(game->img, y + pixel1, x + pixel, 0xFFFFFFFF);
			pixel1++;
		}
		pixel++;
	}
}

void	ft_get_player_position(t_cube *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				game->player_x = (i * BOX_SIZE) + BOX_SIZE / 2;
				game->player_y = (j * BOX_SIZE) + BOX_SIZE / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}
