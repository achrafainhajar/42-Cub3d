/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tstt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:44:46 by mrafik            #+#    #+#             */
/*   Updated: 2023/03/01 17:36:14 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

int	ft_strlen2(char **str, int i)
{
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

void	norm_map_check(char **ar, int i, t_prasing_data *data, int j)
{
	int	size;

	size = ft_strlen2(ar, i);
	while (j < ft_strlen(ar[i]))
	{
		if (ar[i][j] == '0' || ar[i][j] == data->direction)
		{
			if (i + 1 >= size || (ar[i + 1][j] != '0'
				&& ar[i + 1][j] != '1' && ar[i + 1][j] != data->direction))
				print_error("Map error");
			if (i - 1 < 0 || (ar[i - 1][j] != '0'
				&& ar[i - 1][j] != '1' && ar[i - 1][j] != data->direction))
				print_error("Map error");
			if (j + 1 > ft_strlen(ar[i]) || (ar[i][j + 1] != '0'
				&& ar[i][j + 1] != '1' && ar[i][j + 1] != data->direction))
				print_error("Map error");
			if (j - 1 < 0 || (ar[i][j - 1] != '0'
				&& ar[i][j - 1] != '1' && ar[i][j - 1] != data->direction))
				print_error("Map error");
		}
		j++;
	}
}

void	map_checker(char **ar, int i, t_prasing_data *data)
{
	int	size;
	int	j;

	size = ft_strlen2(ar, i);
	check_stranger(ar, i, data);
	while (i < size)
	{
		j = 0;
		norm_map_check(ar, i, data, j);
		i++;
	}
}
