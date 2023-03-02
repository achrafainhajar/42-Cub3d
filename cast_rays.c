/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:27:55 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/02 22:47:28 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3D.h"

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

void	verticalcast1(t_vars *vars, double rayangle, int l)
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

void	horizontalcast(t_vars *vars, double rayangle)
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

void	cast(t_vars *vars, double rayangle)
{
	horizontalcast(vars, rayangle);
	verticalcast(vars, rayangle);
	if ((vars->player.dist < vars->player.ndist))
	{
		vars->player.l = 1;
	}
	else
	{
		vars->player.l = 0;
		vars->player.dist = vars->player.ndist;
		vars->player.realx = vars->player.nrealx;
		vars->player.realy = vars->player.nrealy;
	}
}
