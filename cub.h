/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:48:27 by het-taja          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:28 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

# define BUFFER_SIZE 42
# define WIND_W 1280
# define WIND_H 720
# define SPEED 3
# define PI 3.14159265358979323846
# define TILE_SIZE 64
# define FOV 60
# define ANG_STEP 0.047
# define WALL_H 75

typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		height;
	int		width;
	int		bpp;
	int		size_line;
	int		endian;
	void	*win;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		*floor;
	int		*ceiling;
	char	*save;
	char	*key;
	char	pv;
	double	pa;
	int		px;
	int		py;
	char	flag;
	int		pos;
	int		c_color;
	int		f_color;
	t_img	image;
	t_img	wall_s;
	t_img	wall_n;
	t_img	wall_w;
	t_img	wall_e;
}			t_game;

size_t			ftstrlen(const char *s);
char			*ftstrdup(const char *s1);
char			*my_strjoin(char *s1, char const *s2);
void			err(char *str);
char			*get_next_line(int fd, bool flag);
bool			space_checker(char c);
bool			check_var(char *str, t_game *game);
bool			save_checker(t_game *game, bool flag, char c);
bool			afterline(char *line, int i);
bool			path_checker(t_game *game, char *var, char *line, int i);
bool			searchar(char *str);
bool			help(char *temp, t_game *game, int *counter, char *var);
bool			line_parser(t_game *game, char *var, char *str, int i);
bool			color_checker(t_game *game, char *var, char *line, int i);
bool			put_val(t_game *game, char *str, char *line, int i);
bool			handle_str(t_game *game, char *str, char *line, int i);
bool			fillin_data(t_game *game, char *line);
t_list			*fillin_map(char *line, t_list *lst);
bool			done(t_game *game);
bool			help2(char *line, int fd, t_game *game);
t_game			*parsing(char *arg);
void			ft_free(t_game *game);
bool			parse_map(t_game *game);
void			destroy_all(t_game *game);

// pixel.c
void			color_convertor(t_game *game);
t_img			create_img(t_game *game, int height, int width);
void			my_put_pixel(t_img image, int x, int y, int color);
t_img			new_file_img(char *path, t_game *game);
unsigned int	get_pixel_img(t_img img, int x, int y);

// move.c
void			go_up(t_game *game);
void			go_down(t_game *game);
void			to_right(t_game *game);
void			to_left(t_game *game);
void			ft_key_hook(t_game *game);

// move2.c
int				wall_checker(t_game *game, int x, int y);
int				can_move(t_game *game, int x, int y);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);

// ray_cast.c
double			dgr_to_rad(double degrees);
double			dist_calc(t_game *game, double x, double y, double ray);
double			complete_line(t_game *game, double x, double y, double ray);
double			dda_line_drawing(t_game *game, double x, double y, double ray);
void			ray_cast(t_game *game, int x, int y, double ray);

// texture.c
void			detect_direction(t_game *game, int x, int y, double ray);
unsigned int	get_wall_color(t_game *game, int x, int y);
void			draw_textures(t_game *game, int x, double y, double wall_h);
void			vertical_line(t_game *game, int x, double dist);

// main.c
int				ft_exit(t_game *game);
int				render_3d(t_game *game);
void			init_image(t_game *game);
void			destroy_all(t_game *game);

#endif
