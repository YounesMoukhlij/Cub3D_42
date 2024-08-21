/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_20.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:53:55 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/21 14:25:49 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	parse_numbers(char *s)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = ft_split(ft_strtrim(s, " "), ',');
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!(str[i][j] >= '0' && str[i][j] <= '9'))
				return (1);
			j++;
		}
		if (ft_atoi(str[i]) > 255 || ft_atoi(str[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_view(t_cube *game, t_ray *ray)
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
	return (game->img_wall->width / BOX_SIZE);
}

void	draw_wall_one(t_cube *game, t_ray *ray)
{
	ray->draws.wall_heigth = (BOX_SIZE / (ray->distance
				* cos(game->rotation_angle - ray->ray_angle))) * ((WINDOW_WIDTH
				/ 2) / tan(PI / 6));
	ray->draws.top = ft_max((WINDOW_HEIGTH / 2) - (ray->draws.wall_heigth / 2),
			0);
	ray->draws.bottom = ft_min((WINDOW_HEIGTH / 2) + (ray->draws.wall_heigth
				/ 2), WINDOW_HEIGTH);
	get_x(game, ray);
	ray->draws.i = ray->draws.top;
	ray->draws.butt = ray->draws.bottom;
	ray->draws.topp = ray->draws.top;
	ray->draws.incr = 0;
	while (ray->draws.incr < ray->draws.topp)
	{
		mlx_put_pixel(game->img, ray->index, ray->draws.incr,
			ft_color(game->colors.r_c, game->colors.g_c, game->colors.b_c,
				255));
		ray->draws.incr++;
	}
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

char	**final_map(t_cube *game, char **str)
{
	int		i;
	int		j;
	char	**s;

	i = 0x0;
	s = (char **)ft_malloc((game->real_map_heigth + 0x1) * 8, 1);
	if (!s)
		return (NULL);
	j = 0x0;
	while (str[i])
	{
		if (i > 0x5)
		{
			s[j] = fill_chars(game, str[i]);
			if (!s[j++])
				return (NULL);
		}
		i++;
	}
	s[j] = 0;
	return (ft_maping(game, s, 0));
}
