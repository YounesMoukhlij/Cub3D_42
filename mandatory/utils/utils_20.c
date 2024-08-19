/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_20.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:53:55 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 17:56:18 by abechcha         ###   ########.fr       */
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
	(void)ray;
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
			ft_color(game->colors.r_c, game->colors.g_c,
				game->colors.b_c, 255));
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
