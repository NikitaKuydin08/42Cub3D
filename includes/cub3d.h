/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 09:52:39 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/05 23:11:04 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/time.h>

// VARIABLES //
# define WIN_HEIGHT 800
# define WIN_WIDTH 800
# define FOV 60
# define PI 3.14159265359

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define FORWARD 0
# define BACKWARD 1
# define LEFT 2
# define RIGHT 3

# define MOVE_SPEED 1
# define ROT_RIGHT 0.25
# define ROT_LEFT -0.25

// ERROR MESSAGES //
# define USAGE "Usage: ./cub3d <path/to/map.cub>"
# define FILE_NOT_EXIST "File doesn't exist"
# define FILE_NOT_REGULAR "File is not a regular file"
# define WRONG_FILE_EXT "FIle has wrong extension, not .cub"
# define WRONG_TEX_EXT "Not a .png file"
# define OPEN_FILE_ERR "Couldn't open the file, wrong permissions"
# define FILE_IS_EMPTY "File is empty"
# define ERR_MALLOC "Memory allocation error"
// INSIDE OF FILE ERROR //
# define MAP_NOT_LAST "Some content after map in the file"
# define MISSING_MAP "Map doesn't exist in the file"
# define MISSING_TEXTURE "At least one texture or rgb colours is missing"
# define UNKNOWN_TEX "Unknown texture identifier value"
# define DUPLICATE_TEX "Duplicate texture identifier"
# define BAD_TEX_VALUE "Bad texture value (missing, malloc fail, or \
trailing garbage)"
# define EXPECTED_WHITESPACE "Header identifier missing whitespace separator"
# define MISSED_TEX "At leaast one texture is missing"
# define INVALID_COUNT_RGB "Invalid number of rgb values, it must be exactly 3"
# define CONTAINS_OTHER_CHAR "At least one rgb colour contains non-digit \
char (including signs)"
# define OUT_OF_RANGE "At least one of R,G,B colours is out of range [0, 255]"
// MAPS_ERRORS //
# define WALL_HOLE_WEST "Map has a hole on the west"
# define WALL_HOLE_NORTH "Map has a hole on the north"
# define WALL_HOLE_SOUTH "Map has a hole on the south"
# define WALL_HOLE_EAST "Map has a hole on the east"
# define MAP_TOO_SMALL "Map is smaller than 3 lines"
# define WRONG_CHAR "Map composed of char(s) different from [0,1,N,S,E,W]"
# define MULTIPLE_PLAYER "Player's position appears in the map more than once"
# define NO_PLAYER "Map doesn't have player. Expected (N, S, E, or W)"
# define TRAPPED_PLAYER "Map doesn't have cell (0) next to player's position"
# define ERR_TAB "Tab character is not allowed in map, only spaces"
// WIN_ERRORS //
# define NOT_INIT "data: Error: mlx: Could not initialize mlx"
# define NOT_INIT_IMG_BUF "data: Error: mlx: Could not allocate a new \
			image buffer"
# define CANT_CREATE_INSTANCE "data: Error: mlx: Could not draw a new image"


// STRUCTURES //
typedef struct s_line
{
	int		x;
	int		y;
	double	step;
	double	pos;

}	t_line;

typedef struct s_texrgbinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;
	uint32_t		hex_floor;
	uint32_t		hex_ceiling;
	mlx_texture_t	*tex[4];
	int				index;
	t_line			line;
}	t_texrgbinfo;

typedef struct s_ray
{
	double	camera_x;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	distwall;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	pos_on_wall;
}	t_ray;

typedef struct s_player
{
	char	orientation;
	int		x;
	int		y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	int				win_height;
	int				win_width;

	char			**file;
	char			*path;
	int				fd;
	int				line_count;

	char			**map;
	int				map_idx;
	int				map_line;
	bool			map_started;
	int				row_count;
	int				*row_lengths;

	bool			needs_redraw;
	int				**texture_pixels;
	t_player		player;
	t_texrgbinfo	texrgbinfo;
	t_ray			ray;
	uint32_t		color;
	bool			terminate;
	bool			delete;
	bool			close;
}	t_data;

void	header(void);

void	init_data(t_data *data);
void	init_raycasting_dda(t_ray *ray, int x, t_player *player);
void	init_ray(t_ray *ray);

// CHECK_MAP_CLOSURE //
int		check_closure(t_data *data, char **map);

// CHECK_MAP //
int		check_map(t_data *data);

// CHECK_TEXTURES //
int		check_textures(t_texrgbinfo *texinfo);
// EXTRACT_DATA //
int		extract_data_from_file(t_data *data);

// HELPERS_TO_EXTRACT //
int		finalize(t_data *data);
int		is_rgb_or_tex(char *line);
int		rest_is_blank(char **file, int idx);
int		is_blank_line(char *line);
char	**recognise_texture(t_texrgbinfo *info, char *line, int *i);

// MAP_COPY //
int		map_copy_into_file(char *arg, t_data *data);

// PERMISSION //
int		check_file(char *arg, bool cub);

//				RENDERING - RAY CASTING				//
void	prep_game(t_data *data);
void	draw_game(t_data *data, t_player *player);
void	raycasting(t_player *player, t_data *data);

// CONTROLS //
void	key_hook(mlx_key_data_t keydata, void *param);
void	loop_hook(void *param);

// UTILS //
int		print_err_msg(char *msg);
void	ft_error(t_data *data, int exit_code, char *msg);
int		free_data(t_data *data);
void	free_tab(void **tab);

// PREPARE GAME //
void	setup_jump_algo(t_ray *ray, t_player *player);

// MOVING AND KEYS IMPLEMENTATION //
void	loop_hook(void *param);
void	key_hook(mlx_key_data_t keydata, void *param);

// UTILS //
int		check_limit_dda(t_data *data, int x, int y);
void	recognise_side_tex(t_texrgbinfo *texinfo, t_ray *ray);
void	free_tab(void **tab);

#endif