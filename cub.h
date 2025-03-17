#ifndef CUB_H
#define CUB_H

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
# define BLACK 0x00000000
# define WHITE 0xffffff
# define RED 0xff0000
# define YELLOW 0xfbff00
# define GREEN 0x14f70d
# define CEILLING 0x0010b5
# define WALL_COLOR 0x00ffec
# define wall_COLOR 0xe20df7
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


t_img   create_img(t_game *game, int height, int width);
void    my_put_pixel(t_img image, int x, int y, int color);
void    draw_square(t_img image, int x, int y, int color);
void    draw_player(t_img image, int x, int y, int color);
void    fill_map(t_img image, int ceilling, int floor);
t_img	new_file_img(char *path, t_game *game);
unsigned int	get_pixel_img(t_img img, int x, int y);
#endif





// https://www.youtube.com/shorts/k07oBHCrJzE