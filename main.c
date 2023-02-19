/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:11 by aainhaja          #+#    #+#             */
/*   Updated: 2023/02/19 20:01:02 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mlx.h>
# include <string.h>
#include <math.h>
# include "get_next_line.h"
#define P2 M_PI/2
#define P3 3 * M_PI/2

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
		my_mlx_pixel_put(&vars->img,  scale_factor * x, scale_factor * y, 0x00ff00);
	}
	else
		my_mlx_pixel_put(&vars->img,  scale_factor * x, scale_factor * y, 0xCFCFCF);
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
        my_mlx_pixel_put(&vars->img, scale_factor * x, scale_factor * y, 0xff00004);
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
 double radius = 0;
    double i;
    while(radius < 3)
    {
        i = 0;
        while(i < 360)
        {
            my_mlx_pixel_put(&vars->img,(vars->player.x * scale_factor) + cos(i) *radius, (vars->player.y * scale_factor)+ sin(i) * radius,0xFF0000);
            i+=0.5;
        }
        radius++;
    }
}
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
void horizontalcast(int columnid,t_vars *vars , float rayangle)
{
	float xintercept;
	float yintercept;
	float ystep;
	float xstep;
	int l = 0;
	
	yintercept = floor(vars->player.y / 32) * 32;
	if(rayangle > 0 && rayangle < M_PI)// down
		yintercept += 32;
	xintercept = vars->player.x + (yintercept - vars->player.y) / tan(rayangle);
	ystep = 32;
	if(!(rayangle > 0 && rayangle < M_PI))
		ystep *= -1;
	xstep = 32 / tan(rayangle);
	if((rayangle < 0.5 * M_PI || rayangle > 1.5* M_PI) && xstep < 0) // right
		xstep = xstep * -1;
	if(!(rayangle < 0.5 * M_PI || rayangle > 1.5* M_PI) && xstep > 0)
			xstep = xstep * -1;
	float x;
	float y;
	x = xintercept;
	y = yintercept;
	if(!(rayangle > 0 && rayangle < M_PI))
		y--;
	while(x >= 0 && x <= vars->width * 32 && y >= 0 && y <= vars->height * 32)
	{
		if(vars->map[(int)y / 32][(int)x / 32] == '1')
		{
			l = 1;
			break;
		}
		x = x + xstep;
		y = y + ystep;
	}
	vars->player.realx = x;
	vars->player.realy = y;
		if(l == 1)
		vars->player.dist = dist(vars->player.x,vars->player.y,x,y,rayangle);
	else 
		vars->player.dist = 10000000;
}
void verticalcast(int columnid,t_vars *vars , float rayangle)
{
	float xintercept;
	float yintercept;
	int l=  0;
	float ystep;
	float xstep;
	
	xintercept = floor(vars->player.x / 32) * 32;
	if((rayangle < 0.5 * M_PI || rayangle > 1.5* M_PI)) //right
		xintercept += 32;
	yintercept = vars->player.y + (xintercept - vars->player.x) * tan(rayangle);
	xstep = 32;
	if(!(rayangle < 0.5 * M_PI || rayangle > 1.5* M_PI)) // left
		xstep *= -1;
	ystep = 32 * tan(rayangle);
	if(!(rayangle > 0 && rayangle < M_PI) && ystep > 0)
		ystep = ystep * -1;
	if(rayangle > 0 && rayangle < M_PI && ystep < 0)
		ystep = ystep * -1;
	float x;
	float y;
	x = xintercept;
	y = yintercept;
	if(!(rayangle < 0.5 * M_PI || rayangle > 1.5* M_PI))
		x--;
	while(x >= 0 && x <= vars->width * 32 && y >= 0 && y <= vars->height * 32)
	{
		if(vars->map[(int)y / 32][(int)x / 32] == '1')
		{
			l = 1;
			break;
		}
		x = x + xstep;
		y = y + ystep;
	}
	vars->player.nrealx = x;
	vars->player.nrealy = y;
	if(l == 1)
		vars->player.ndist = dist(vars->player.x,vars->player.y,x,y,rayangle);
	else 
		vars->player.ndist = 10000000;
}
void render3d(t_vars *vars,int j,float rayangle)
{
	int i = 0;
	float raydistance = vars->player.dist  * cos(rayangle - vars->player.rotationAngle);
	float distprojectionplan = ((vars->width * 32) / 2) / tan(vars->player.fov_angle / 2);
	int wallstripheight = (32 / raydistance) * distprojectionplan;
	int walltop = ((vars->height * 32) / 2) - (wallstripheight / 2);
	if(walltop < 0 || walltop >= vars->height * 32)
		walltop = 0;
	int wallbot = ((vars->height * 32) / 2) + (wallstripheight / 2);
	if(wallbot >= vars->height * 32 || wallbot < 0)
		wallbot  = (vars->height * 32) - 1;
	int color = 0xff00004 - vars->player.dist;
	//printf( "%d--%d\n",walltop,wallbot);
	while(wallbot > walltop)
	{
		my_mlx_pixel_put(&vars->img, (vars->width * 32) - (j + 1), walltop, color);
		walltop++;
	}
}
void cast(int columnid,t_vars *vars , float rayangle)
{
	horizontalcast(columnid,vars,rayangle);
	verticalcast(columnid,vars,rayangle);
	if((vars->player.dist < vars->player.ndist))
	{
		int l;
		//draw_line(vars,rayangle,vars->player.realx,vars->player.realy);
	}
	else
	{
		vars->player.dist = vars->player.ndist;
		//draw_line(vars,rayangle,vars->player.nrealx,vars->player.nrealy);
	}
	
}
void castRays(t_vars *vars)
{
	int columnid = 0;
	float rayangle = vars->player.rotationAngle - (vars->player.fov_angle / 2);
	int i = 0;
	while(i < vars->player.ray_num)
	{
		rayangle += vars->player.fov_angle / vars->player.ray_num;
		rayangle = normalizeangle(rayangle);
		cast(columnid,vars,rayangle);
		render3d(vars,i,rayangle);
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
	//render(vars);
	castRays(vars);
	//draw_square(vars);
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
	vars->player.rotationAngle = M_PI / 2 ;
	vars->player.moveSpeed = 2;
	vars->player.rotationSpeed = 2 * (M_PI/180);
	vars->player.fov_angle = 60 * (M_PI / 180);
	vars->player.ray_num = (vars->width * 32);
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