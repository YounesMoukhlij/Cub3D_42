/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:04 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/03 12:34:15 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
int ft_check_door(t_cube *game , int next_horizontal_x , int next_horizontal_y )
{
	int y = next_horizontal_y - (int)game->player_x;
	int x = next_horizontal_x - (int)game->player_y;
	x = abs(x);
	y = abs(y);
	if (next_horizontal_y / BOX_SIZE > game->map_widht || next_horizontal_x / BOX_SIZE > game->map_height)
		return 0;
	if (game->map[(next_horizontal_y / BOX_SIZE)][(next_horizontal_x / BOX_SIZE)] == 'D' && (x > BOX_SIZE / 2 && y > BOX_SIZE / 2))
		return 1;
	return 0;
}

void	get_x(t_cube *game, t_ray *ray)
{
	if (game->hit_v)
		game->offset_x = (int)ray->wall_y % BOX_SIZE;
	else
		game->offset_x = (int)ray->wall_x % BOX_SIZE;
}

void ft_draw_wall( t_cube *game , t_ray *ray)
{
	(void) ray;
	int dis;
	int j;
    int wall_heigth = (BOX_SIZE / (ray->distance * cos(game->rotation_angle \
		- game->ray_angle))) * ((WINDOW_WIDTH / 2) / tan(PI / 6));

        int top = ft_max((1000 / 2) - (wall_heigth / 2), 0);
		int	bottom = ft_min((1000 / 2) + (wall_heigth / 2), 1000);
		int i;
		get_x(game, ray);
	 	i = top;
		int r;
		int g;
		int b;
		int a;
		while (i < bottom)
		{
			dis = i  - WINDOW_HEITH / 2 + wall_heigth / 2;
			game->offset_y = dis * ((float)BOX_SIZE / wall_heigth); 
			j = ((game->offset_x + game->offset_y * BOX_SIZE) * 4);
			r = game->img_wall->pixels[j];
			g = game->img_wall->pixels[j + 1];
			b = game->img_wall->pixels[j + 2];
			a = game->img_wall->pixels[j + 3];
			mlx_put_pixel(game->img, ray->index, i, ft_color(r, g, b, a));
			i++;
		}
}

float ft_normalize(float angel)
{
	angel = fmod(angel , 2 * PI);
	if (angel < 0)
		angel = (2 * PI) + angel;
	return angel;
}

