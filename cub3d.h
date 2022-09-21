/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:52:31 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/21 21:15:08 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <mlx.h>

typedef struct tcolor
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct my_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct elmmap
{
	int			texture_fd[4];
	t_texture	texture;
	int			line_nbr;
	int			player;
	int			p_x;
	int			p_y;
	int			dir;
	int			longer_line;
	char		**map;
	t_mlx		m_mlx;
	t_color		floor;
	t_color		ceiling;
}	t_elm_map;

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define BSIZE 40
# define PSIZE 8

//UTILS
size_t	ft_strlen(const char	*s);
int		ft_isspace(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_isdigit(int c);
int		ft_arrlen(void **arr);
int		ft_atoi(const char *str);
void	check_digits(char	**rgb, t_elm_map *map, char *line);
void	check_color(char *line, t_elm_map *map);
int		check_empty_line(char *line);
char	*ignore_space(char *haystack);

//GET NEXT LINE
char	*get_line(char *r, int fd);
char	*ft_re(char *r);
char	*ft_affiche_line(char *r);
char	*get_next_line(int fd);

// PARSING
void	check_inputs(int ac, char **av);
void	check_extension(char *haystack, char *needle);
void	check_map_format(char *line, t_elm_map *map);
int		ft_strstart(char *haystack, char *needle);
void	read_file(char *path, t_elm_map *map);
char	*get_informations(char *line);
void	set_colors(char *line, t_color	*color, char **rgb);
int		init_map(char *path, t_elm_map	*map);
int		check_map(t_elm_map	*map);

//RAYCASTING
void	raycasting_main(t_elm_map	*map);
void	put_block(int y, int x, t_elm_map *map, int color);
void	put_player_block(int y, int x, t_elm_map *map, int color);

// MATH
double	deg2rad(double deg);

// ERROR PRINT & FREE & DESTROY
int		put_error(char *str);

#endif