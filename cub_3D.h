/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:10:57 by mrafik            #+#    #+#             */
/*   Updated: 2023/02/27 21:09:23 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include<stdlib.h>
# include<stdio.h>
# include<unistd.h>
# include<fcntl.h>

typedef struct t_prasing_data
{
		char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**floor;
	char	**ceiling;
	char	**map;
	char	direction;
}			t_prasing_data;

# define A_KEY 0
# define D_KEY 2
# define S_KEY 1
# define W_KEY 13
# define scale_factor 1
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
    double x;
    double y;
    int l;
    double realx;
    double nrealx;
    double nrealy;
    long ndist;
    double realy;
    int raduis;
    int turnDirection;
    int walkDirection;
    double rotationAngle;
    double moveSpeed;
    double rotationSpeed;
    double fov_angle;
    int ray_num;
    long dist;
    int d;
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
    tex         N;
    tex         W;
    tex         E;
    tex         S;
    int f;
    int c;
    Player      player;
    char	**floor;
	char	**ceiling;
    double   tempx;
    double   tempy;
    double   temp1x;
    double   temp1y;
}				t_vars;

int		ft_strlen(const char *s);
int		ft_strlen2(char **str, int i);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, int start, int len);
int		ft_atoi(const char *str);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_isalpha(int c);
void	map_checker(char **ar, int i, t_prasing_data *data);
void	check_stranger(char **str, int x, t_prasing_data *data);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
void	print_error(char *str);
int		ft_isdigit(int c);
void	store_map(char **map, int *x, t_prasing_data *data);
void	ceiling_floor(char **map, int x, int i, t_prasing_data *data);
void	parsing_norm(char **map, int *x, int i, t_prasing_data *data);
void	check_all(char **map, t_prasing_data *data);
void	parsing(char *str, t_prasing_data *data);
void	parsing_befor_split(char *all);
void	print_error(char *str);
void	read_file_contents(char *filename, char **all);
void	check_all_data(t_prasing_data *data);
int		type_check(char *map);
void	check_stranger(char **str, int x, t_prasing_data *data);
void	get_direction(int t, t_prasing_data *data, char **str);
void	init(t_prasing_data *data);
int		store_data(char *str, t_prasing_data *data, int i);
int 	store_helper(char *str, int i, t_prasing_data *data, char *tmp);
int		texter_type(char *map);
int		check_texter(char *str, int i);
int		search(char *str, char *ptr, int i);
int		is_color(char *str);
void	if_num_color(char **tmp);
void	if_num_helper(char **tmp, int i);
void	color_norm(char **tmp, int i, int x);
void	color_helper(char *str);
void	ft_free(char **str);
int		whitespace(char a);

#endif