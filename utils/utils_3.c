/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:47:31 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/03 18:48:28 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int 	ft_color(int  r, int  g, int  b, int  a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	ft_max(float a, float b)
{
	if (a < b)
		return (b);
	return (a);
}
float	ft_min(float a, float b)
{
	if (a > b)
		return (b);
	return (a);
}

void	get_x(t_cube *game, t_ray *ray)
{
	if (game->hit_v)
		game->offset_x = (int)ray->wall_y % BOX_SIZE;
	else
		game->offset_x = (int)ray->wall_x % BOX_SIZE;
}



float ft_normalize(float angel)
{
	angel = fmod(angel , 2 * PI);
	if (angel < 0)
		angel = (2 * PI) + angel;
	return angel;
}


