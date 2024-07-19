/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:04 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/14 08:18:44 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	fov_angle = 60 * (PI / 180);
double  roation_angle = PI / 2;
double	num_ray = (24 * box_size ) / 4;

void dda(t_cube *game,int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        mlx_put_pixel(game->img, x1, y1, 0x00FF00FF);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void new_ray(t_cube *game)
{
	dda(game , game->player_y , game->player_x , game->player_y + cos(game->ray_angle) * 60 , game->player_x + sin(game->ray_angle) * 60);
}
double ft_normalize(double angel)
{
	angel = fmod(angel , 2 * PI);
	if (angel < 0)
		angel = (2 * PI) + angel;
	return angel;
}
int ft_calcule_distance(double x1, double y1, double x2 , double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void ray_cast(int colum , t_cube *game)
{
	game->ray_angle =  ft_normalize(game->ray_angle);
	double intercept_y = 0;
	double intercept_x = 0;
	double step_x = 0;
	double step_y = 0;
	game->is_facingDown = game->ray_angle > 0 && game->ray_angle < PI;
	game->is_facingup = !game->is_facingDown;
	game->is_facingRight = game->ray_angle < 0.5 * PI || game->ray_angle > 1.5 * PI;
	game->is_facingLeft = !game->is_facingRight;
	(void)colum;
	intercept_y = floor((game->player_x / box_size)) * box_size;
	intercept_y += game->is_facingDown ? box_size : 0 ;
	intercept_x = game->player_y + (intercept_y  - game->player_x) / tan(game->ray_angle);
	step_y = box_size;
	step_y *= game->is_facingup ? -1 : 1;
	step_x = box_size / (tan(game->ray_angle));
	step_x *= (game->is_facingLeft && step_x > 0) ? -1 : 1;
	step_x *= (game->is_facingRight &&  step_x < 0) ? -1 : 1;
	double  wall_horizontal_y = 0;
	double  wall_horizontal_x = 0;
	int found_horizontal_wall = 0;
	double next_horizontal_x = intercept_x;
	double next_horizontal_y  =  intercept_y;
	if (game->is_facingup)
		next_horizontal_y--;
	while(next_horizontal_x >= 0 && next_horizontal_x <= game->map_widht && next_horizontal_y >= 0 && next_horizontal_y <= game->map_height){
		if (!ft_check_walls(game, next_horizontal_x , next_horizontal_y))
		{
			found_horizontal_wall = 1;
			wall_horizontal_x = next_horizontal_x;
			wall_horizontal_y = next_horizontal_y;
			break;
		}
		else{
			next_horizontal_x += step_x;
			next_horizontal_y += step_y;
		}
	}

    /////////
	int found_vertical_wall = 0;
	double wall_x = 0;
	double wall_y = 0;
	double  wall_vertical_y = 0;
	double  wall_vertical_x = 0;
	intercept_x = floor((game->player_y / box_size)) * box_size;
	intercept_x += game->is_facingRight ? box_size : 0 ;
	intercept_y = game->player_x + (intercept_x  - game->player_y) * tan(game->ray_angle);
	step_x = box_size;
	step_x *= game->is_facingLeft ? -1 : 1;
	step_y = box_size * (tan(game->ray_angle));
	step_y *= (game->is_facingup && step_y > 0) ? -1 : 1;
	step_y *= (game->is_facingDown &&  step_y < 0) ? -1 : 1;
	double next_vertical_x = intercept_x;
	double next_vertical_y  =  intercept_y;

	if (game->is_facingLeft) ////////////////
		next_vertical_x--;
	while(next_vertical_x >= 0 && next_vertical_x <= game->map_widht && next_vertical_y >= 0 && next_vertical_y <= game->map_height){
		if (!ft_check_walls(game, next_vertical_x , next_vertical_y))
		{
			found_vertical_wall = 1;
			wall_vertical_x = next_vertical_x;
			wall_vertical_y = next_vertical_y;
			break;
		}
		else{
			next_vertical_x += step_x;
			next_vertical_y += step_y;
		}
	}
	double horizontal_wall_distance;
	double vertical_wall_distance;
		if (found_horizontal_wall)
			horizontal_wall_distance = ft_calcule_distance(game->player_y , game->player_x , wall_horizontal_x , wall_horizontal_y);
		else
			horizontal_wall_distance = 10000000000;
		if (found_vertical_wall)
			vertical_wall_distance = ft_calcule_distance(game->player_y , game->player_x , wall_vertical_x , wall_vertical_y);
		else
			vertical_wall_distance = 10000000000;
		if (horizontal_wall_distance  < vertical_wall_distance)
		{
			wall_x = wall_horizontal_x;
			wall_y = wall_horizontal_y;
			game->distance = horizontal_wall_distance;
		}
		else{
			wall_x = wall_vertical_x;
			wall_y = wall_vertical_y;
			game->distance = vertical_wall_distance;
		}
		// game->was_vertical = 0;
		// game->was_vertical = (vertical_wall_distance < horizontal_wall_distance);
		ft_draw_line(game , game->player_y , game->player_x  , wall_x , wall_y , 0);
}
void draw_line_DDA(t_cube *game) {
	game->ray_angle = (roation_angle - (fov_angle / 2));
   	game->rays = malloc(sizeof(float) * num_ray + 1);
   	int i = 0;
	int colun = 0;
   while(i < num_ray)
   {
		ray_cast(colun , game);
		// new_ray(game);
		game->ray_angle += (fov_angle / num_ray);
		i++;
		colun++;
   }
}

void ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2 , int flag)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
		if(flag == 1)
        	mlx_put_pixel(game->img, x1, y1, 0x00FF00FF);
		else
        	mlx_put_pixel(game->img, x1, y1, 0x00FF00FF);

        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}
