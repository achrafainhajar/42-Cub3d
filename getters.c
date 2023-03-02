/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:15:44 by aainhaja          #+#    #+#             */
/*   Updated: 2023/03/02 22:54:45 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

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

double	get_view(char a)
{
	if (a == 'N')
		return (3 * M_PI / 2);
	else if (a == 'S')
		return (M_PI / 2);
	else if (a == 'W')
		return (M_PI);
	else if (a == 'E')
		return (2 * M_PI);
	return (0);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	get_pos(t_vars	*vars, t_prasing_data *data)
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
	return (creratergb(r, g, b));
}
