#ifndef CUB_H
#define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "lib/mlx.h"

#define BUFFER_SIZE 42

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		win_h;
	int		win_w;
	char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     *floor;
    int     *ceiling;
	char	*save;
	int		p_x;
	int		p_y;
	// float	x;
	// float	y;
	// float	dir;
	// float	plane;
	// float	move_speed;
	// float	rot_speed;
	char	**map;
}               t_game;

size_t	ftstrlen(const char *s);
char	*ftstrdup(const char *s1);
char	*my_strjoin(char *s1, char const *s2);
char	*get_next_line(int fd, bool flag);
t_game  *parsing(char *arg);
void    ft_free(t_game *game);
bool	parse_map(t_game *game);

# endif 