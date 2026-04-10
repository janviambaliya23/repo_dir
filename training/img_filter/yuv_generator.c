#include <stdio.h>

int main()
{
    int width = 1920;
    int height = 1080;

    int Y_size = width * height;
    int UV_size = (width * height) / 4;

    unsigned char Y[Y_size];
    unsigned char U[UV_size];
    unsigned char V[UV_size];

    FILE *fp;

    // Fill Y with brightness
    for(int i = 0; i < Y_size; i++)
        Y[i] = 128;

    // Fill U
    for(int i = 0; i < UV_size; i++)
        U[i] = 64;

    // Fill V
    for(int i = 0; i < UV_size; i++)
        V[i] = 192;

    fp = fopen("output.yuv","wb");

    fwrite(Y,1,Y_size,fp);
    fwrite(U,1,UV_size,fp);
    fwrite(V,1,UV_size,fp);

    fclose(fp);

    printf("YUV file generated\n");

    return 0;
}
