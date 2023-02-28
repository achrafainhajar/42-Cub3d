/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hlp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:50:25 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/25 13:01:45 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

int	type_check(char *map)
{
	char	*str;

	str = ft_strrchr(map, '.');
	if (!str)
		return (0);
	else if (ft_strcmp(str, ".cub"))
		return (0);
	if (ft_strlen(map) <= 4)
		return (0);
	return (1);
}

void	check_all_data(t_prasing_data *data)
{
	if (!data->ceiling || !data->direction || !data->east
		|| !data->floor || !data->map || !data->north
		|| !data->south || !data->west)
		print_error("error missing Data");
}

void	read_file_contents(char *filename, char **all)
{
	int		fd;
	char	*str;

	*all = NULL;
	fd = open(filename, 0);
	str = get_next_line(fd);
	if (fd < 0 || !str)
		print_error("error");
	while (str)
	{
		*all = ft_strjoin(*all, str);
		free(str);
		str = get_next_line(fd);
	}
}

void	print_error(char *str)
{
	printf("%s \n", str);
	exit(1);
}

void	parsing_befor_split(char *all)
{
	int	x;

	x = 0;
	while (all[x])
	{
		if (all[x] == '\n')
		{
			while (all[x] && !whitespace(all[x]))
				x++;
			if (all[x] == '1' || all[x] == '0')
			{
				while (all[x])
				{
					if (all[x] == '\n' && all[x + 1] && all[x + 1] == '\n')
						print_error("error");
					x++;
				}
			}
		}
		if (all[x])
			x++;
	}
}
