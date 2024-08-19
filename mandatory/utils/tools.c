/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:19:10 by abechcha          #+#    #+#             */
/*   Updated: 2024/08/18 14:48:30 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_length_heigth(char **str, int mode, int i)
{
	if (!mode)
	{
		while (str[i])
			i++;
		i -= 6;
	}
	if (mode)
	{
		while (str[mode][i])
			i++;
	}
	return (i);
}

char	*fill_chars(t_cube *game, char *s)
{
	game->twilzat.i = 0;
	game->twilzat.j = 0;
	game->twilzat.f = 0;
	if (ft_strlen(s) < game->real_map_width)
		game->twilzat.f = 1;
	if (game->twilzat.f)
	{
		game->twilzat.tmp = ft_malloc(game->real_map_width + 1, 1);
		if (!game->twilzat.tmp)
			return (NULL);
		while (s[game->twilzat.i])
		{
			if (check_one(game, s))
				game->twilzat.tmp[game->twilzat.j] = ' ';
			else
				game->twilzat.tmp[game->twilzat.j] = s[game->twilzat.i];
			game->twilzat.i++;
			game->twilzat.j++;
		}
		game->twilzat.tmp[game->twilzat.j] = '\0';
	}
	if (!game->twilzat.f)
		return (ft_strdup(s));
	return (game->twilzat.tmp);
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
