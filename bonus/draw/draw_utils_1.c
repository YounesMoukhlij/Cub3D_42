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
	(void)ray;
	if (game->map[(int)(ray->wall_y / BOX_SIZE)][(int)(ray->wall_x
			/ BOX_SIZE)] == 'D')
		game->img_wall = game->png.door;
	else
	{
		if (!game->hit_v)
		{
			if (game->is_facingup)
				game->img_wall = game->png.so;
			else if (game->is_facingdown)
				game->img_wall = game->png.no;
		}
		else
		{
			if (game->is_facingleft)
				game->img_wall = game->png.ea;
			if (game->is_facingright)
				game->img_wall = game->png.we;
		}
	}
	return (game->img_wall->width / BOX_SIZE);
}

void	draw_wall_one(t_cube *game, t_ray *ray)
{
	game->draws.wall_heigth = (BOX_SIZE / (ray->distance
				* cos(game->rotation_angle - game->ray_angle))) * ((WINDOW_WIDTH
				/ 2) / tan(PI / 6));
	game->draws.top = ft_max((WINDOW_HEIGTH / 2) - (game->draws.wall_heigth / 2), 0);
	game->draws.bottom = ft_min((WINDOW_HEIGTH / 2) + (game->draws.wall_heigth / 2),
			WINDOW_HEIGTH);
	get_x(game, ray);
	game->draws.i = game->draws.top;
	game->draws.butt = game->draws.bottom;
	game->draws.topp = game->draws.top;
	game->draws.incr = 0;
	while (game->draws.incr++ < game->draws.topp)
		mlx_put_pixel(game->img, ray->index, game->draws.incr,
			ft_color(game->colors.r_c, game->colors.g_c, game->colors.b_c,
				255));
	game->draws.incr = WINDOW_HEIGTH;
	while (game->draws.incr > game->draws.butt)
	{
		if (game->draws.butt < 0)
			game->draws.butt = 0;
		mlx_put_pixel(game->img, ray->index, game->draws.butt,
			ft_color(game->colors.r_f, game->colors.g_f, game->colors.b_f,
				255));
		game->draws.butt++;
	}
}

// void ft_handle_image(t_cube *game , t_ray *ray , int x)
// {
// 	while(x > 0){
// 		game->draws.j = ((game->offset_x + game->offset_y * BOX_SIZE) * 4);
// 		game->draws.r = game->img_wall->pixels[game->draws.j];
// 		game->draws.g = game->img_wall->pixels[game->draws.j + 1];
// 		game->draws.b = game->img_wall->pixels[game->draws.j + 2];
// 		game->draws.a = game->img_wall->pixels[game->draws.j + 3];
// 		mlx_put_pixel(game->img, ray->index, game->draws.i,
// 			ft_color(game->draws.r, game->draws.g, game->draws.b,
// 			game->draws.a));
// 		x--;
// 	}
// }
