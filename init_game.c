/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:22:47 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/02 22:26:52 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3D.h"

void	tex_add(t_vars *vars, t_prasing_data *data)
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

void	init_player(t_vars *vars, t_prasing_data *data)
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

int	ft_exit(t_vars *vars)
{
	(void)vars;
	exit(0);
}

int	lol(t_vars *vars, double y, double x)
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

char	**editmap(char **map, int l)
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
