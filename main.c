/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:11 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/02 21:28:30 by aainhaja         ###   ########.fr       */
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
#include<mlx.h>
#include<string.h>
#include<math.h>
#include"cub_3D.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_pressed(int key_code, t_vars *vars)
{
	if (key_code == W_KEY)
		vars->player.walkdirection = 1;
	else if (key_code == S_KEY)
		vars->player.walkdirection = -1;
	else if (key_code == 123)
		vars->player.turndirection = 1;
	else if (key_code == 124)
		vars->player.turndirection = -1;
	else if (key_code == 2)
	{
		vars->player.d = 2;
		vars->player.walkdirection = -1;
	}
	else if (key_code == 0)
	{
		vars->player.d = 2;
		vars->player.walkdirection = 1;
	}
	else if (key_code == 53)
		exit(0);
	return (1);
}

int	key_release(int key_code, t_vars	*vars)
{
	if (key_code == W_KEY)
		vars->player.walkdirection = 0;
	else if (key_code == S_KEY)
		vars->player.walkdirection = 0;
	else if (key_code == 123)
		vars->player.turndirection = 0;
	else if (key_code == 124)
		vars->player.turndirection = 0;
	else if (key_code == 2)
	{
		vars->player.d = 0;
		vars->player.walkdirection = 0;
	}
	else if (key_code == 0)
	{
		vars->player.d = 0;
		vars->player.walkdirection = 0;
	}
	return (0);
}

double	dist(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

double	normalizeangle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle <= 0)
	{
		angle = (2 * M_PI) + angle;
	}
	return (angle);
}