void clear_player(t_cube *game)
{
	int pixel;
	pixel = 0;
	int pixel1 = 0;
	while(pixel < player_size)
	{
		pixel1 = 0;
		while(pixel1< player_size){
			mlx_put_pixel(game->img, game->player_y + pixel1 , game->player_x + pixel, 0xFFFFFF);
			pixel1++;
		}
		pixel++;
	}
}
int ft_check_walls(t_cube *game , int x , int y)
{
	x = x / box_size;
	y = y / box_size;
	if (game->map_2d[y][x])
	{
		if (game->map_2d[y][x] != '1' )
			return 1;
	}
	return 0;
}
void  ft_check_move(struct mlx_key_data ll ,void *tmp)
{
	t_cube *game;
	(void)ll;
	game = (t_cube *)tmp;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		// ft_draw_line(game, game->player_y, game->player_x, game->player_new_y, game->player_new_x , 1);
		roation_angle += 1 * reation_speed;
		game->player_new_y =  game->player_y + cos(roation_angle);
		game->player_new_x =  game->player_x + sin(roation_angle);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		// ft_draw_line(game, game->player_y, game->player_x, game->player_new_y, game->player_new_x , 1);
		game->move = 1 * player_speed;
		
		if (ft_check_walls( game,game->player_y + cos(roation_angle) ,  game->player_x + sin(roation_angle))){
			game->player_y += cos(roation_angle) * game->move;
			game->player_x += sin(roation_angle) * game->move;
			game->player_new_y =  game->player_y + cos(roation_angle);
			game->player_new_x =  game->player_x + sin(roation_angle);
		}
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		// ft_draw_line(game, game->player_y, game->player_x, game->player_new_y, game->player_new_x , 1);
		roation_angle += -1 * reation_speed;
		game->player_new_y =  game->player_y + cos(roation_angle);
		game->player_new_x =  game->player_x + sin(roation_angle);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		// ft_draw_line(game, game->player_y, game->player_x, game->player_new_y, game->player_new_x , 1);
		game->move = -1 * player_speed;
		if (ft_check_walls( game,game->player_y + cos(roation_angle) ,  game->player_x + sin(roation_angle))){
			game->player_y += cos(roation_angle) * game->move;
			game->player_x += sin(roation_angle) * game->move;
			game->player_new_y =  game->player_y + cos(roation_angle);
			game->player_new_x =  game->player_x + sin(roation_angle);
		}
	}
	ft_drawing_map(game);
	draw_line_DDA(game);
	ft_put_player(game);
	game->move = 0;
}
void ft_put_player(t_cube *game)
{
	int pixel;
	pixel = 0;
	int pixel1 = 0;
	while(pixel < player_size)
	{
		pixel1 = 0;
		while(pixel1< player_size){
			mlx_put_pixel(game->img,  game->player_y + pixel1, game->player_x + pixel, 0xFF0000FF);
			pixel1++;
		}
		pixel++;
	}
	// ft_draw_line(game ,game->player_y ,game->player_x, game->player_new_y ,game->player_new_x, 0);
}
void ft_drawing_map_element(t_cube *game)
{
	int i = 0;
	int j ;
	while (game->map_2d[i])
	{
		j = 0;
		while(game->map_2d[i][j])
		{
			if (game->map_2d[i][j] == '1')
				ft_draw_square(game , i * box_size , j * box_size);
			else if (game->map_2d[i][j] == '0' || game->map_2d[i][j] == 'N')
				ft_draw_floor(game , i * box_size , j * box_size);
			j++;
		}
		i++;
	}
}
void map_dem(t_cube *game)
{
	int i;
	i = 0;
	int j;
	while(game->map_2d[i])
	{
		j = 0;
		while(game->map_2d[i][j])
			j++;
		i++;
	}
	game->map_widht = j;
	game->map_height = i;
}
void ft_drawing_map(t_cube *game)
{
	ft_drawing_map_element(game);
	ft_put_player(game);
}

void	finish_him(t_cube *game)
{
	ft_free(game->map_2d);
}

void set_values(t_cube *game)
{
	game->player_turn = 0;
	game->player_walk = 0;
}
int main(int ac, char **av)
{
	t_cube	game;

	parse(ac, av[0x1], &game);
	game.mlx =  mlx_init(1500, 1000, "cub3D", 0);




    ft_get_player_position(&game);
	set_values(&game);


	game.img  = mlx_new_image(game.mlx, 1500,650);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	game.map_widht = 24 * box_size;
	game.map_height = 12 * box_size;
	ft_drawing_map(&game);
	mlx_key_hook(game.mlx, ft_check_move , &game);
	mlx_loop(game.mlx);
	finish_him(&game);
	return (0x0);
}



