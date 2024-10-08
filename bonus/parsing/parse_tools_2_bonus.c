/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:07:38 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/21 14:46:29 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	fill_colors(t_cube *game, char *s, int mode)
{
	char	**str;
	int		i;

	i = 0;
	parse_s(game, s, 0);
	str = ft_split(ft_strtrim(s, " "), ',');
	if (!str)
		return ;
	check_color(game, str);
	while (str[i])
	{
		if (!mode && !i)
			game->colors.r_c = ft_atoi(str[i]);
		else if (!mode && i == 1)
			game->colors.g_c = ft_atoi(str[i]);
		else if (!mode && i == 2)
			game->colors.b_c = ft_atoi(str[i]);
		else if (mode && !i)
			game->colors.r_f = ft_atoi(str[i]);
		else if (mode && i == 1)
			game->colors.g_f = ft_atoi(str[i]);
		else if (mode && i == 2)
			game->colors.b_f = ft_atoi(str[i]);
		i++;
	}
}

char	*check_bef(char *s, int i, int flag)
{
	if (ft_strlen(s) < 3 || (s[i] != '.' && s[1] != '/'))
		return (NULL);
	while (s[i])
	{
		if (s[i] == '.' && s[i + 1] == 'p'
			&& s[i + 2] == 'n' && s[i + 3] == 'g'
			&& s[i + 4] == '\0')
			flag = 1;
		i++;
	}
	if (!flag)
		return (0x0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '.' && s[i + 1] == '/')
			break ;
		if (s[i] != ' ' && s[i] != '.')
			return (NULL);
		i++;
	}
	return (s);
}

void	get_path(t_cube *game, int i, char *str)
{
	char	*s;

	s = check_bef(ft_strtrim(ft_substr(game->map_2d[i],
					3, ft_strlen(game->map_2d[i]) - 1), " "), 0x0, 0x0);
	if (!s)
		error_message(game, 6);
	if (!ft_strcmp(str, "NO"))
		game->texture_walls.no = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "SO"))
		game->texture_walls.so = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "EA"))
		game->texture_walls.ea = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "WE"))
		game->texture_walls.we = ft_strtrim(ft_strdup(s), " ");
}

int	ultra_check(t_cube *game, int mode)
{
	if (!mode)
	{
		if (game->cnt.a1 > 0x1
			|| game->cnt.a2 > 0x1
			|| game->cnt.a3 > 0x1
			|| game->cnt.a4 > 0x1
			|| game->cnt.a5 > 0x1
			|| game->cnt.a6 > 0x1)
			return (0x1);
		if (!game->cnt.a1 || !game->cnt.a2
			|| !game->cnt.a3 || !game->cnt.a4
			|| !game->cnt.a5 || !game->cnt.a6)
			return (0x1);
	}
	else
	{
		if (player_num(game))
			return (0x1);
	}
	return (0);
}