int ft_calcule_distance(float x1, float y1, float x2 , float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void ray_cast(int  colum , t_cube *game)
{
	game->ray_angle =  ft_normalize(game->ray_angle);
	game->is_facingDown = game->ray_angle > 0 && game->ray_angle < PI;
	game->is_facingup = !game->is_facingDown;
	game->is_facingRight = game->ray_angle < (0.5 * PI) || game->ray_angle > (1.5 * PI);
	game->is_facingLeft = !game->is_facingRight;
	float intercept_y = 0;
	float intercept_x = 0;
	float step_x = 0;
	float step_y = 0;

	
	t_ray *ray = malloc(sizeof(t_ray));
	if (!ray)
		error_message(NULL, 1);
	intercept_y = floor((game->player_x / BOX_SIZE)) * BOX_SIZE;
	intercept_y += game->is_facingDown ? BOX_SIZE : 0 ;
	intercept_x = game->player_y + (intercept_y  - game->player_x) / tan(game->ray_angle);
	step_y = BOX_SIZE;
	step_y *= game->is_facingup ? -1 : 1;
	step_x = BOX_SIZE / (tan(game->ray_angle));
	step_x *= (game->is_facingLeft && step_x > 0) ? -1 : 1;
	step_x *= (game->is_facingRight &&  step_x < 0) ? -1 : 1;
	float  wall_horizontal_y = 0;
	float  wall_horizontal_x = 0;
	int found_horizontal_wall = 0;
	float next_horizontal_x = intercept_x;
	float next_horizontal_y  =  intercept_y;
	if (game->is_facingup)
		next_horizontal_y--;
	while(next_horizontal_x >= 0 && next_horizontal_x <= game->map_widht && next_horizontal_y >= 0 && next_horizontal_y <= game->map_height){
		if (!ft_check_walls(game, next_horizontal_x , next_horizontal_y) || ft_check_door(game , next_horizontal_x , next_horizontal_y))
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

    ///////////////////////////+

	int found_vertical_wall = 0;
	float wall_x = 0;
	float wall_y = 0;
	float  wall_vertical_y = 0;
	float  wall_vertical_x = 0;
	intercept_x = floor((game->player_y / BOX_SIZE)) * BOX_SIZE;
	intercept_x += game->is_facingRight ? BOX_SIZE : 0 ;
	intercept_y = game->player_x + (intercept_x  - game->player_y) * tan(game->ray_angle);
	step_x = BOX_SIZE;
	step_x *= game->is_facingLeft ? -1 : 1;
	step_y = BOX_SIZE * (tan(game->ray_angle));
	step_y *= (game->is_facingup && step_y > 0) ? -1 : 1;
	step_y *= (game->is_facingDown &&  step_y < 0) ? -1 : 1;
	float next_vertical_x = intercept_x;
	float next_vertical_y  =  intercept_y;

	if (game->is_facingLeft)
		next_vertical_x--;
	while(next_vertical_x >= 0 && next_vertical_x <= game->map_widht && next_vertical_y >= 0 && next_vertical_y <= game->map_height){
		if (!ft_check_walls(game, next_vertical_x , next_vertical_y) ||ft_check_door(game , next_vertical_x , next_vertical_y))
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
	float horizontal_wall_distance;
	float vertical_wall_distance;
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
			ray->distance = horizontal_wall_distance;
			game->hit_v = 0;
		}
		else{
			wall_x = wall_vertical_x;
			wall_y = wall_vertical_y;
			ray->distance = vertical_wall_distance;
			game->hit_v = 1;
		}
		ray->index = colum;
		ray->wall_x = wall_x;
		ray->wall_y = wall_y;
		game->was_vertical = 0;
		game->was_vertical = (vertical_wall_distance < horizontal_wall_distance); 
		ft_draw_wall( game , ray);
}
void draw_line_DDA(t_cube *game) {
	game->ray_angle = (game->rotation_angle - (game->fov_angle / 2));
   	int i = 0;
	int colun = 0;
   while(i < game->num_ray)
   {
		ray_cast(colun , game);
		if (i == game->num_ray / 2)
			ft_draw_line(game ,103 , 103  , 100 + cos(game->ray_angle) * 20 ,  100 + sin(game->ray_angle) * 20);
		game->ray_angle += (game->fov_angle / game->num_ray);
		i++;
		colun++;
   }
}

void ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        mlx_put_pixel(game->img_mini_map, x1, y1, ft_color(0, 0, 0, 255));
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
	x = x / BOX_SIZE;
	y = y / BOX_SIZE;
	if (x > game->map_widht / BOX_SIZE || y > game->map_height / BOX_SIZE)
		return 0;
	if (game->map[y][x])
	{
		if (game->map[y][x] != '1' )
			return 1;
	}
	return 0;
}
void ft_test(t_cube *game)
{
	int i = 0;
	while(i < 1000)
	{
		int j = 0;
		while(j < 1500)
		{
			mlx_put_pixel(game->img, j  , i, ft_color(0, 0, 0, 255));
			j++; 
		}
		i++;
	}
}
void ft_test_1(t_cube *game)
{
	int i = 0;
	while(i < 200)
	{
		int j = 0;
		while(j < 200)
		{
			mlx_put_pixel(game->img_mini_map, j  , i, ft_color(0, 0, 0, 255));
			j++; 
		}
		i++;
	}
}
void  ft_check_move(void *tmp)
{
	t_cube *game;
	game = (t_cube *)tmp;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation_angle += 1 * rotation_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->move = 1 * player_speed;
		if (ft_check_walls( game,game->player_y + cos(game->rotation_angle)  * game->move,  game->player_x + sin(game->rotation_angle) * game->move)){
			game->player_y += cos(game->rotation_angle) * game->move;
			game->player_x += sin(game->rotation_angle) * game->move;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->rotation_angle += -1 * rotation_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->move = -1 * player_speed;
		if (ft_check_walls(game,game->player_y + cos(game->rotation_angle)  * game->move,  game->player_x + sin(game->rotation_angle) * game->move)){
			game->player_y += cos(game->rotation_angle) * game->move;
			game->player_x += sin(game->rotation_angle) * game->move;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{

	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	ft_test(game);     //// removed before textures
	// ft_drawing_map(game);
	draw_line_DDA(game);
}
void ft_put_player(t_cube *game)
{
	int pixel;
	pixel = 0;
	int pixel1;
	while(pixel <= player_size_mini_map)
	{
		pixel1 = 0;
		while(pixel1 <= player_size_mini_map)
		{
			mlx_put_pixel(game->img_mini_map,  100 + pixel1, 100 + pixel, 0xFF0000FF);
			pixel1++;
		}
		pixel++;
	}
}
void ft_drawing_map_element(t_cube *game)
{
	int i = 0;
	game->player_y_mini_map = (game->player_x / BOX_SIZE) * BOX_SIZE_MINI_MAP;
	game->player_x_mini_map = (game->player_y / BOX_SIZE) * BOX_SIZE_MINI_MAP;
	int start_y  = game->player_y_mini_map - 100 ;
	while (start_y < game->player_y_mini_map + 100)
	{
		int j = 0;
		int start_x = game->player_x_mini_map - 100;
		while(start_x < game->player_x_mini_map + 100)
		{
			if (start_x / BOX_SIZE_MINI_MAP >= 0 && start_x / BOX_SIZE_MINI_MAP <= game->map_widht / BOX_SIZE  && start_y / BOX_SIZE_MINI_MAP >= 0 && start_y / BOX_SIZE_MINI_MAP <= game->map_height / BOX_SIZE)
			{
				if (game->map[start_y / BOX_SIZE_MINI_MAP][start_x / BOX_SIZE_MINI_MAP] == '1')
					mlx_put_pixel(game->img_mini_map , j  , i, 0xFF0000FF);
				else
					mlx_put_pixel(game->img_mini_map , j  , i, 0xFFFFFFFF);
			}
			else
				mlx_put_pixel(game->img_mini_map , j  , i, ft_color(0, 0, 0, 255));
			start_x++;
			j++;
		}
		start_y++;
		i++;
	}
}

void ft_drawing_map(t_cube *game)
{
	ft_drawing_map_element(game);
	ft_put_player(game);
}


int main(int ac, char **av)
{
	t_cube	game;

	parse(ac, av[0x1], &game);
	game.mlx =  mlx_init(WINDOW_WIDTH,WINDOW_HEITH, "cub3D", 0);
    ft_get_player_position(&game);
	game.img  = mlx_new_image(game.mlx, 1500,1000);
	game.img_mini_map  = mlx_new_image(game.mlx, 200,200);
	game.mini_heigth = WINDOW_HEITH / 4;
	game.mini_width = WINDOW_WIDTH / 4;
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_image_to_window(game.mlx, game.img_mini_map, 0, 0);
	game.player_turn = 0;
	game.player_walk = 0;
	game.map_widht = game.real_map_width * BOX_SIZE;
	game.map_height = game.real_map_heigth * BOX_SIZE;
	game.fov_angle = 60 * (PI / 180);
	// game.rotation_angle = 0;
	game.num_ray = (1500);
	game.img_wall =  mlx_texture_to_image(game.mlx, game.texture);
	if (!game.img_wall)
	{
		puts("eeee\n");
		exit(1);
	}
	// ft_drawing_map(&game);
	mlx_loop_hook(game.mlx, ft_check_move , &game);
	mlx_loop(game.mlx);

	return (0x0);
}



