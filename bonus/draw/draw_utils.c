/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:22:02 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 17:55:14 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_plus(t_cube *game)
{
	game->draws.dis = game->draws.i - WINDOW_HEIGTH / 2
		+ game->draws.wall_heigth / 2;
	game->offset_y = game->draws.dis * ((float)BOX_SIZE
			/ game->draws.wall_heigth);
	game->draws.j = ((game->offset_x + game->offset_y * BOX_SIZE) * 4);
	game->draws.r = game->img_wall->pixels[game->draws.j];
	game->draws.g = game->img_wall->pixels[game->draws.j + 1];
	game->draws.b = game->img_wall->pixels[game->draws.j + 2];
	game->draws.a = game->img_wall->pixels[game->draws.j + 3];
}

void	ft_draw_wall(t_cube *game, t_ray *ray, int z, int x)
{
	draw_wall_one(game, ray);
	game->draws.i = game->draws.top;
	while (game->draws.i < game->draws.bottom)
	{
		z = check_view(game, ray);
		if (z == 0)
			x = BOX_SIZE / game->img_wall->width;
		if (z)
		{
			draw_plus(game);
			mlx_put_pixel(game->img, ray->index, game->draws.i,
				ft_color(game->draws.r, game->draws.g, game->draws.b,
					game->draws.a));
			game->draws.i += z;
		}
		else
		{
			ft_handle_image(game, ray, x);
			game->draws.i++;
		}
	}
}

void	draw_line_dda(t_cube *game)
{
	int	i;
	int	colun;

	colun = 0;
	i = 0;
	game->ray_angle = (game->rotation_angle - (game->field_of_view_angle / 2));
	while (i < game->num_ray)
	{
		ray_cast(colun, game);
		game->ray_angle += (game->field_of_view_angle / game->num_ray);
		i++;
		colun++;
	}
}

int	check_me(int x, int y, int width, int heigth)
{
	if (x / BOX_MINI >= 0 && x / BOX_MINI <= width / BOX_SIZE && y
		/ BOX_MINI >= 0 && y / BOX_MINI <= heigth / BOX_SIZE)
		return (0x1);
	return (0x0);
}
