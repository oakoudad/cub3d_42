/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:52:31 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/16 15:11:35 by eelmoham         ###   ########.fr       */
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
	int				texture_fd[4];
	t_texture		texture;
	int				line_nbr;
	int				player;
	double			p_x;
	double			p_y;
	int				dir;
	int				longer_line;
	char			**check_map;
	char			**map;
	t_mlx			m_mlx;
	t_color			floor;
	t_color			ceiling;
	t_hook			keys;
	t_textureimg	texture_no;
	t_textureimg	texture_we;
	t_textureimg	texture_ea;
	t_textureimg	texture_so;
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
}	t_raying;

typedef struct s_txt
{
	float	x;
	float	y;
	float	h;
	char	c;
}	t_txt;	

typedef struct s_drwall
{
	float			h;
	float			distance;
	float			delta_x;
	float			delta_y;
	float			yy;
	float			to;
	unsigned int	xcolor;
	t_txt			txt;
}	t_drwall;

# define NO 0
# define SO 1
# define WE 2
# define EA 3

# define MAPSIZE 10
# define BSIZE 128
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
float	fix_angle(float angle);
float	dist(t_elm_map *map, float endX, float endY);
int		is_wall(t_elm_map *map, float x, float y);
char	*get_line(char *r, int fd);
char	*ft_re(char *r);
char	*ft_affiche_line(char *r);
char	*get_next_line(int fd);
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
void	raycasting_main(t_elm_map	*map);
void	put_block(int y, int x, t_elm_map *map, int color);
int		events(int key, t_elm_map	*map);
void	draw_wall(t_elm_map *map, float i, t_txt data);
void	findwall(t_elm_map *map, float angle, float x);
double	deg2rad(double deg);
int		put_error(char *str);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		create_texture(t_elm_map *map, t_txt *txt);
int		creatergb(int r, int g, int b);
void	put_block(int y, int x, t_elm_map	*map, int color);
void	draw_map_2d(t_elm_map	*map);
void	dst_draw2(t_elm_map *map, t_raying *r, int x, float distv);
void	dst_draw(t_elm_map *map, t_raying *r, int x);
void	get_hor_wall(t_elm_map *map, t_raying	*raying, float angle);
void	get_vrt_wall(t_elm_map *map, t_raying	*raying, float angle);
void	init_raying(t_elm_map *map, float *angle, t_raying	*raying);
t_txt	init_data(float x, float y, float h, char c);
void	dst_draw_norm(t_elm_map *map, t_raying *r, int x, float distv);
void	init_draw_wall(t_elm_map *map, t_txt data, t_drwall	*drwall);
int		draw_line(t_elm_map *map, float endX, float endY);
void	player_point(t_elm_map *map, int i, int j);
void	draw_map2(t_elm_map *map, int j);
int		events(int key, t_elm_map	*map);
int		round_base(int nbr);
void	draw_3d(t_elm_map *map);
#endif