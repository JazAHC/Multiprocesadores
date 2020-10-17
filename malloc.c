#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 60
#define PIXELS 927361
//927361

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("sample.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("malloc.bmp","wb");    //Imagen transformada
    double t1, t2, time;

    unsigned char r, g, b;               //Pixel
    
    unsigned char *in, *out;
    in = (unsigned char*)malloc(PIXELS*3*sizeof(unsigned char));
    out = (unsigned char*)malloc(PIXELS*3*sizeof(unsigned char));
    int j = 0;

    for(int i=0; i<54; i++) fputc(fgetc(image), outputImage);   //Copia cabecera a nueva imagen
    
    omp_set_num_threads(NUM_THREADS);
    
    while(!feof(image)){
        *(in + j) = fgetc(image);
        j++;
    }
    
    t1 = omp_get_wtime();
    #pragma omp parallel
    {
           #pragma omp for ordered
           for(int i =0; i < PIXELS*3; i+=3){
               r = *(in + i);
               g = *(in + i + 1);
               b = *(in + i + 2);
               unsigned char pixel = 0.21*r+0.72*g+0.07*b;
               #pragma omp ordered
               {
                   *(out + i) = pixel;
                   *(out + i + 1) = pixel;
                   *(out + i + 2) = pixel;
               }
           }
           
    }
    t2 = omp_get_wtime();
    time = t2 - t1;
    printf("Time = %f\n",time);
    for(int i = 0; i < PIXELS*3; i++){
        fputc(*(out + i), outputImage);
    }
    free(in);
    free(out);
    fclose(image);
    fclose(outputImage);
    return 0;
}
