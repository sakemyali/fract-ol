#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> //TODO debugging
# include <stdlib.h> //malloc free
# include <unistd.h> // write
# include <math.h>
# ifdef __linux__
#  include <X11/X.h>
#  include <X11/keysym.h>
# endif
# include "minilibx_opengl_20191021/mlx.h"

# ifndef __linux__
/* Minimal event/key/button definitions for non-Linux builds (macOS fallback)
 * These are only used to allow compilation and basic key comparisons. */
#  ifndef KeyPress
#   define KeyPress 2
#  endif
#  ifndef ButtonPress
#   define ButtonPress 4
#  endif
#  ifndef DestroyNotify
#   define DestroyNotify 17
#  endif
#  ifndef MotionNotify
#   define MotionNotify 6
#  endif
#  ifndef KeyPressMask
#   define KeyPressMask (1L<<0)
#  endif
#  ifndef ButtonPressMask
#   define ButtonPressMask (1L<<2)
#  endif
#  ifndef StructureNotifyMask
#   define StructureNotifyMask (1L<<17)
#  endif
#  ifndef PointerMotionMask
#   define PointerMotionMask (1L<<6)
#  endif

/* Keysyms used by the app */
#  ifndef XK_Escape
#   define XK_Escape 0xFF1B
#  endif
#  ifndef XK_Left
#   define XK_Left 0xFF51
#  endif
#  ifndef XK_Right
#   define XK_Right 0xFF53
#  endif
#  ifndef XK_Up
#   define XK_Up 0xFF52
#  endif
#  ifndef XK_Down
#   define XK_Down 0xFF54
#  endif
#  ifndef XK_plus
#   define XK_plus 0x002B
#  endif
#  ifndef XK_minus
#   define XK_minus 0x002D
#  endif

/* Mouse wheel buttons */
#  ifndef Button4
#   define Button4 4
#  endif
#  ifndef Button5
#   define Button5 5
#  endif
# endif


#define ERROR_MESSAGE "Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia <value_1> <value_2>\"\n"

/*
 * We use a square to 
 * keep the rendering math simple
*/
#define WIDTH	800
#define	HEIGHT	800

/*
 * COLORS
*/
#define BLACK       0x000000  // RGB(0, 0, 0)
#define WHITE       0xFFFFFF  // RGB(255, 255, 255)
#define RED         0xFF0000  // RGB(255, 0, 0)
#define GREEN       0x00FF00  // RGB(0, 255, 0)
#define BLUE        0x0000FF  // RGB(0, 0, 255)

// Psychedelic colors
#define MAGENTA_BURST   0xFF00FF  // A vibrant magenta
#define LIME_SHOCK      0xCCFF00  // A blinding lime
#define NEON_ORANGE     0xFF6600  // A blazing neon orange
#define PSYCHEDELIC_PURPLE 0x660066  // A deep purple
#define AQUA_DREAM      0x33CCCC  // A bright turquoise
#define HOT_PINK        0xFF66B2  // As the name suggests!
#define ELECTRIC_BLUE   0x0066FF  // A radiant blue
#define LAVA_RED        0xFF3300  // A bright, molten red





/*
 * COMPLEX value
*/
typedef struct	s_complex
{
	//		real
	double	x;
	//		i
	double	y;
}				t_complex;



/*
 * IMAGE
 * This is basically a pixels buffer
 * values from mlx_get_data_addr()
*/
typedef struct	s_img
{
	void	*img_ptr; //pointer to image struct
	char	*pixels_ptr; //points to the actual pixels
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;


/*
 * FRACTAL ID
 * ~ MLX stuff
 * ~ Image 
 * ~ Hooks values
*/
typedef struct	s_fractal
{
	char	*name;
	//MLX
	void	*mlx_connection; // mlx_init()
	void	*mlx_window; 	 // mlx_new_window()
	//Image
	t_img	img;

	//Hooks member variables //TODO
	double	escape_value; // hypotenuse
	int		iterations_defintion; // value tight with the image quality and rendering speed
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;










/*
 * PROTOTYPES
 * They are basically IOUs to the compiler
*/
//*** strings utils ***
//*** strings utils ***
int		ft_strncmp(char *s1, char *s2, int n);
void	ft_putstr_fd(char *s, int fd);
double	ft_atod(char *s);

//*** init ***
void	fractol_init(t_fractal *fractal);

//*** render ***
void	fractol_render(t_fractal *fractal);

//*** math ***
double	ft_map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex	complex_add(t_complex z1, t_complex z2);
t_complex	complex_square(t_complex z);

//*** hooks_events ***
int		handle_key(int keysym, t_fractal *fractal);

//*** clean_up ***
int		handle_close(t_fractal *fractal);
int		handle_mouse(int button, int x, int y, t_fractal *fractal);
int		handle_julia_motion(int x, int y, t_fractal *fractal);

#endif
