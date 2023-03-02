/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:11 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/02 22:35:29 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	my_mlx_pixel_put(img *data, int x, int y, int color);
// void draw_map(t_vars *vars,int x,int y)
// {
// 	if(vars->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
// 	{
// 		my_mlx_pixel_put(&vars->img, 
		//scale_factor * x, scale_factor * y, 0x00ff00);
// 	}
// 	else
// 		my_mlx_pixel_put(&vars->img, 
	//scale_factor * x, scale_factor * y, 0xCFCFCF);
// }

// void	draw(t_vars *vars,int x ,int y)
// {
// 	int i = y;

// 	int j = x;
// 	if(x >= vars->width * TILE_SIZE || y >= vars->height* TILE_SIZE)
// 		return;
// 	while(i < y + TILE_SIZE)
// 	{
// 		j = x;
// 		while(j < x + TILE_SIZE)
// 		{
// 			draw_map(vars,j,i);
// 			j++;
// 		}
// 		i++;
// 	}
// }
// void draw_line(t_vars *vars,double rayangle,double i ,double j)
// {
// 	int x1 = (vars->player.x);
//     int y1 = (vars->player.y);
//     int x2 = i;
//     int y2 = j;

//     int dx = x2 - x1;
//     int dy = y2 - y1;
//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
//     double x_inc = dx / (double) steps;
//     double y_inc = dy / (double) steps;
//     double x = x1;
//     double y = y1;
//     for (int i = 0; i <= steps; i++) {
//         my_mlx_pixel_put(&vars->img, 
			//scale_factor * x, scale_factor * y, 0xff00004);
//         x += x_inc;
//         y += y_inc;
//     }
// }
// void render(t_vars *vars)
// {
// 	int i = 0;
// 	int tilex;
// 	int pixel;
// 	int tiley;
// 	int j = 0;
// 	while(i < vars->height * TILE_SIZE)
// 	{
// 		j = 0;
// 		while(j < vars->width * TILE_SIZE)
// 		{
// 			tilex = j * TILE_SIZE;
// 			tiley = i * TILE_SIZE;
// 			draw(vars,tilex,tiley);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_square(t_vars *vars)
// {
//  double radius = 0;
//     double i;
//     while(radius < 3)
//     {
//         i = 0;
//         while(i < 360)
//         {
//             my_mlx_pixel_put(&vars->img,
	//(vars->player.x * scale_factor) + cos(i) *radius,
		//(vars->player.y * scale_factor)+ sin(i) * radius,0xFF0000);
//             i+=0.5;
//         }
//         radius++;
//     }
// }
#include"cub_3D.h"

int	main(int ac, char **av)
{
	t_vars			vars;
	t_prasing_data	data;

	vars.h = 0;
	if (ac != 2 || !type_check(av[1]))
		print_error("error");
	parsing(av[1], &data);
	vars.map = editmap(data.map, get_width(data.map));
	vars.f = get_rgb(data.floor);
	vars.c = get_rgb(data.ceiling);
	get_pos(&vars, &data);
	vars.player.d = 0;
	vars.mlx = mlx_init();
	vars.height = get_height(vars.map);
	vars.width = get_width(vars.map);
	vars.mlx_win = mlx_new_window(vars.mlx, WIDTH,
			HEIGHT, "Cub3d");
	init_player(&vars, &data);
	update(&vars);
	vars.h = 1;
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_loop(vars.mlx);
}