unsigned long	createRGB(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	horizontalcast1(t_vars *vars, double rayangle, int l)
{
	double	y1;

	while (vars->tempx >= 0 && vars->tempx < vars->width * TILE_SIZE
		&& vars->tempy >= 0 && vars->tempy < vars->height * TILE_SIZE)
	{
		y1 = vars->tempy;
		if (!(rayangle > 0 && rayangle < M_PI) && y1 - 1 >= 0)
			y1--;
		if (vars->map[(int)floor(y1 / TILE_SIZE)]
			[(int)floor(vars->tempx / TILE_SIZE)] == '1')
		{
			l = 1;
			break ;
		}
		vars->tempx += vars->temp1x;
		vars->tempy += vars->temp1y;
	}
	vars->player.realx = vars->tempx;
	vars->player.realy = vars->tempy;
	if (l == 1)
		vars->player.dist = dist(vars->player.x, vars->player.y,
				vars->tempx, vars->tempy);
	else
		vars->player.dist = 10000000;
}

void verticalcast1(t_vars *vars, double rayangle, int l)
{
	double	x;

	while (vars->tempx >= 0 && vars->tempx < vars->width * TILE_SIZE
		&& vars->tempy >= 0 && vars->tempy < vars->height * TILE_SIZE)
	{
		x = vars->tempx;
		if (!(rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI) && x - 1 >= 0)
			x--;
		if (vars->map[(int)floor(vars->tempy / TILE_SIZE)]
			[(int)floor(x / TILE_SIZE)] == '1')
		{
			l = 1;
			break ;
		}
		vars->tempx += vars->temp1x;
		vars->tempy += vars->temp1y;
	}
	vars->player.nrealx = vars->tempx;
	vars->player.nrealy = vars->tempy;
	if (l == 1)
		vars->player.ndist = dist(vars->player.x, vars->player.y,
				vars->tempx, vars->tempy);
	else
		vars->player.ndist = 10000000;
}
void horizontalcast(t_vars *vars, double rayangle)
{
	int	l;

	l = 0;
	vars->tempy = floor(vars->player.y / TILE_SIZE) * TILE_SIZE;
	if (rayangle > 0 && rayangle < M_PI)
		vars->tempy += TILE_SIZE;
	vars->tempx = vars->player.x
		+ (vars->tempy - vars->player.y) / tan(rayangle);
	vars->temp1y = TILE_SIZE;
	if (!(rayangle > 0 && rayangle < M_PI))
		vars->temp1y *= -1;
	vars->temp1x = TILE_SIZE / tan(rayangle);
	if ((rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI) && vars->temp1x < 0)
		vars->temp1x = vars->temp1x * -1;
	if (!(rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI) && vars->temp1x > 0)
			vars->temp1x = vars->temp1x * -1;
	horizontalcast1(vars, rayangle, l);
}

void	verticalcast(t_vars *vars, double rayangle)
{
	int	l;

	l = 0;
	vars->tempx = floor(vars->player.x / TILE_SIZE) * TILE_SIZE;
	if ((rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI))
		vars->tempx += TILE_SIZE;
	vars->tempy = vars->player.y + (vars->tempx - vars->player.x)
		* tan(rayangle);
	vars->temp1x = TILE_SIZE;
	if (!(rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI))
		vars->temp1x *= -1;
	vars->temp1y = TILE_SIZE * tan(rayangle);
	if (!(rayangle > 0 && rayangle < M_PI) && vars->temp1y > 0)
		vars->temp1y *= -1;
	if (rayangle > 0 && rayangle < M_PI && vars->temp1y < 0)
		vars->temp1y *= -1;
	verticalcast1(vars, rayangle, l);
}

int	get_v_color(t_vars	*vars, int y, int x, double	rayangle)
{
	char	*pixel;
	int		color;

	color = 0;
	if (!(rayangle > 0 && rayangle < M_PI))
	{
		pixel = vars->s.addr + y * vars->s.line_length
			+ x * (vars->s.bits_per_pixel / 8);
		color = *((int *) pixel);
	}
	else if ((rayangle > 0 && rayangle < M_PI))
	{
		pixel = vars->n.addr + y * vars->n.line_length
			+ x * (vars->n.bits_per_pixel / 8);
		color = *((int *) pixel);
	}
	return (color);
}

int	get_color(t_vars *vars, int y, int x, double rayangle)
{
	char	*pixel;
	int		color;

	if (vars->player.l)
		return (get_v_color(vars, y, x, rayangle));
	else
	{
		if (!(rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI))
		{
			pixel = vars->e.addr + y * vars->e.line_length
				+ x * (vars->e.bits_per_pixel / 8);
			color = *((int *) pixel);
		}
		else
		{
			pixel = vars->w.addr + y * vars->w.line_length
				+ x * (vars->w.bits_per_pixel / 8);
			color = *((int *) pixel);
		}
	}
	return (color);
}

void	draw_f_c(t_vars *vars, int wallbot,int j)
{
	double	i;

	i = 0;
	while (i <= ((HEIGHT) - wallbot))
	{
		my_mlx_pixel_put(&vars->img, (WIDTH) - (j + 1), i, vars->c);
		i++;
	}
	i = wallbot + 1;
	while (i < HEIGHT)
	{
		my_mlx_pixel_put(&vars->img, (WIDTH) - (j + 1), i, vars->f);
		i++;
	}
	if (vars->player.l)
		vars->player.nrealx = (int)vars->player.realx % 64;
	else
		vars->player.nrealx = (int)vars->player.realy % 64;
}

void	reder3d1(t_vars *vars, double wallstripheight, int j,double rayangle)
{
	int	walltop;
	int	wallbot;
	int	distft;

	walltop = ((HEIGHT) / 2) - (wallstripheight / 2);
	if (walltop < 0 || walltop >= HEIGHT)
		walltop = 0;
	wallbot = ((HEIGHT) / 2) + (wallstripheight / 2);
	if (wallbot >= HEIGHT || wallbot < 0)
		wallbot = (HEIGHT) - 1;
	draw_f_c(vars, wallbot, j);
	while (wallbot > walltop)
	{
		distft = walltop + (wallstripheight / 2) - ((HEIGHT) / 2);
		vars->player.nrealy = distft * ((float)64 / wallstripheight);
		my_mlx_pixel_put(&vars->img, (WIDTH - 1) - (j),
			walltop, get_color(vars,
				(int)vars->player.nrealy, (int)vars->player.nrealx, rayangle));
		walltop++;
	}
}

void render3d(t_vars *vars, int j, double rayangle)
{
	double	raydistance;
	double	distprojectionplan;
	int		wallstripheight;

	raydistance = vars->player.dist
		* cos(rayangle - vars->player.rotationangle);
	distprojectionplan = (WIDTH / 2)
		/ tan(vars->player.fov_angle / 2);
	wallstripheight = ((int)(TILE_SIZE / raydistance * distprojectionplan));
	reder3d1(vars, wallstripheight, j, rayangle);
}

void	cast(t_vars *vars , double rayangle)
{
	horizontalcast(vars, rayangle);
	verticalcast(vars, rayangle);
	if ((vars->player.dist < vars->player.ndist))
	{
		//draw_line(vars, rayangle, vars->player.realx, vars->player.realy);
		vars->player.l = 1;
	}
	else
	{
		//printf("ana fndst\n");
		vars->player.l = 0;
		vars->player.dist = vars->player.ndist;
		vars->player.realx = vars->player.nrealx;
		vars->player.realy = vars->player.nrealy;
		//draw_line(vars, rayangle, vars->player.realx, vars->player.realy);
	}
}

void castRays(t_vars *vars)
{
	double	rayangle;
	int		i;

	i = 0;
	rayangle = vars->player.rotationangle - (vars->player.fov_angle / 2);
	while (i < vars->player.ray_num)
	{
		rayangle += vars->player.fov_angle / vars->player.ray_num;
		rayangle = normalizeangle(rayangle);
		cast(vars, rayangle);
		render3d(vars, i, rayangle);
		i++;
	}
}

int lol(t_vars *vars,double y,double x)
{
	if (vars->map[((int)y / TILE_SIZE)][((int)(x + 5) / TILE_SIZE)] == '1')
		return (0);
	else if (vars->map[((int)y / TILE_SIZE)][((int)(x - 5) / TILE_SIZE)] == '1')
		return (0);
	else if (vars->map[((int)(y + 5) / TILE_SIZE)][((int)x / TILE_SIZE)] == '1')
		return (0);
	else if (vars->map[((int)(y - 5) / TILE_SIZE)][((int)x / TILE_SIZE)] == '1')
		return (0);
	return (1);
}

int walk(t_vars *vars,double movestep,double y,double x)
{
	if (vars->player.d == 2)
	{
		x += cos(vars->player.rotationangle + M_PI / 2) * movestep;
		y += sin(vars->player.rotationangle + M_PI / 2) * movestep;
	}
	else
	{
		x += cos(vars->player.rotationangle) * movestep;
		y += sin(vars->player.rotationangle) * movestep;
	}
	if (x >= 0 && x <= vars->width * TILE_SIZE && y >= 0
		&& y <= vars->height * TILE_SIZE
		&& vars->map[((int)floor(y / TILE_SIZE))]
		[((int)floor(x / TILE_SIZE))] != '1')
	{
		if (!lol(vars, y, x))
			return (0);
		vars->player.x = x;
		vars->player.y = y;
		vars->v = 1;
	}
	return (0);
}

void direction(t_vars *vars)
{
	double	movestep;
	double	x;
	double	y;

	if (vars->player.turndirection)
	{
		vars->player.rotationangle += vars->player.turndirection
			* vars->player.rotationspeed;
		vars->v = 1;
	}
	if (vars->player.walkdirection)
	{
		vars->player.rotationangle += vars->player.turndirection
			* vars->player.rotationspeed;
		movestep = vars->player.walkdirection * vars->player.movespeed;
		y = vars->player.y;
		x = vars->player.x;
		walk(vars, movestep, y, x);
	}
}

int ft_exit(t_vars *vars)
{
	(void)vars;
	exit(0);
}

int	update(t_vars *vars)
{
	(void)vars;
	mlx_hook(vars->mlx_win, 2, 1L << 0, key_pressed, vars);
	direction(vars);
	mlx_hook(vars->mlx_win, 3, 1L << 0, key_release, vars);
	mlx_hook(vars->mlx_win, 17, 1L << 0, ft_exit, vars);
	if (vars->v == 1)
	{
		if (vars->h == 1)
			mlx_destroy_image(vars->mlx, vars->img.img);
		vars->img.img = mlx_new_image(vars->mlx,
				WIDTH, HEIGHT);
		vars->img.addr = mlx_get_data_addr(vars->img.img,
				&vars->img.bits_per_pixel,
				&vars->img.line_length, &vars->img.endian);
		castRays(vars);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
		vars->v = 0;
	}
	return (0);
}

int	get_width(char	**map)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	tmp = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
			i++;
		if (tmp < i)
			tmp = i;
		j++;
	}
	return (tmp);
}

