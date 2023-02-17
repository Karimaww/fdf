#include "../include/line.h"

void drawline(t_data img, int x0, int y0, int x1, int y1)  
{	
	int dx, dy, p, x, y; 
	dx=x1-x0;  
	dy=y1-y0;  
	x=x0;  
	y=y0;  
	p=2*dy-dx;  
	while(x<x1)  
	{  
		if(p>=0)  
		{  
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
			y=y+1;  
			p=p+2*dy-2*dx;  
		}  
		else  
		{  
			putpixel(x,y,7);  
			p=p+2*dy;}  
			x=x+1;  
		}  
} 

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_mlx_me()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 800, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}