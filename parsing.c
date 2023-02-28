/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:45:31 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/28 02:56:16 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

void	store_map(char **map, int *x, t_prasing_data *data)
{
	int	v;
	int	k;

	map_checker(map, (*x), data);
	v = ft_strlen2(map,*x) - (*x) + 1;
	data->map = (char **) malloc ((v + 1) * sizeof(char *));
	k = 0;
	while (map[*x])
	{
		data->map[k] = ft_strdup(map[*x]);
		k++;
		(*x)++;
	}
	(*x)--;
	data->map[k] = 0;
}

void	ceiling_floor(char **map, int x, int i, t_prasing_data *data)
{
	if (!is_color(map[x]))
		print_error("Color error");
	if (search(map[x], "F", i))
	{
		if (data->floor)
			print_error("duplicated data");
		data->floor = ft_split(map[x], ',');
	}
	else
	{
		if (data->ceiling)
			print_error("duplicated data");
		data->ceiling = ft_split(map[x], ',');
	}
}

void	parsing_norm(char **map, int *x, int i, t_prasing_data *data)
{
	while (map[*x][i])
	{
		if (whitespace(map[*x][i]))
		{
			if (check_texter(map[*x], i))
			{
				store_data(map[*x], data, i);
				break ;
			}
			else if (search(map[*x], "F", i) || search(map[*x], "C", i))
			{
				ceiling_floor(map, *x, i, data);
				break ;
			}
			else if (map[*x][i] == 48 || map[*x][i] == 49)
			{
				store_map(map, x, data);
				break ;
			}
			else
				print_error("error");
		}
		i++;
	}
}

void	check_all(char **map, t_prasing_data *data)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (map[x])
	{
		parsing_norm(map, &x, i, data);
		x++;
	}
}

void	parsing(char *str, t_prasing_data *data)
{
	char			*all;
	char			**map;

	init(data);
	read_file_contents(str, &all);
	parsing_befor_split(all);
	map = ft_split(all, '\n');
	free(all);
	check_all(map, data);
	ft_free(map);
	check_all_data(data);
}
