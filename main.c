/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:11 by aainhaja          #+#    #+#             */
/*   Updated: 2023/02/17 09:37:14 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mlx.h>
# include <string.h>
#include <math.h>
# include "get_next_line.h"
#define P2 M_PI/2
#define P3 3*M_PI/2

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
	*(unsigned int*)dst = color;
}
int key_pressed(int key_code,t_vars *vars)
{
	if(key_code == W_KEY)
		vars->player.walkDirection = 1;
	else if(key_code == S_KEY)
		vars->player.walkDirection = -1;
	else if(key_code == 123)
		vars->player.turnDirection = 1;
	else if(key_code == 124)
		vars->player.turnDirection = -1;
}
int key_release(int key_code,t_vars *vars)
{

		if(key_code == W_KEY)
		vars->player.walkDirection = 0;
	else if(key_code == S_KEY)
		vars->player.walkDirection = 0;
	else if(key_code == 123)
		vars->player.turnDirection = 0;
	else if(key_code == 124)
		vars->player.turnDirection = 0;
}
void draw_map(t_vars *vars,int x,int y)
{
	if(vars->map[y / 32][x / 32] == '1')
	{
		my_mlx_pixel_put(&vars->img,  x, y, 0x00ff00);
	}
	else
		my_mlx_pixel_put(&vars->img,  x, y, 0xCFCFCF);
}
void draw(t_vars *vars,int x ,int y)
{
	int i = y;

	int j = x;
	if(x >= vars->width * 32 || y >= vars->height* 32)
		return;
	while(i < y + 32)
	{
		j = x;
		while(j < x + 32)
		{
			draw_map(vars,j,i);
			j++;
		}
		i++;
	}
}
void draw_line(t_vars *vars,float rayangle,float i ,float j)
{
	int x1 = (vars->player.x);
    int y1 = (vars->player.y);
    int x2 = i;
    int y2 = j;

    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float) steps;
    float y_inc = dy / (float) steps;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(&vars->img, x, y, 0xff00004);
        x += x_inc;
        y += y_inc;
    }
}
void render(t_vars *vars)
{
	int i = 0;
	int tilex;
	int pixel;
	int tiley;
	int j = 0;
	while(i < vars->height * 32)
	{
		j = 0;
		while(j < vars->width * 32)
		{
			tilex = j * 32;
			tiley = i * 32;
			draw(vars,tilex,tiley);
			j++;
		}
		i++;
	}
}

void	draw_square(t_vars *vars)
{
	// int	x;
	// int	y;

	// x = (vars->player.x * 32) - 5 / 2;
	// while (x <	(vars->player.x * 32) + 5 / 2)
	// {
	// 	y = (vars->player.y * 32) - 5 / 2;
	// 	while (y < (vars->player.y * 32) + 5 / 2)
	// 	{
	// 		my_mlx_pixel_put(&vars->img, x, y, 0xFFFFFF);
	// 		y++;
	// 	}
	// 	x++;
	// }


 double radius = 0;
    double i;
    while(radius < 3)
    {
        i = 0;
        while(i < 360)
        {
            my_mlx_pixel_put(&vars->img,(vars->player.x) + cos(i) *radius, (vars->player.y)+ sin(i) * radius,0xFF0000);
            i+=0.5;
        }
        radius++;
    }
}
// void cast(int columnid,t_vars *vars , float rayangle)
// {
// 	float xintercept;
// 	float yintercept;
// 	float ystep;
// 	float xstep;
	
// 	yintercept = floor(vars->player.y / 32) * 32;
// 	if(rayangle > 0 && rayangle < M_PI)
// 		yintercept += 32;
// 	xintercept = vars->player.x + (yintercept - vars->player.y) / tan(rayangle);
// 	ystep = -32;
// 	if(rayangle > 0 && rayangle < M_PI)
// 		ystep *= -1;
// 	xstep = 32 / tan(rayangle);
// 	if((rayangle < 0.5 * M_PI || rayangle > 1.5)* M_PI && xstep < 0)
// 		xstep = xstep * -1;
// 	if((rayangle >= 0.5 * M_PI || rayangle <= 1.5)* M_PI && xstep > 0)
// 			xstep = xstep * -1;
// 	float x;
// 	float y;
// 	x = xintercept + xstep;
// 	y = yintercept + ystep;
// 	while(vars->map[(int)y / 32][(int)x / 32] != '1')
// 	{
// 		x = x + xstep;
// 		y = y + ystep;
// 	}
// 	vars->player.realx = x;
// 	vars->player.realy = y;
// 	vars->player.dist = dist(vars->player.x,vars->player.y,x,y,rayangle);
// }
float dist(float ax,float ay ,float bx,float by,float ang)
{
	return(sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
float normalizeangle(float angle)
{
	angle = remainder(angle,2 * M_PI);
	if(angle < 0)
	{
		 angle = (2 * M_PI) + angle;
	}
	return(angle);
}
int horizontalcast(int columnid,t_vars *vars , float rayangle)
{
	float xintercept;
	float yintercept;
	float ystep;
	float xstep;
	float ntan = -1 / tan(rayangle);
	if(rayangle > M_PI)
	{
		yintercept = (((int) vars->player.y >> 6) << 6) -0.0001;
		xintercept = vars->player.x + (vars->player.y - yintercept) * ntan;
		ystep = -32;
		xstep = -ystep * ntan;
	}
	if(rayangle <  M_PI)
	{
		yintercept = (((int) vars->player.y >> 6) << 6) + 32;
		xintercept = vars->player.x + (vars->player.y - yintercept) * ntan;
		ystep = 32;
		xstep = -ystep * ntan;
	}
	float x;
	float y;
	vars->player.dist = 1000000000;
	x = xintercept + xstep;
	y = yintercept + ystep;
	if(x  < 0 || x  > vars->width * 32 || y > vars->height * 32 || y < 0)
			return(1);
	while(vars->map[(int)y / 32][(int)x / 32] != '1')
	{
		x = x + xstep;
		y = y + ystep;
		if(x  < 0 || x  > vars->width * 32 || y > vars->height * 32 || y < 0)
			return(1);
	}
	vars->player.realx = x;
	vars->player.realy = y;
	vars->player.dist = dist(vars->player.x,vars->player.y,x,y,rayangle);
}
int verticalcast(int columnid,t_vars *vars , float rayangle)
{
	float xintercept;
	float yintercept;
	float ystep;
	float xstep;
	float ntan = -tan(rayangle);
	if(rayangle > P2 && rayangle < P3)
	{
		xintercept = (((int) vars->player.x >> 6) << 6) -0.0001;
		yintercept = vars->player.y + (vars->player.x - xintercept) * ntan;
		xstep = -32;
		ystep = -xstep * ntan;
	}
	if(rayangle <  P2 || rayangle > P3)
	{
		xintercept = (((int) vars->player.x >> 6) << 6) + 32;
		yintercept = vars->player.y + (vars->player.x - xintercept) * ntan;
		xstep = 32;
		ystep = -xstep * ntan;
	}
	float x;
	float y;
	vars->player.ndist =1000000000;
	x = xintercept;
	y = yintercept;
	
	if(x  < 0 || x  > vars->width * 32 || y > vars->height * 32 || y < 0)
			return(1);
	while(vars->map[(int)y / 32][(int)x / 32] != '1')
	{
		x = x + xstep;
		y = y + ystep;
		if(x  < 0 || x  > vars->width * 32 || y > vars->height * 32 || y < 0)
			return(1);
	}
	vars->player.nrealx = x;
	vars->player.nrealy = y;
	vars->player.ndist = dist(vars->player.x,vars->player.y,x,y,rayangle);
	return(0);
}
void cast(int columnid,t_vars *vars , float rayangle)
{
	horizontalcast(columnid,vars,rayangle);
	verticalcast(columnid,vars,rayangle);
	printf( "%ld-%ld\n",vars->player.ndist,vars->player.dist);
	if(rayangle == 0 || rayangle == M_PI)
	{
		draw_line(vars,rayangle,vars->player.x,vars->player.y);
	}
	else if((vars->player.dist < vars->player.ndist))
		draw_line(vars,rayangle,vars->player.realx,vars->player.realy);
	else
		draw_line(vars,rayangle,vars->player.nrealx,vars->player.nrealy);
	
}
void castRays(t_vars *vars)
{
	int columnid = 0;
	float rayangle = vars->player.rotationAngle - (vars->player.fov_angle / 2);
	int i = 0;
	while(i < 1)
	{
		rayangle += vars->player.fov_angle / vars->player.ray_num;
		//printf("%f\n",vars->player.rotationAngle);
		cast(columnid,vars,vars->player.rotationAngle);
		columnid++;
		i++;
	}
}
int update(t_vars *vars)
{
	vars->img.img = mlx_new_image(vars->mlx, vars->width * 32, vars->height * 32);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length,
								&vars->img.endian);
	mlx_hook(vars->mlx_win, 2, 1L<<0, key_pressed, vars);
	if(vars->player.turnDirection)
	{
		vars->player.rotationAngle += vars->player.turnDirection * vars->player.rotationSpeed;
		vars->player.rotationAngle = normalizeangle(vars->player.rotationAngle);
	}
	if(vars->player.walkDirection)
	{
		int movestep = vars->player.walkDirection * vars->player.moveSpeed;
		float x;
		x = vars->player.x;
		x  += cos(vars->player.rotationAngle) * movestep;
		float y;
		y = vars->player.y;
		y += sin(vars->player.rotationAngle) * movestep;
		if(x > 0 && x < vars->width * 32 && y > 0 && y < vars->height * 32 && vars->map[(int)y / 32][ (int)x / 32] != '1')
		{
			vars->player.x = x;
			vars->player.y = y;
		}
	}
	mlx_hook(vars->mlx_win, 3, 1L<<0, key_release, vars);
	render(vars);
	castRays(vars);
	draw_square(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);					
}
int get_width(char **map)
{
	int i;

	i = 0;
	while(map[1][i])
		i++;
	return(i);	
}  
void init_player(t_vars *vars)
{
	vars->player.x = (vars->width / 2) * 32 + 16;
	vars->player.y = (vars->height / 2) * 32 + 16;
	vars->player.raduis = 3;
	vars->player.turnDirection = 0;
	vars->player.walkDirection = 0;
	vars->player.rotationAngle = (M_PI / 2) ;
	vars->player.moveSpeed = 2;
	vars->player.rotationSpeed = 2 * (M_PI/180);
	vars->player.fov_angle = 60 * (M_PI / 180);
	vars->player.ray_num = (vars->width) ;
}
int get_height(char **map)
{
	int i;

	i = 0;
	while(map[i])
		i++;
	return(i);
}
int	main(int argc, char **argv)
{
	char	*str;
	int		fd;
	t_vars	vars;

	fd = open(argv[1], O_RDONLY);
	str = matrix(fd);
	vars.map = ft_split(str, '\n');
	vars.mlx = mlx_init();
	vars.height = get_height(vars.map);
	vars.width = get_width(vars.map);
	vars.mlx_win = mlx_new_window(vars.mlx, vars.width * 32, vars.height * 32, "Cub3d");
	vars.img.img = mlx_new_image(vars.mlx, vars.width * 32, vars.height * 32);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
								&vars.img.endian);
	init_player(&vars);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_loop(vars.mlx);
	(void) argc;
}