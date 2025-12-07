#include "fractol.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * ESC or i press the x🔴 in the window
 * there won't be leaks!
 * int (*f)(void *param)
*/
int	handle_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection,
					fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection,
						fractal->mlx_window);
	/* Do not free mlx_connection directly; MLX manages its own resources. */
	exit(EXIT_SUCCESS);
}


/*
 * Keypress prototype
 * int (*f)(int keycode, void *param)
*/
int	handle_key(int keysym, t_fractal *fractal)
{
	/* Accept both X11 keysyms and macOS MLX keycodes */
	if (keysym == XK_Escape || keysym == 53)
		handle_close(fractal);
	if (keysym == XK_Left || keysym == 123)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right || keysym == 124)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up || keysym == 126)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Down || keysym == 125)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_plus || keysym == 24)
		fractal->iterations_defintion += 10;
	else if (keysym == XK_minus || keysym == 27)
		fractal->iterations_defintion -= 10;

	/* refresh the image */
	fractol_render(fractal);
	return 0;
}



/*
 * int (*f)(int button, int x, int y, void *param)
*/
int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	//Zoom in
	if (button == Button5)
	{
		fractal->zoom *= 0.95;
	}
	//Zoom out
	else if (button == Button4)
	{
		fractal->zoom *= 1.05;
	}
	/* refresh */
	fractol_render(fractal);
	return 0;
}


/*
 * TRACK the mouse
 * to change julia dynamically
 * int (*f)(int x, int y, void *param)
*/
int	handle_julia_motion(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = (ft_map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (ft_map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
		fractol_render(fractal);
	}
	return 0;
}

