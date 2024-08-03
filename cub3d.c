/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:04 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/03 12:02:09 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	fov_angle = 60 * (PI / 180);
float  roation_angle = 0;
float	num_ray = (1500);
float MOUSE_SENSITIVITY = 0.001; 
int		lastMouseX = 0; 

void rect(mlx_image_t *game,  int x1, int y1, int x2, int y2, int color)
{
    int x, y;
	(void)color;
	for (x = x1; x <= x2; x++) 
	{
        for (y = y1; y <= y2; y++)
		{
            mlx_put_pixel(game, x, y, 0x00FF00FF);
        }
    }
}

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

void	ft_mlx_put_pixel(t_cube *data, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_HEITH && y >= 0 && y < WINDOW_WIDTH)
		mlx_put_pixel(data->img, x, y, color);
}




// int	ft_texture_color(unsigned int c)
// {
// 	int	r;
// 	int	g;
// 	int	b;
// 	int	a;

// 	a = c % 256;
// 	c /= 256;
// 	b = c % 256;
// 	c /= 256;
// 	g = c % 256;
// 	c /= 256;
// 	r = c;
// 	// return (ft_color(r, g , b, a));
// 	return (ft_color(a, b, g, r));
// }

void	get_x(t_cube *game, int i)
{
	(void) i;
	if (game->hit_v)
		game->offset_x = (int)game->wall_y % box_size;
	else
		game->offset_x = (int)game->wall_x % box_size;
}


void ft_draw_wall(t_ray *head, t_cube *game , float distance , int index)
{
	(void)head;
	// int step;
	int dis;
	int j;
    int wall_heigth = (box_size / (distance * cos(roation_angle \
		- game->ray_angle))) * ((WINDOW_WIDTH / 2) / tan(PI / 6));

        int top = ft_max((1000 / 2) - (wall_heigth / 2), 0);
		int	bottom = ft_min((1000 / 2) + (wall_heigth / 2), 1000);
		int i;
		get_x(game, index);
	 	i = top;
		int r;
		int g;
		int b;
		int a;
		while (i < bottom)
		{
			dis = i  - WINDOW_HEITH / 2 + wall_heigth / 2;
			game->offset_y = dis * ((float)box_size / wall_heigth); 
			j = ((game->offset_x + game->offset_y * box_size) * 4);
			r = game->img_wall->pixels[j];
			g = game->img_wall->pixels[j + 1];
			b = game->img_wall->pixels[j + 2];
			a = game->img_wall->pixels[j + 3];
			mlx_put_pixel(game->img, index, i, ft_color(r, g, b, a));
			
	// 		if (game->hit_v)
	// 			mlx_put_pixel(game->img,  index, i, ft_color(255, 0, 0, 255 * exp(-0.0001 * distance)));
	// 		else
	// 			mlx_put_pixel(game->img,  index, i, ft_color(0, 0, 255, 255 * exp(-0.0001 * distance)));
			i++;
		}



}






