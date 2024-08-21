/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:22:02 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/21 14:07:25 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void    draw_plus(t_cube *game, t_ray *ray)
{
    ray->draws.dis = ray->draws.i + (ray->draws.wall_heigth / 2) - (WINDOW_HEIGTH / 2);
  	game->offset_y = ray->draws.dis * ((float)BOX_SIZE / ray->draws.wall_heigth) / BOX_SIZE;
    ray->draws.j = ((int)(game->offset_x * game->img_wall->width)
        + (int)(game->offset_y * game->img_wall->height) * game->img_wall->width) * 4;
    ray->draws.r = game->img_wall->pixels[ray->draws.j];
    ray->draws.g = game->img_wall->pixels[ray->draws.j + 1];
    ray->draws.b = game->img_wall->pixels[ray->draws.j + 2];
    ray->draws.a = game->img_wall->pixels[ray->draws.j + 3];
}

void    ft_draw_wall(t_cube *game, t_ray *ray)
{
    draw_wall_one(game, ray);
    ray->draws.i = ray->draws.top;
    if (ray->hit_v)
        game->offset_x = fmod(ray->wall_y , BOX_SIZE) / BOX_SIZE;
    else
        game->offset_x = fmod(ray->wall_x , BOX_SIZE) / BOX_SIZE;
    while (ray->draws.i < ray->draws.bottom)
    {
        check_view(game, ray);
        draw_plus(game , ray);
        mlx_put_pixel(game->img, ray->index, ray->draws.i,
            ft_color(ray->draws.r, ray->draws.g, ray->draws.b,
                ray->draws.a));
        ray->draws.i++;
    }
}

void	draw_line_dda(t_cube *game, int i, int colum)
{
    t_ray   ray;

	ray.ray_angle = (game->rotation_angle - (game->field_of_view_angle / 2));
	while (i < game->num_ray)
	{
		ray_cast(colum, game , &ray);
		ray.ray_angle += (game->field_of_view_angle / game->num_ray);
		i++;
		colum++;
	}
    i = 0;
    while (i < game->num_ray)
	{
		if (i > 0 && i < game->num_ray - 1)
        {
            if (game->arr[i -1].hit_v && game->arr[i + 1].hit_v)
                game->arr[i].hit_v = 1;
            if (!game->arr[i -1].hit_v && !game->arr[i + 1].hit_v)
                game->arr[i].hit_v = 0;
        }
	    ft_draw_wall(game, &game->arr[i]);
		i++;
	}
}

int	check_me(int x, int y, int width, int heigth)
{
	if (x / BOX_MINI >= 0 && x / BOX_MINI <= width / BOX_SIZE && y
		/ BOX_MINI >= 0 && y / BOX_MINI <= heigth / BOX_SIZE)
		return (0x1);
	return (0x0);
}

