/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:15:55 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/21 15:15:57 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL.h>
# include <SDL_mixer.h>
# include "libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

# define FDERROR(fd) if (fd < 0) ft_error(1)
# define MALLCHECKF(x) if (!x) ft_error(4)
# define MALLCHECK(x) if (!x) return (NULL)
# define WIDTH	1000
# define HEIGHT 800
# define MW 200
# define MH 200
# define TEXW 64
# define TEXTURES 6
# define SPR 0

typedef	struct	s_ray
{
	double	raydirx;
	double	raydiry;
	double	camx;
	double	camy;
	double	sdistx;
	double	sdisty;
	double	ddisty;
	double	ddistx;
	double	perwalld;
	double	wall;
	double	fwallx;
	double	fwally;
	double	distw;
	double	distp;
	double	distc;
	int		stepx;
	int		texn;
	int		texx;
	int		texy;
	int		flx;
	int		fly;
	int		stepy;
	int		hit;
	int		mapx;
	int		mapy;
	int		side;
	int		lineh;
	int		draws;
	int		drawe;
	int		*color;
}				t_ray;

typedef	struct	s_event
{
	int		move_up;
	int		move_down;
	int		rot_rigth;
	int		rot_left;
	int		shoot_event;
}				t_event;

typedef	struct	s_wolf
{
	t_event		eventcall;
	int			wid;
	double		speed;
	int			len;
	double		posx;
	double		posy;
	double		dirx;
	double		oldirx;
	double		diry;
	double		planex;
	double		olplanex;
	double		planey;
	double		time;
	double		oldtime;
	double		frtime;
	double		movspeed;
	double		rotspeed;
	char		**map;
	int			run;
	int			gun_num;
	Mix_Music	*music;
	Mix_Chunk	*shoot;
	SDL_Window	*win;
	SDL_Surface	*surface;
	SDL_Surface	*vimap;
	SDL_Surface	*texture[TEXTURES];
	SDL_Surface	*gun[4];
	SDL_Rect	rectmap;
	t_ray		ray;
}				t_wolf;

typedef	struct	s_line
{
	char			*content;
	struct s_line	*next;
}				t_line;

void			ft_error(int i);
char			**ft_read_file(char *file, t_wolf *wolf);
t_line			*ft_lnewline(char *content);
void			ft_raycast(t_wolf *wolf);
void			ft_valid_len(t_line *list, t_wolf *wolf, int count);
void			ft_lddline(t_line **list, char *content);
void			ft_ldel(t_line **list);
void			ft_sdl_init(t_wolf *wolf);
void			ft_sdl_loop(t_wolf *wolf);
void			ft_sdl_quit(SDL_Event event, int *run);
void			ft_sdl_move(t_wolf *wolf);
void			ft_put_pixel(t_wolf *wolf, int x, int y, int pixel);
void			ft_draw_line(t_ray *ray, int y, t_wolf *wolf);
void			ft_fps(t_wolf *wolf);
void			ft_move(t_wolf *wolf);
void			ft_load_texture(t_wolf *wolf);
void			ft_val_border(char	**map, t_wolf *wolf);
void			ft_load_sound(t_wolf *wolf);
void			ft_ray_rot(t_ray *ray);
void			ft_draw_gun(t_wolf *wolf);
void			ft_free_ress(t_wolf *wolf);
void			ft_cr_vimap(t_wolf *wolf);
void			ft_sdl_shoot(t_wolf *wolf);

#endif
