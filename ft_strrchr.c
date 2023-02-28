/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:15:37 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/17 14:22:46 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub_3D.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == c)
		{
			return ((char *)(s + len));
		}
		len--;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0')
		&& (s2[i] != '\0') && (s1[i] == s2[i]))
	{
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
