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
# include "./mlx_linux/minilibx-linux/mlx.h"

# define BUFFER_SIZE 42
# define WIND_W 1280
# define WIND_H 720

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     *floor;
    int     *ceiling;
	char	*save;
	int		p_x;
	int		p_y;
}               t_game;

size_t	ftstrlen(const char *s);
char	*ftstrdup(const char *s1);
char	*my_strjoin(char *s1, char const *s2);
char	*get_next_line(int fd, bool flag);
t_game  *parsing(char *arg);
void    ft_free(t_game *game);
bool	parse_map(t_game *game);

# endif 