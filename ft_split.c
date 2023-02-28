/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:12:52 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/15 16:36:33 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3D.h"

static int	ft_size(char *str, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (str[x] == c)
		x++;
	while (str[x] != '\0')
	{
		if (str[x] == c)
		{
			y++;
			while (str[x] == c)
				x++;
		}
		else
			x++;
	}
	return (++y);
}

static char	*ft_cm(char *str, const char *s, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s[x] != '\0')
	{
		if (s[x] == c)
			break ;
		x++;
	}
	str = (char *) malloc ((x + 1) * sizeof(char *));
	while (y < x)
	{
		str[y] = s[y];
		y++;
	}
	str[x] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!s)
		return (0);
	str = (char **) malloc ((ft_size((char *)s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (s[y] != '\0')
	{
		if (s[y] != c)
		{
			str[x] = ft_cm(str[x], &s[y], c);
			x++;
			while (s[y] != c && s[y] != '\0')
				y++;
		}
		else
			y++;
	}
	str[x] = 0;
	return (str);
}
