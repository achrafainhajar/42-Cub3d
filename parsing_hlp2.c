/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hlp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:53:22 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/28 23:52:08 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

void	if_num_color(char **tmp)
{
	int	i;
	int	x;

	i = 0;
	while (tmp[i])
	{
		if (i == 0)
			x = 1;
		else
			x = 0;
		while (tmp[i][x])
		{
			if (whitespace(tmp[i][x]) && !ft_isdigit(tmp[i][x]))
			{
				print_error("error");
			}
			x++;
		}
		if_num_helper(tmp, i);
		i++;
	}
}

int	is_color(char *str)
{
	int		x;
	int		i;
	char	**tmp;

	color_helper(str);
	tmp = ft_split(str, ',');
	if (ft_strlen2(tmp, 0) != 3)
		print_error("Error");
	i = 0;
	while (tmp[i])
	{
		if (i == 0)
			x = 1;
		else
			x = 0;
		color_norm(tmp, i, x);
		i++;
	}
	if_num_color(tmp);
	ft_free(tmp);
	return (1);
}

int	search(char *str, char *ptr, int i)
{
	int	x;

	x = 0;
	while (1)
	{
		if (!ptr[x] && (!str[i] || !whitespace(str[i])))
			return (1);
		if (str[i] != ptr[x])
			return (0);
		i++;
		x++;
	}
	return (0);
}

int	check_texter(char *str, int i)
{
	if (search(str, "NO", i) || search(str, "EA", i)
		|| search(str, "WE", i) || search(str, "SO", i))
		return (1);
	else
		return (0);
}

int	texter_type(char *map)
{
	char	*str;

	str = ft_strrchr(map, '.');
	if (!str)
		return (0);
	else if (ft_strcmp(str, ".xpm"))
		return (0);
	if (ft_strlen(map) <= 4)
		return (0);
	return (1);
}
