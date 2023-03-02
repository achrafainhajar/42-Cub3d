/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:34:48 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/03 00:05:48 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3D.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

unsigned long	creratergb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

unsigned int	get_v_color(t_vars	*vars, int y, int x, double rayangle)
{
	char			*pixel;
	unsigned int	color;

	color = 0;
	if (!(rayangle > 0 && rayangle < M_PI))
	{
		pixel = vars->s.addr + y * vars->s.line_length
			+ x * (vars->s.bits_per_pixel / 8);
		color = *((unsigned int *) pixel);
	}
	else if ((rayangle > 0 && rayangle < M_PI))
	{
		pixel = vars->n.addr + y * vars->n.line_length
			+ x * (vars->n.bits_per_pixel / 8);
		color = *((unsigned int *) pixel);
	}
	return (color);
}
