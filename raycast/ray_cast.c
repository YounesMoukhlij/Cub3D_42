/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:33:23 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/04 13:05:38 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


t_ray *first_chapter(t_cube *game)
{
    t_ray   *ray;
	game->ray_angle =  ft_normalize(game->ray_angle);
	game->is_facingDown = game->ray_angle > 0 && game->ray_angle < PI;
	game->is_facingup = !game->is_facingDown;
	game->is_facingRight = game->ray_angle < (0.5 * PI) || game->ray_angle > (1.5 * PI);
	game->is_facingLeft = !game->is_facingRight;
    game->r_tools.intercept_y = 0;
	game->r_tools.intercept_x = 0;
	game->r_tools.step_x = 0;
	game->r_tools.step_y = 0;
    ray = malloc(sizeof(t_ray));
	if (!ray)
		error_message(NULL, 1);
    return(ray);
    
}

void    second_chapter(t_cube *game)
{
	game->r_tools.intercept_y = floor((game->player_x / BOX_SIZE)) * BOX_SIZE;
	game->r_tools.intercept_y += game->is_facingDown ? BOX_SIZE : 0 ;
    game->r_tools.intercept_x = game->player_y + (game->r_tools.intercept_y  - game->player_x) / tan(game->ray_angle);
	game->r_tools.step_y = BOX_SIZE;
	game->r_tools.step_y *= game->is_facingup ? -1 : 1;
	game->r_tools.step_x = BOX_SIZE / (tan(game->ray_angle));
	game->r_tools.step_x *= (game->is_facingLeft && game->r_tools.step_x > 0) ? -1 : 1;
	game->r_tools.step_x *= (game->is_facingRight &&  game->r_tools.step_x < 0) ? -1 : 1;
	  game->r_tools.wall_horizontal_y = 0;
	  game->r_tools.wall_horizontal_x = 0;
	 game->r_tools.found_horizontal_wall = 0;
     game->r_tools.next_horizontal_x = game->r_tools.intercept_x;
	 game->r_tools.next_horizontal_y  =  game->r_tools.intercept_y;
	if (game->is_facingup)
		game->r_tools.next_horizontal_y--;
}

void        third_chapter(t_cube *game)
{
	while(game->r_tools.next_horizontal_x >= 0
        && game->r_tools.next_horizontal_x <= game->map_widht
        && game->r_tools.next_horizontal_y >= 0
        && game->r_tools.next_horizontal_y <= game->map_height)
        {
		    if (!ft_check_walls(game, game->r_tools.next_horizontal_x,
                game->r_tools.next_horizontal_y)
                || ft_check_door(game , game->r_tools.next_horizontal_x
                , game->r_tools.next_horizontal_y))
		    {
			    game->r_tools.found_horizontal_wall = 1;
			game->r_tools.wall_horizontal_x = game->r_tools.next_horizontal_x;
			game->r_tools.wall_horizontal_y = game->r_tools.next_horizontal_y;
			break;
		}
		else{
			game->r_tools.next_horizontal_x += game->r_tools.step_x;
			game->r_tools.next_horizontal_y += game->r_tools.step_y;
		}
	}
    
}

void    fourth_chapter(t_cube *game, t_ray *ray)
{
    
	 game->r_tools.found_vertical_wall = 0;
	 ray->wall_x = 0;
	 ray->wall_y = 0;
	  game->r_tools.wall_vertical_y = 0;
	  game->r_tools.wall_vertical_x = 0;
    game->r_tools.intercept_x = floor((game->player_y / BOX_SIZE)) * BOX_SIZE;
    game->r_tools.intercept_x += game->is_facingRight ? BOX_SIZE : 0 ;
    game->r_tools.intercept_y = game->player_x + (game->r_tools.intercept_x  - game->player_y) * tan(game->ray_angle);
	game->r_tools.step_x = BOX_SIZE;
	game->r_tools.step_x *= game->is_facingLeft ? -1 : 1;
	game->r_tools.step_y = BOX_SIZE * (tan(game->ray_angle));
	game->r_tools.step_y *= (game->is_facingup && game->r_tools.step_y > 0) ? -1 : 1;
	game->r_tools.step_y *= (game->is_facingDown &&  game->r_tools.step_y < 0) ? -1 : 1;
     game->r_tools.next_vertical_x = game->r_tools.intercept_x;
	 game->r_tools.next_vertical_y  =  game->r_tools.intercept_y;
	if (game->is_facingLeft)
		game->r_tools.next_vertical_x--;
}

void ray_cast(int  colum , t_cube *game)
{
	t_ray *ray;

    ray = first_chapter(game);
    second_chapter(game);
    third_chapter(game);
    fourth_chapter(game, ray);
    fifth_chapter(game);
    sixth_chapter(game, ray);


		ray->index = colum;

		game->was_vertical = 0;
		game->was_vertical = (game->r_tools.vertical_wall_distance < game->r_tools.horizontal_wall_distance); 
		ft_draw_wall( game , ray);
}
