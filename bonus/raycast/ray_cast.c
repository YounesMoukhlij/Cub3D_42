/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:33:23 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 19:42:53 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	first_chapter(t_cube *game , t_ray *ray)
{
	game->ray_angle = ft_normalize(game->ray_angle);
	ray->is_facingdown = game->ray_angle > 0 && game->ray_angle < PI;
	ray->is_facingup = !ray->is_facingdown;
	ray->is_facingright = game->ray_angle < (0.5 * PI)
		|| game->ray_angle > (1.5 * PI);
	ray->is_facingleft = !ray->is_facingright;
	game->r_tools.intercept_y = 0;
	game->r_tools.intercept_x = 0;
	game->r_tools.step_x = 0;
	game->r_tools.step_y = 0;
}

void	second_chapter(t_cube *game , t_ray *ray)
{
	game->r_tools.intercept_y = floor((game->player_x / BOX_SIZE)) * BOX_SIZE;
	if (ray->is_facingdown)
		game->r_tools.intercept_y += BOX_SIZE;
	game->r_tools.intercept_x = game->player_y + (game->r_tools.intercept_y
			- game->player_x) / tan(game->ray_angle);
	game->r_tools.step_y = BOX_SIZE;
	if (ray->is_facingup)
		game->r_tools.step_y *= -1;
	game->r_tools.step_x = BOX_SIZE / (tan(game->ray_angle));
	if (ray->is_facingleft && game->r_tools.step_x > 0)
		game->r_tools.step_x *= -1;
	if (ray->is_facingright && game->r_tools.step_x < 0)
		game->r_tools.step_x *= -1;
	game->r_tools.wall_horizontal_y = 0;
	game->r_tools.wall_horizontal_x = 0;
	game->r_tools.found_horizontal_wall = 0;
	game->r_tools.next_horizontal_x = game->r_tools.intercept_x;
	game->r_tools.next_horizontal_y = game->r_tools.intercept_y;
	if (ray->is_facingup)
		game->r_tools.next_horizontal_y--;
}

void	third_chapter(t_cube *game )
{
	while (game->r_tools.next_horizontal_x >= 0
		&& game->r_tools.next_horizontal_x <= game->map_widht
		&& game->r_tools.next_horizontal_y >= 0
		&& game->r_tools.next_horizontal_y <= game->map_height)
	{
		if (!ft_check_walls(game, game->r_tools.next_horizontal_x,
				game->r_tools.next_horizontal_y) || ft_check_door(game,
				game->r_tools.next_horizontal_x,
				game->r_tools.next_horizontal_y))
		{
			game->r_tools.found_horizontal_wall = 1;
			game->r_tools.wall_horizontal_x = game->r_tools.next_horizontal_x;
			game->r_tools.wall_horizontal_y = game->r_tools.next_horizontal_y;
			break ;
		}
		else
		{
			game->r_tools.next_horizontal_x += game->r_tools.step_x;
			game->r_tools.next_horizontal_y += game->r_tools.step_y;
		}
	}
}

void	fourth_chapter(t_cube *game, t_ray *ray)
{
	game->r_tools.found_vertical_wall = 0;
	ray->wall_x = 0;
	ray->wall_y = 0;
	game->r_tools.wall_vertical_y = 0;
	game->r_tools.wall_vertical_x = 0;
	game->r_tools.intercept_x = floor((game->player_y / BOX_SIZE)) * BOX_SIZE;
	if (ray->is_facingright)
		game->r_tools.intercept_x += BOX_SIZE;
	game->r_tools.intercept_y = game->player_x + (game->r_tools.intercept_x
			- game->player_y) * tan(game->ray_angle);
	game->r_tools.step_x = BOX_SIZE;
	if (ray->is_facingleft)
		game->r_tools.step_x *= -1;
	game->r_tools.step_y = BOX_SIZE * (tan(game->ray_angle));
	if (ray->is_facingup && game->r_tools.step_y > 0)
		game->r_tools.step_y *= -1;
	if (ray->is_facingdown && game->r_tools.step_y < 0)
		game->r_tools.step_y *= -1;
	game->r_tools.next_vertical_x = game->r_tools.intercept_x;
	game->r_tools.next_vertical_y = game->r_tools.intercept_y;
	if (ray->is_facingleft)
		game->r_tools.next_vertical_x--;
}

void	ray_cast(int colum, t_cube *game)
{
	t_ray	ray;

	first_chapter(game, &ray);
	second_chapter(game, &ray);
	third_chapter(game);
	fourth_chapter(game, &ray);
	fifth_chapter(game, &ray);
	sixth_chapter(game, &ray);
	ray.index = colum;
	game->was_vertical = 0;
	game->was_vertical = (game->r_tools.vertical_wall_distance
			< game->r_tools.horizontal_wall_distance);
	game->arr[colum] = ray; 
	// ft_draw_wall(game, &ray);
}