double	get_view(char	a)
{
	if ( a == 'N')
		return (3 * M_PI / 2);
	else if (a == 'S')
		return (M_PI / 2);
	else if (a == 'W')
		return (M_PI);
	else if (a == 'E')
		return (2 * M_PI);
	return (0);
}

void tex_add(t_vars *vars,t_prasing_data *data)
{
	vars->e.img = mlx_xpm_file_to_image(vars->mlx,
			data->east, &vars->e.w, &vars->e.h);
	vars->w.img = mlx_xpm_file_to_image(vars->mlx,
			data->west, &vars->w.w, &vars->w.h);
	vars->s.img = mlx_xpm_file_to_image(vars->mlx,
			data->south, &vars->s.w, &vars->s.h);
	vars->n.img = mlx_xpm_file_to_image(vars->mlx,
			data->north, &vars->n.w, &vars->n.h);
	if (!vars->n.img || !vars->w.img || !vars->e.img || !vars->s.img)
		print_error("error");
	vars->e.addr = mlx_get_data_addr(vars->e.img,
			&vars->e.bits_per_pixel,
			&vars->e.line_length, &vars->e.endian);
	vars->w.addr = mlx_get_data_addr(vars->w.img,
			&vars->w.bits_per_pixel,
			&vars->w.line_length, &vars->w.endian);
	vars->s.addr = mlx_get_data_addr(vars->s.img,
			&vars->s.bits_per_pixel,
			&vars->s.line_length, &vars->s.endian);
	vars->n.addr = mlx_get_data_addr(vars->n.img,
			&vars->n.bits_per_pixel,
			&vars->n.line_length, &vars->n.endian);
}

