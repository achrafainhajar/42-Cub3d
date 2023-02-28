/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hlp1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:51:50 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/26 16:16:17 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

int	store_helper(char *str, int i, t_prasing_data *data, char *tmp)
{
	if (search(str, "NO", i))
	{
		if (data->north)
			print_error("Duplicated Data");
		data->north = tmp;
		return (1);
	}
	else if (search(str, "EA", i))
	{
		if (data->east)
			print_error("Duplicated Data");
		data->east = tmp;
		return (1);
	}
	else if (search(str, "WE", i))
	{
		if (data->west)
			print_error("Duplicated Data");
		data->west = tmp;
		return (1);
	}
	return (0);
}

int	store_data(char *str, t_prasing_data *data, int i)
{
	int		fd;
	char	*tmp;
	int		d;

	d = i;
	d += 2;
	while (!whitespace(str[d]))
		d++;
	tmp = ft_substr(str, d, ft_strlen(str));
	fd = open(tmp, 0);
	if (fd < 0 || !texter_type(tmp))
		print_error("Bad file descriptor or file not xpm");
	//free(tmp);
	if (store_helper(str, i, data, tmp))
		return (1);
	else if (search(str, "SO", i))
	{
		if (data->south)
			print_error("Duplicated Data");
		data->south = tmp;
		return (1);
	}
	return (0);
}

void	init(t_prasing_data *data)
{
	data->ceiling = NULL;
	data->east = NULL;
	data->floor = NULL;
	data->map = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->direction = 0;
}

void	get_direction(int t, t_prasing_data *data, char **str)
{
	int	i;

	while (str[t])
	{
		i = 0;
		while (str[t][i])
		{
			if (str[t][i] == 'N' || str[t][i] == 'S'
				|| str[t][i] == 'E' || str[t][i] == 'W')
			{
				if (data->direction != 0)
					print_error("Duplicated Data");
				else
				data->direction = str[t][i];
			}
			i++;
		}
		t++;
	}
}

void	check_stranger(char **str, int x, t_prasing_data *data)
{
	int	i;

	get_direction(x, data, str);
	while (str[x])
	{
		i = 0;
		while (str[x][i])
		{
			if (whitespace(str[x][i]))
			{
				if (str[x][i] != '0' && str[x][i] != '1'
					&& str[x][i] != data->direction)
					print_error("error");
			}
			i++;
		}
		x++;
	}
}