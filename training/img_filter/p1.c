#include <stdio.h>

int main(int argv, char **argc) {
	if (argv != 3) {
		printf("USAGE: ./exe file.yuv colour_code(eg:-ff0000)\n");
		return 0;
	}
	unsigned char y[HEIGHT][WIDTH];
	unsigned char u[HEIGHT/2][WIDTH/2];
	unsigned char v[HEIGHT/2][WIDTH/2];
	int colour = strtol(argc[2], NULL, 16);
	unsigned char r = (colour >> 16) & 0xFF;
	unsigned char g = (colour >> 8) & 0xFF;
	unsigned char b = colour & 0xFF;
	unsigned char y_colour = (0.299*r + 0.587*g + 0.114*b);
	unsigned char u_colour = (-0.14713*r - 0.28886*g + 0.436*b) + 128;
	unsigned char v_colour = (0.615*r - 0.51499*g - 0.10001*b) + 128;
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
				YUV420 Solid Colour Image Generator

				y[i][j] = y_colour;
	for (int i = 0; i < HEIGHT/2; i++)
		for (int j = 0; j < WIDTH/2; j++) {
			u[i][j] = u_colour;
			v[i][j] = v_colour;
		}
	FILE *fd = fopen(argc[1], "wb");
	fwrite(y, 1, HEIGHT * WIDTH, fd);
	fwrite(u, 1, (WIDTH/2) * (HEIGHT/2), fd);
	fwrite(v, 1, (WIDTH/2) * (HEIGHT/2), fd);
	fclose(fd);
	return 0;
}
