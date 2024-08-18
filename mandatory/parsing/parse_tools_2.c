/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:07:38 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 12:54:22 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_color(t_cube *game, char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 3)
		error_message(game, 10);
	return (0x0);
}

void	parse_s(t_cube *game, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',' && s[i + 1] == ',' && s[i + 1])
			error_message(game, 0x7);
		if (s[ft_strlen(s) - 1] == ',')
			error_message(game, 0x7);
		i++;
	}
}

char	*check_bef(char *s)
{
	if (ft_strlen(s) < 3)
		return (NULL);
	if (s[0] != '.' && s[1] != '/')
		return (NULL);
	return (s);
}

void	get_path(t_cube *game, int i, char *str)
{
	char	*s;

	s = check_bef(ft_substr(game->map_2d[i],
				3, ft_strlen(game->map_2d[i]) - 1));
	if (!s)
		return ;
	if (!ft_strcmp(str, "NO"))
		game->texture_walls.no = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "SO"))
		game->texture_walls.so = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "EA"))
		game->texture_walls.ea = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "WE"))
		game->texture_walls.we = ft_strtrim(ft_strdup(s), " ");
}
