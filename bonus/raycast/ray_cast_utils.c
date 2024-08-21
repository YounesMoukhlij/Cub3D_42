/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:26:17 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 14:16:02 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	fifth_chapter(t_cube *game, t_ray *ray)
{
	(void)ray;
	while (game->r_tools.next_vertical_x >= 0
		&& game->r_tools.next_vertical_x <= game->map_widht
		&& game->r_tools.next_vertical_y >= 0
		&& game->r_tools.next_vertical_y <= game->map_height)
	{
		if (!ft_check_walls(game, game->r_tools.next_vertical_x,
				game->r_tools.next_vertical_y) || ft_check_door(game,
				game->r_tools.next_vertical_x, game->r_tools.next_vertical_y))
		{
			game->r_tools.found_vertical_wall = 1;
			game->r_tools.wall_vertical_x = game->r_tools.next_vertical_x;
			game->r_tools.wall_vertical_y = game->r_tools.next_vertical_y;
			break ;
		}
		else
		{
			game->r_tools.next_vertical_x += game->r_tools.step_x;
			game->r_tools.next_vertical_y += game->r_tools.step_y;
		}
	}
}

void	sixth_extra_chapter(t_cube *game, t_ray *ray)
{

	if (game->r_tools.horizontal_wall_distance
		< game->r_tools.vertical_wall_distance)
	{
		ray->wall_x = game->r_tools.wall_horizontal_x;
		ray->wall_y = game->r_tools.wall_horizontal_y;
		ray->distance = game->r_tools.horizontal_wall_distance;
		ray->hit_v = 0;
	}
	else
	{
		ray->wall_x = game->r_tools.wall_vertical_x;
		ray->wall_y = game->r_tools.wall_vertical_y;
		ray->distance = game->r_tools.vertical_wall_distance;
		ray->hit_v = 1;
	}
}

void	sixth_chapter(t_cube *game, t_ray *ray)
{
	if (game->r_tools.found_horizontal_wall)
		game->r_tools.horizontal_wall_distance = ft_calcule_distance(
				game->player_y, game->player_x, game->r_tools.wall_horizontal_x,
				game->r_tools.wall_horizontal_y);
	else
		game->r_tools.horizontal_wall_distance = 2147483647;
	if (game->r_tools.found_vertical_wall)
		game->r_tools.vertical_wall_distance = ft_calcule_distance(
				game->player_y, game->player_x, game->r_tools.wall_vertical_x,
				game->r_tools.wall_vertical_y);
	else
		game->r_tools.vertical_wall_distance = 2147483647;
	sixth_extra_chapter(game, ray);
}
