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
# define SPEED 5
# define PI 3.14159265358979323846
# define TILE_SIZE 50
# define PLAYER_COLOR 0x00000000

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
	char	pv;
	int		px;
	int		py;
	double	pdx;
	double	pdy;
	double	pa;
}			t_game;

// parsing
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

#endif