/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_20.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:53:55 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 12:57:43 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	player_vision(char **s, t_cube *game)
{
	int	i;
	int	j;

	i = 6;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == 'N')
				game->rotation_angle = (3 * PI) / 2;
			else if (s[i][j] == 'S')
				game->rotation_angle = PI / 2;
			else if (s[i][j] == 'W')
				game->rotation_angle = PI;
			else if (s[i][j] == 'E')
				game->rotation_angle = 0;
			j++;
		}
		i++;
	}
}

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

char	*check_chars(char *s)
{
	if (s[0] == 'C')
		if (ft_strcmp(s, "C "))
			return (NULL);
	if (s[0] == 'F')
		if (ft_strcmp(s, "F "))
			return (NULL);
	if (s[0] == 'N')
		if (ft_strcmp(s, "NO"))
			return (NULL);
	if (s[0] == 'S')
		if (ft_strcmp(s, "SO"))
			return (NULL);
	if (s[0] == 'W')
		if (ft_strcmp(s, "WE"))
			return (NULL);
	if (s[0] == 'E')
		if (ft_strcmp(s, "EA"))
			return (NULL);
	return (s);
}

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
			ft_color(game->colors.r_c, game->colors.g_c,
				game->colors.b_c, 255));
	game->draws.incr = WINDOW_HEITH;
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
