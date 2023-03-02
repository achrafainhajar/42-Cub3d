/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:20:36 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/02 22:55:11 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3D.h"

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

int	walk(t_vars *vars, double movestep, double y, double x)
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

void	direction(t_vars *vars)
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
		castrays(vars);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
		vars->v = 0;
	}
	return (0);
}
