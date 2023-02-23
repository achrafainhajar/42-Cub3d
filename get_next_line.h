/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:41:30 by aainhaja          #+#    #+#             */
/*   Updated: 2023/02/23 18:46:16 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define A_KEY 0
# define D_KEY 2
# define S_KEY 1
# define W_KEY 13
# define scale_factor 0.2
# define TILE_SIZE 64

typedef struct t_img {
    void *img;
    int bits_per_pixel;
    int line_length;
    int endian;
    char  *addr;
}				img;

typedef struct t_player
{
    float x;
    float y;
    int l;
    float realx;
    float nrealx;
    float nrealy;
    long ndist;
    float realy;
    int raduis;
    int turnDirection;
    int walkDirection;
    float rotationAngle;
    int moveSpeed;
    float rotationSpeed;
    float fov_angle;
    int ray_num;
    long dist;
}               Player;
typedef struct textures {
     void *img;
    int bits_per_pixel;
    int line_length;
    int endian;
    char  *addr;
    int w;
    int h;
}				tex;
typedef struct s_vars {
    void        *mlx;
    int         width;
    int         height;
    void        *mlx_win;
	char		**map;
    img         img;
    int v;
    tex         wall;
    Player      player;
}				t_vars;
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s, char const *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);

#endif