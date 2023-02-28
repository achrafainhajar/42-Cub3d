/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hlp3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:54:38 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/28 20:41:37 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

int	whitespace(char a)
{
	int	i;

	i = 0;
	if (a == ' '
		|| a == '\t'
		|| a == '\n'
		|| a == '\v'
		|| a == '\f'
		|| a == '\r' )
	{
		return (0);
	}
	return (1);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	color_helper(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			x++;
			if (str[i + 1] && str[i + 1] == ',')
				print_error("error");
		}
		i++;
	}
	if (x != 2)
		print_error("error");
}

void	color_norm(char **tmp, int i, int x)
{
	int	t;

	t = 0;
	while (tmp[i][x])
	{
		if (whitespace(tmp[i][x]))
		{
			t = 1;
			while (tmp[i][x] && whitespace(tmp[i][x]))
				x++;
			while (tmp[i][x])
			{
				if (whitespace(tmp[i][x]))
					print_error("Color error");
				x++;
			}
		}
		else if (!tmp[i][x] && t == 0)
			print_error("Color error");
		if (tmp[i][x])
			x++;
	}
}

void	if_num_helper(char **tmp, int i)
{
	int		x;
	char	*ptr;

	if (i == 0)
	{
		x = 1;
		while (tmp[i][x])
		{
			if (whitespace(tmp[i][x]))
			{
				ptr = ft_substr(tmp[i], x, ft_strlen(tmp[i]));
				if (ft_atoi(ptr) > 255 || ft_atoi(ptr) < 0)
					print_error("error");
				free(ptr);
			}
			x++;
		}
	}
	else
		if (ft_atoi(tmp[i]) > 255 || ft_atoi(tmp[i]) < 0)
			print_error("error");
}