// Function to get color from texture

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
	dda(game , game->player_y , game->player_x , game->player_y + cos(game->ray_angle) , game->player_x + sin(game->ray_angle));
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
void ray_cast( t_ray *head ,int  colum , t_cube *game)
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

	
	(void)colum;
	intercept_y = floor((game->player_x / box_size)) * box_size;
	intercept_y += game->is_facingDown ? box_size : 0 ;
	intercept_x = game->player_y + (intercept_y  - game->player_x) / tan(game->ray_angle);
	step_y = box_size;
	step_y *= game->is_facingup ? -1 : 1;
	step_x = box_size / (tan(game->ray_angle));
	step_x *= (game->is_facingLeft && step_x > 0) ? -1 : 1;
	step_x *= (game->is_facingRight &&  step_x < 0) ? -1 : 1;
	float  wall_horizontal_y = 0;
	float  wall_horizontal_x = 0;
	int found_horizontal_wall = 0;
	float next_horizontal_x = intercept_x;
	float next_horizontal_y  =  intercept_y;
	if (game->is_facingup)
		next_horizontal_y--;
	while(next_horizontal_x >= 0 && next_horizontal_x <= game->map_widht && next_horizontal_y >= 0 && next_horizontal_y <= game->map_height)
	{
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

    ///////////////////////////+

	int found_vertical_wall = 0;
	game->wall_x = 0;
	game->wall_y = 0;
	float  wall_vertical_y = 0;
	float  wall_vertical_x = 0;
	intercept_x = floor((game->player_y / box_size)) * box_size;
	intercept_x += game->is_facingRight ? box_size : 0 ;
	intercept_y = game->player_x + (intercept_x  - game->player_y) * tan(game->ray_angle);
	step_x = box_size;
	step_x *= game->is_facingLeft ? -1 : 1;
	step_y = box_size * (tan(game->ray_angle));
	step_y *= (game->is_facingup && step_y > 0) ? -1 : 1;
	step_y *= (game->is_facingDown &&  step_y < 0) ? -1 : 1;
	float next_vertical_x = intercept_x;
	float next_vertical_y  =  intercept_y;

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
			game->wall_x = wall_horizontal_x;
			game->wall_y = wall_horizontal_y;
			game->distance = horizontal_wall_distance;
			game->hit_v = 0;
		}
		else{
			game->wall_x = wall_vertical_x;
			game->wall_y = wall_vertical_y;
			game->distance = vertical_wall_distance;
			game->hit_v = 1;
		}
		(void)head;
		game->was_vertical = 0;
		game->was_vertical = (vertical_wall_distance < horizontal_wall_distance);
		ft_draw_wall(head , game , game->distance , colum);
		// ft_draw_line(game , game->player_y , game->player_x  , wall_x , wall_y , 0);
}
void draw_line_DDA(t_cube *game)
{
	game->ray_angle = (roation_angle - (fov_angle / 2));
   	int i = 0;
	int colun = 0;
	t_ray *head = NULL;
   	while(i < num_ray)
   	{
		lst_add_back(&head);
		ray_cast(lst_last(head), colun , game);
		// new_ray(game);
		game->ray_angle += (fov_angle / num_ray);
		i++;
		colun++;
   	}
//    ft_draw_wall(head , game);
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
	
	if (!(y < game->real_map_heigth && x < game->real_map_width))
		return (0);
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

void ft_mouse_move(float x_pos, float y_pos, void *pointer)
{

	(void) y_pos;
    t_cube *game = pointer;
	(void) game;
	(void) pointer;
    int mouseX = (int)x_pos;
    int deltaX = (mouseX - (lastMouseX)) * 0.1;


    if (deltaX != 0)
    {
        roation_angle += deltaX * MOUSE_SENSITIVITY;
        roation_angle = fmod(roation_angle, 2 * PI); 
    }

    lastMouseX = mouseX; 
}

void  ft_check_move(void *tmp)
{
	t_cube *game;
	game = (t_cube *)tmp;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		roation_angle += 1 * rotation_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->move = 1 * player_speed;
		
		if (ft_check_walls( game,game->player_y + cos(roation_angle)  * game->move,  game->player_x + sin(roation_angle) * game->move)){
			game->player_y += cos(roation_angle) * game->move;
			game->player_x += sin(roation_angle) * game->move;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		roation_angle += -1 * rotation_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)||mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->move = -1 * player_speed;
		if (ft_check_walls(game,game->player_y + cos(roation_angle)  * game->move,  game->player_x + sin(roation_angle) * game->move)){
			game->player_y += cos(roation_angle) * game->move;
			game->player_x += sin(roation_angle) * game->move;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		// mlx_cursor_hook(game->mlx, ft_mouse_move, &game);
    
    	// lastMouseX = 500 / 2;
    	// mlx_set_mouse_pos(game->mlx, lastMouseX, 500 / 2);
		mlx_close_window(game->mlx);
	}
	// else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	// {
	// 	if (ft_check_walls( game,game->player_y + cos(roation_angle + rotation_speed) ,  game->player_x + sin(roation_angle + rotation_speed))){
	// 		game->player_y += cos(roation_angle + rotation_speed );
	// 		game->player_x += sin(roation_angle + rotation_speed);
	// 	}
	// }
	// else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	// {
	// 	// if (ft_check_walls(game,game->player_y + cos(roation_angle - rotation_speed) ,  game->player_x + sin(roation_angle -  rotation_speed))){
	// 		// roation_angle += -1 * rotation_speed;
	// 		game->player_y += cos(roation_angle  + ( -1 * rotation_speed));
	// 		game->player_x += sin(roation_angle  + ( -1 * rotation_speed));
	// 	// }
	// }
	ft_test(game);
	// ft_drawing_map(game);
	draw_line_DDA(game);
	// ft_put_player(game);
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
}
void ft_drawing_map_element(t_cube *game)
{
	int start_px = game->player_y_mini_map - 100;
	int start_py = game->player_x_mini_map - 100;
	while(start_py < game->player_x_mini_map + 100)
	{
		start_px =  game->player_y_mini_map - 100;
		while(start_px < game->player_y_mini_map + 100)
		{
			if (start_px  > 0 &&  start_py > 0 &&  start_py <  130)
			{
				printf("%d %d\n",start_py / box_size_mini_map , start_px /box_size_mini_map );
				if (game->map[start_py / box_size_mini_map ][start_px /box_size_mini_map] == 'N')
					mlx_put_pixel(game->img_mini_map , start_px ,start_py , 0x00FF00FF);
				else
					mlx_put_pixel(game->img_mini_map , start_px ,start_py , 0xFF0000FF);
			}
			start_px++;
		}
		start_py++;
	}

}

void ft_drawing_map(t_cube *game)
{
	ft_drawing_map_element(game);
	ft_put_player(game);
}

void	finish_him(t_cube *game)
{
	ft_free(game->map);
}

void set_values(t_cube *game)
{
	game->player_turn = 0;
	game->player_walk = 0;
}

void	leak_s(void)
{
	system("leaks cub3D");
}

int main(int ac, char **av)
{
	t_cube	game;


	// atexit(leak_s);
	parse(ac, av[0x1], &game);
	game.mlx =  mlx_init(WINDOW_WIDTH, WINDOW_HEITH, "cub3D", 0);
    ft_get_player_position(&game);
	set_values(&game);
	game.mini_heigth = WINDOW_HEITH / 4;
	game.mini_width = WINDOW_WIDTH / 4;
	game.color = (uint32_t *)game.texture->pixels;
	game.img  = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEITH);
	game.img_mini_map  = mlx_new_image(game.mlx, 200,200);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_image_to_window(game.mlx, game.img_mini_map, 0, 0);
	game.map_widht = game.real_map_width * box_size;
	game.map_height =  game.real_map_heigth * box_size;

	game.img_wall =  mlx_texture_to_image(game.mlx, game.texture);
	if (!game.img_wall)
	{
		puts("eeee\n");
		exit(1);
	}
	mlx_loop_hook(game.mlx, ft_check_move , &game);
	mlx_loop(game.mlx);
	return (0x0);
}


