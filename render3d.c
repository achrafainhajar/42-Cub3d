/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:32:44 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/03 00:59:11 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3D.h"

unsigned int	get_color(t_vars *vars, int y, int x, double rayangle)
{
	char			*pixel;
	unsigned int	color;

	if (vars->player.l)
		return (get_v_color(vars, y, x, rayangle));
	else
	{
		if (!(rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI))
		{
			pixel = vars->e.addr + y * vars->e.line_length
				+ x * (vars->e.bits_per_pixel / 8);
			color = *((unsigned int *) pixel);
		}
		else
		{
			pixel = vars->w.addr + y * vars->w.line_length
				+ x * (vars->w.bits_per_pixel / 8);
			color = *((unsigned int *) pixel);
		}
	}
	return (color);
}

void	draw_f_c(t_vars *vars, int wallbot, int j)
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

void	reder3d1(t_vars *vars, double wallstripheight, int j, double rayangle)
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

void	render3d(t_vars *vars, int j, double rayangle)
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

void	castrays(t_vars	*vars)
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
