/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:46:20 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 17:55:24 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	check_view(t_cube *game, t_ray *ray)
{
	if (game->map[(int)(ray->wall_y / BOX_SIZE)][(int)(ray->wall_x
			/ BOX_SIZE)] == 'D')
		game->img_wall = game->png.door;
	else
	{
		if (!ray->hit_v)
		{
			if (ray->is_facingup)
				game->img_wall = game->png.so;
			else if (ray->is_facingdown)
				game->img_wall = game->png.no;
		}
		else
		{
			if (ray->is_facingleft)
				game->img_wall = game->png.ea;
			if (ray->is_facingright)
				game->img_wall = game->png.we;
		}
	}
	return (game->img_wall->width / BOX_SIZE);
}

void	draw_wall_one(t_cube *game, t_ray *ray)
{
	ray->draws.wall_heigth = (BOX_SIZE / (ray->distance * cos(game->rotation_angle - ray->ray_angle))) * ((WINDOW_WIDTH / 2) / tan(PI / 6));
	ray->draws.top = ft_max((WINDOW_HEIGTH / 2) - (ray->draws.wall_heigth / 2), 0);
	ray->draws.bottom = ft_min((WINDOW_HEIGTH / 2) + (ray->draws.wall_heigth / 2),
			WINDOW_HEIGTH);
	get_x(game, ray);
	ray->draws.i = ray->draws.top;
	ray->draws.butt = ray->draws.bottom;
	ray->draws.topp = ray->draws.top;
	ray->draws.incr = 0;
	while (ray->draws.incr++ < ray->draws.topp)
		mlx_put_pixel(game->img, ray->index, ray->draws.incr,
			ft_color(game->colors.r_c, game->colors.g_c, game->colors.b_c,
				255));
	ray->draws.incr = WINDOW_HEIGTH;
	while (ray->draws.incr > ray->draws.butt)
	{
		if (ray->draws.butt < 0)
			ray->draws.butt = 0;
		mlx_put_pixel(game->img, ray->index, ray->draws.butt,
			ft_color(game->colors.r_f, game->colors.g_f, game->colors.b_f,
				255));
		ray->draws.butt++;
	}
}
