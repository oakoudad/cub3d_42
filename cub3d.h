/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:52:31 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/13 23:59:43 by oakoudad         ###   ########.fr       */
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

typedef struct s_texture_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture_img;

typedef struct my_mlx
{
	void	*mlx;
	void	*win;
	void	*win3d;
	t_img	img;
	t_img	img3d;
}	t_mlx;

typedef struct my_hook
{
	char	x;
	char	y;
	char	cam;
}	t_hook;

typedef struct textureimg
{
	int				width;
	int				height;
	t_texture_img	img;
}	t_textureimg;

typedef struct elmmap
{
	int			texture_fd[4];
	t_texture	texture;
	int			line_nbr;
	int			player;
	double		p_x;
	double		p_y;
	int			dir;
	int			longer_line;
	char		**check_map;
	char		**map;
	t_mlx		m_mlx;
	t_color		floor;
	t_color		ceiling;
	t_hook		keys;
	t_textureimg	txtimg;
}	t_elm_map;


typedef struct raying
{
	float	h_wall_x;
	float	h_wall_y;
	float	v_wall_x;
	float	v_wall_y;
	float	v_step_y;
	float	v_step_x;
	float	h_step_y;
	float	h_step_x;
	int		vrt;
	int		hor;
	float	angl;
}t_raying;

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define BSIZE 64
# define PSIZE 1
# define HSCREEN 1000.0
# define WSCREEN 2000.0

# define W 13
# define D 2
# define S 1
# define A 0
# define ESC 53
# define CAMERA_R 124
# define CAMERA_L 123

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
float	to_positive_angle(float angle);
float	dist(t_elm_map *map, float endX, float endY);
int		is_wall(t_elm_map *map, float x, float y);

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
int		init_map(t_elm_map	*map, int fd);
int		check_map(t_elm_map	*map);
void	set_direction(t_elm_map *map, char c);

//RAYCASTING
void	raycasting_main(t_elm_map	*map);
void	put_block(int y, int x, t_elm_map *map, int color);
void	put_player_block(int y, int x, t_elm_map *map, int color);
int		events(int key, t_elm_map	*map);
void	draw_wall(t_elm_map *map, float wall_x, float wall_y, float i, float dilta, char c);
void	findwall(t_elm_map *map, float angle, float x);

// MATH
double	deg2rad(double deg);

// ERROR PRINT & FREE & DESTROY
int		put_error(char *str);

// mlx
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);


int	create_texture(int x, float y, t_elm_map *map, float h);
#endif