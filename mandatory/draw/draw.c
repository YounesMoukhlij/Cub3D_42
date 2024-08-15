/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:32:30 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/13 18:27:08 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_view(t_cube *game, t_ray *ray)
{
	(void)ray;
	if (game->map[(int)(ray->wall_y / BOX_SIZE)][(int)(ray->wall_x / BOX_SIZE)] == 'D')
		game->img_wall = game->png.door;
	else
	{
		if (!game->hit_v)
		{
			if (game->is_facingup)
				game->img_wall = game->png.so;
			else if (game->is_facingDown)
				game->img_wall = game->png.no;
		}
		else
		{
			if (game->is_facingLeft)
				game->img_wall = game->png.ea;
			if (game->is_facingRight)
				game->img_wall = game->png.we;
		}
	}
}

void	ft_draw_wall(t_cube *game, t_ray *ray)
{
	game->draws.wall_heigth = (BOX_SIZE / (ray->distance
				* cos(game->rotation_angle - game->ray_angle))) * ((WINDOW_WIDTH
				/ 2) / tan(PI / 6));
	game->draws.top = ft_max((1000 / 2) - (game->draws.wall_heigth / 2), 0);
	game->draws.bottom = ft_min((1000 / 2) + (game->draws.wall_heigth / 2),
			1000);
	get_x(game, ray);
	game->draws.i = game->draws.top;
	game->draws.butt = game->draws.bottom;
	game->draws.topp = game->draws.top;
	game->draws.incr = 0;
	while (game->draws.incr++ < game->draws.topp)
		mlx_put_pixel(game->img, ray->index, game->draws.incr,
				ft_color(game->colors.r_c, game->colors.g_c, game->colors.b_c,
					255));
	game->draws.incr = WINDOW_HEITH;
	while (game->draws.incr > game->draws.butt++)
	{
		mlx_put_pixel(game->img, ray->index, game->draws.butt,
				ft_color(game->colors.r_f, game->colors.g_f, game->colors.b_f,
					255));
	}
	game->draws.i = game->draws.top;
	while (game->draws.i < game->draws.bottom)
	{
		check_view(game, ray);
		game->draws.dis = game->draws.i - WINDOW_HEITH / 2
			+ game->draws.wall_heigth / 2;
		game->offset_y = game->draws.dis * ((float)BOX_SIZE
				/ game->draws.wall_heigth);
		game->draws.j = ((game->offset_x + game->offset_y * BOX_SIZE) * 4);
		game->draws.r = game->img_wall->pixels[game->draws.j];
		game->draws.g = game->img_wall->pixels[game->draws.j + 1];
		game->draws.b = game->img_wall->pixels[game->draws.j + 2];
		game->draws.a = game->img_wall->pixels[game->draws.j + 3];
			mlx_put_pixel(game->img, ray->index, game->draws.i,
				ft_color(game->draws.r, game->draws.g, game->draws.b,
					game->draws.a));
		game->draws.i++;
	}
}

void	ft_draw_line(t_cube *game, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = x1 < x2 ? 1 : -1;
	sy = y1 < y2 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		mlx_put_pixel(game->img_mini_map, x1, y1, ft_color(0, 0, 0, 255));
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
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

void	ft_drawing_map_element(t_cube *game)
{
	int	i;
	int	start_y;
	int	j;
	int	start_x;

	i = 0;
	game->player_y_mini_map = (game->player_x / BOX_SIZE) * BOX_SIZE_MINI_MAP;
	game->player_x_mini_map = (game->player_y / BOX_SIZE) * BOX_SIZE_MINI_MAP;
	start_y = game->player_y_mini_map - 100;
	while (start_y < game->player_y_mini_map + 100)
	{
		j = 0;
		start_x = game->player_x_mini_map - 100;
		while (start_x < game->player_x_mini_map + 100)
		{
			if (start_x / BOX_SIZE_MINI_MAP >= 0 && start_x
				/ BOX_SIZE_MINI_MAP <= game->map_widht / BOX_SIZE && start_y
				/ BOX_SIZE_MINI_MAP >= 0 && start_y
				/ BOX_SIZE_MINI_MAP <= game->map_height / BOX_SIZE)
			{
				if (!game->map[start_y / BOX_SIZE_MINI_MAP][start_x
					/ BOX_SIZE_MINI_MAP])
					break ;
				else if (game->map[start_y / BOX_SIZE_MINI_MAP][start_x
						/ BOX_SIZE_MINI_MAP] == '1')
					mlx_put_pixel(game->img_mini_map, j, i, 0xFF0000FF);
				else if (game->map[start_y / BOX_SIZE_MINI_MAP][start_x
						/ BOX_SIZE_MINI_MAP] == 'D')
					mlx_put_pixel(game->img_mini_map, j, i, ft_color(0, 255, 0,
								255));
				else
					mlx_put_pixel(game->img_mini_map, j, i, 0xFFFFFFFF);
			}
			else
				mlx_put_pixel(game->img_mini_map, j, i, ft_color(0, 0, 0, 255));
			start_x++;
			j++;
		}
		start_y++;
		i++;
	}
}
