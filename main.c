/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:11 by aainhaja          #+#    #+#             */
/*   Updated: 2023/02/26 14:44:39 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mlx.h>
# include <string.h>
#include <math.h>
# include "get_next_line.h"
#define P2 M_PI/2
#define P3 3 * M_PI/2

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
char	**ft_splitcpy(const char *s, char c, char **str, int alloc)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			str[cnt][j] = s[i];
			i++;
			j++;
		}
		if (cnt < alloc)
			str[cnt][j] = '\0';
		cnt++;
	}
	if (i != 0 && s[i - 1] == c)
		cnt--;
	str[cnt] = NULL;
	return (str);
}

char	**ft_charcount(const char *s, char c, char **str, int alloc)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	j = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			j++;
		}
		if (cnt < alloc)
			str[cnt] = malloc(sizeof(char) * j + 1);
		if (str == NULL)
			return (0);
		j = 0;
		cnt++;
	}
	return (ft_splitcpy(s, c, str, alloc));
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		cnt;
	char	**str;

	if (!s)
		return (0);
	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			cnt++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	str = malloc(sizeof(char *) * (cnt + 1));
	if (str == NULL)
		return (0);
	return (ft_charcount(s, c, str, cnt));
}

char	*matrix(int fd)
{
	char	*str;
	char	*sret;
	char	*fr;

	fr = malloc(sizeof(char *) * 5);
	sret = NULL;
	str = get_next_line(fd);
	while (str)
	{
		sret = ft_strjoin(sret, str);
		free(fr);
		free(str);
		fr = sret;
		str = get_next_line(fd);
	}
	return (sret);
}
void	my_mlx_pixel_put(img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int key_pressed(int key_code,t_vars *vars)
{
	if (key_code == W_KEY)
		vars->player.walkDirection = 1;
	else if (key_code == S_KEY)
		vars->player.walkDirection = -1;
	else if (key_code == 123)
		vars->player.turnDirection = 1;
	else if (key_code == 124)
		vars->player.turnDirection = -1;
	else if (key_code == 2)
	{
		vars->player.d = 2;
		vars->player.walkDirection = -1;
	}
	else if (key_code == 0)
	{
		vars->player.d = 2;
		vars->player.walkDirection = 1;
	}
}

int	key_release(int	key_code,t_vars	*vars)
{
	if (key_code == W_KEY)
		vars->player.walkDirection = 0;
	else if (key_code == S_KEY)
		vars->player.walkDirection = 0;
	else if (key_code == 123)
		vars->player.turnDirection = 0;
	else if (key_code == 124)
		vars->player.turnDirection = 0;
	else if (key_code == 2)
	{
		vars->player.d = 0;
		vars->player.walkDirection = 0;
	}
	else if (key_code == 0)
	{
		vars->player.d = 0;
		vars->player.walkDirection = 0;
	}
}

double	dist(double ax,double ay ,double bx,double by,double ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

double normalizeangle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle <= 0)
	{
		angle = (2 * M_PI) + angle;
	}
	return (angle);
}

void	horizontalcast1(t_vars *vars, double rayangle, int l)
{
	double	y1;

	while (vars->tempx >= 0 && vars->tempx < vars->width * TILE_SIZE
		&& vars->tempy >= 0 && vars->tempy < vars->height * TILE_SIZE)
	{
		y1 = vars->tempy;
		if (!(rayangle > 0 && rayangle < M_PI))
			y1--;
		if (vars->map[(int)floor(y1 / TILE_SIZE)]
			[(int)floor(vars->tempx / TILE_SIZE)] == '1')
		{
			l = 1;
			break ;
		}
		vars->tempx = vars->tempx + vars->temp1x;
		vars->tempy = vars->tempy + vars->temp1y;
	}
	vars->player.realx = vars->tempx;
	vars->player.realy = vars->tempy;
	if (l == 1)
		vars->player.dist = dist(vars->player.x, vars->player.y,
				vars->tempx, vars->tempy, rayangle);
	else
		vars->player.dist = 10000000;
}

void horizontalcast(int columnid, t_vars *vars, double rayangle)
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

void verticalcast1(t_vars *vars, double rayangle, int l)
{
	double	x;

	while (vars->tempx >= 0 && vars->tempx < vars->width * TILE_SIZE
		&& vars->tempy >= 0 && vars->tempy < vars->height * TILE_SIZE)
	{
		x = vars->tempx;
		if (!(rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI))
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
				vars->tempx, vars->tempy, rayangle);
	else
		vars->player.ndist = 10000000;
}

void	verticalcast(int columnid, t_vars *vars, double rayangle)
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

int	get_color(t_vars *vars, int y, int x)
{
	char	*pixel;
	int		color;

	pixel = vars->wall.addr + y * vars->wall.line_length
		+ x * (vars->wall.bits_per_pixel / 8);
	color = *((int *) pixel);
	return (color);
}

void	reder3d1(t_vars *vars, double wallstripheight, int j)
{
	int	walltop;
	int	wallbot;
	int	distft;

	walltop = ((vars->height * TILE_SIZE) / 2) - (wallstripheight / 2);
	if (walltop < 0 || walltop >= vars->height * TILE_SIZE)
		walltop = 0;
	wallbot = ((vars->height * TILE_SIZE) / 2) + (wallstripheight / 2);
	if (wallbot >= vars->height * TILE_SIZE || wallbot < 0)
		wallbot = (vars->height * TILE_SIZE) - 1;
	if (vars->player.l)
		vars->player.nrealx = (int)vars->player.realx % 64;
	else
		vars->player.nrealx = (int)vars->player.realy % 64;
	while (wallbot > walltop)
	{
		distft = walltop + (wallstripheight / 2 ) - ((vars->height * 64) / 2);
		vars->player.nrealy = distft * ((float)64/ wallstripheight);
		my_mlx_pixel_put(&vars->img, (vars->width * TILE_SIZE - 1) - (j),
			walltop, get_color(vars,
				(int)vars->player.nrealy, (int)vars->player.nrealx));
		walltop++;
	}
}

void render3d(t_vars *vars, int j, double rayangle)
{
	double	raydistance;
	double	distprojectionplan;
	int		wallstripheight;

	raydistance = vars->player.dist
		* cos(rayangle - vars->player.rotationAngle);
	distprojectionplan = ((vars->width * TILE_SIZE) / 2) 
		/ tan(vars->player.fov_angle / 2);
	wallstripheight = ((int)(TILE_SIZE / raydistance * distprojectionplan));
	reder3d1(vars, wallstripheight, j);
}

void	cast(int columnid, t_vars *vars , double rayangle)
{
	rayangle = normalizeangle(rayangle);
	horizontalcast(columnid, vars,rayangle);
	verticalcast(columnid, vars,rayangle);
	if ((vars->player.dist < vars->player.ndist))
	{
		//printf("ana fdst\n");
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
	rayangle = vars->player.rotationAngle - (vars->player.fov_angle / 2);
	while (i < vars->player.ray_num)
	{
		rayangle += vars->player.fov_angle / vars->player.ray_num;
		cast(i, vars, rayangle);
		render3d(vars, i, rayangle);
		i++;
	}
}
int walk(t_vars *vars,double movestep,double y,double x)
{
	if (vars->player.d == 2)
	{
		x += cos(vars->player.rotationAngle + M_PI / 2) * movestep;
		y += sin(vars->player.rotationAngle + M_PI / 2) * movestep;
	}
	else
	{
		x += cos(vars->player.rotationAngle) * movestep;
		y += sin(vars->player.rotationAngle) * movestep;
	}
	if (x >= 0 && x <= vars->width * TILE_SIZE && y >= 0
		&& y <= vars->height * TILE_SIZE
		&& vars->map[((int)floor(y/ TILE_SIZE))]
		[((int)floor(x/ TILE_SIZE))] != '1')
	{
		if (vars->map[((int)y / TILE_SIZE)][((int)(x + 10)/ TILE_SIZE)] == '1')
				x = vars->player.x;
		else if (vars->map[((int)y / TILE_SIZE)][((int)(x - 10)/ TILE_SIZE)] == '1')
			x = vars->player.x;
		else if (vars->map[((int)(y + 10) / TILE_SIZE)][((int)x / TILE_SIZE)] == '1')
			y = vars->player.y;
		else if (vars->map[((int)(y - 10) / TILE_SIZE)][((int)x / TILE_SIZE)] == '1')
				y =vars->player.y;
		vars->player.x = x;
		vars->player.y = y;
		vars->v = 1;
	}
}

void direction(t_vars *vars)
{
	double	movestep;
	double	x;
	double	y;

	if (vars->player.turnDirection)
	{
		vars->player.rotationAngle += vars->player.turnDirection
			* vars->player.rotationSpeed;
		vars->player.rotationAngle = normalizeangle(vars->player.rotationAngle);
		vars->v = 1;
	}
	if (vars->player.walkDirection)
	{
		vars->player.rotationAngle += vars->player.turnDirection
			* vars->player.rotationSpeed;
		vars->player.rotationAngle = normalizeangle(vars->player.rotationAngle);
		movestep = vars->player.walkDirection * vars->player.moveSpeed;
		y = vars->player.y;
		x = vars->player.x;
		walk(vars, movestep, y, x);
	}
}

int	update(t_vars *vars)
{
	double	x;
	double	y;
	double	movestep;

	mlx_hook(vars->mlx_win, 2, 1L << 0, key_pressed, vars);
	direction(vars);
	mlx_hook(vars->mlx_win, 3, 1L << 0, key_release, vars);
	if (vars->v == 1)
	{
		vars->img.img = mlx_new_image(vars->mlx,
				vars->width * TILE_SIZE,
				vars->height * TILE_SIZE);
		vars->img.addr = mlx_get_data_addr(vars->img.img,
				&vars->img.bits_per_pixel,
				&vars->img.line_length, &vars->img.endian);
		//render(vars);
		castRays(vars);
		//draw_square(vars);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);	
		vars->v = 0;
	}
}

int	get_width(char **map)
{
	int	i;

	i = 0;
	while (map[1][i])
		i++;
	return (i);
}

void init_player(t_vars *vars)
{
	int	w;
	int	h;

	vars->player.x = (vars->width / 2) * TILE_SIZE + 32;
	vars->player.y = (vars->height / 2) * TILE_SIZE + 32;
	vars->player.raduis = 3;
	vars->player.turnDirection = 0;
	vars->player.walkDirection = 0;
	vars->player.rotationAngle = M_PI / 2 ;
	vars->player.moveSpeed = 3;
	vars->player.rotationSpeed = (M_PI / 180);
	vars->player.fov_angle = 60 * (M_PI / 180);
	vars->player.ray_num = (vars->width * TILE_SIZE);
	vars->wall.img = mlx_xpm_file_to_image(vars->mlx,
			"floor.xpm", &vars->wall.w, &vars->wall.h);
	vars->wall.addr = mlx_get_data_addr(vars->wall.img,
			&vars->wall.bits_per_pixel,
			&vars->wall.line_length, &vars->wall.endian);
	vars->v = 1;
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	char	*str;
	int		fd;
	t_vars	vars;

	fd = open(argv[1], O_RDONLY);
	str = matrix(fd);
	vars.map = ft_split(str, '\n');
	vars.player.d = 0;
	vars.mlx = mlx_init();
	vars.height = get_height(vars.map);
	vars.width = get_width(vars.map);
	vars.mlx_win = mlx_new_window(vars.mlx, vars.width * TILE_SIZE,
			vars.height * TILE_SIZE, "Cub3d");
	init_player(&vars);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_loop(vars.mlx);
	(void) argc;
}