void init_player(t_vars *vars, t_prasing_data *data)
{
	vars->player.raduis = 3;
	vars->player.turndirection = 0;
	vars->player.walkdirection = 0;
	vars->player.rotationangle = get_view(data->direction);
	vars->player.movespeed = 10;
	vars->player.rotationspeed = 2 * (M_PI / 180);
	vars->player.fov_angle = 60 * (M_PI / 180);
	vars->player.ray_num = (WIDTH);
	tex_add(vars, data);
	vars->v = 1;
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	//printf("%d\n",i);
	return (i);
}
void	get_pos(t_vars *vars,t_prasing_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (vars->map[++i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == data->direction)
			{
				vars->player.x = (j * TILE_SIZE) + 32;
				vars->player.y = (i * TILE_SIZE) + 32;
				break ;
			}
			j++;
		}
	}
}

int	get_rgb(char	**str)
{
	int		x;
	int		r;
	int		g;
	int		b;
	char	*ptr;

	x = 1;
	ptr = NULL;
	while (str[0][x])
	{
		if (whitespace(str[0][x]))
		{
			ptr = ft_substr(str[0], x, ft_strlen(str[0]));
			break ;
		}
		x++;
	}
	r = atoi(ptr);
	g = atoi(str[1]);
	b = atoi(str[2]);
	free(ptr);
	return (createRGB(r, g, b));
}

char **editmap(char **map, int l)
{
	int		i;
	int		j;
	char	**m;

	j = 0;
	m = malloc(sizeof(char *) * (get_height(map) + 1));
	while (map[j])
	{
		i = 0;
		m[j] = malloc(sizeof(char) * l + 1);
		m[j][l] = 0;
		while (map[j][i])
		{
			m[j][i] = map[j][i];
			i++;
		}
		while (i < l)
		{
			m[j][i] = '1';
			i++;
		}
		j++;
	}
	m[j] = 0;
	return (m);
}

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
