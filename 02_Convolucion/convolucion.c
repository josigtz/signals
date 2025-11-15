#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265

struct HEADER{
    char    id[4];          
    int32_t totallength;    
    char    wavefmt[8];     
    int32_t format;         
    int16_t pcm;            
    int16_t channels;       
    int32_t frequency;       
    int32_t bytes_per_second;
    int16_t bytes_by_capture;
    int16_t bits_per_sample;
    char    data[4];        
    int32_t bytes_in_data;
};
    
float * generar_impulso (int TAM_ARREGLO);

int main(int argc, char *argv[]){
	float * h = (float *) malloc (sizeof (float) * 100);
	char *filename = argv[1];
	char *filename2 = argv[2];

	FILE *entrada = fopen(filename,"rb");	
	FILE *salida = fopen(filename2,"wb");
	
	if ( entrada == NULL ) {
        perror("No se pudo abrir el archivo origen");
        exit(1);
    }
    
    if ( salida == NULL ) {
        perror("No se pudo abrir el archivo destino");
        exit(1);
    }
    
	struct HEADER header;
	
    if ( fread(&header, sizeof(header), 1, entrada) < 1 ) {
        fprintf(stderr,"No se pudo leer la cabecera %s\n", filename);
        exit(1);
    }    
    
    h = generar_impulso (100);
    
    char c;
    int num_samples = (8 * header.bytes_in_data) / (header.bits_per_sample);

    fwrite(&header, sizeof(header), 1, salida);
    
	int16_t aux[100] = {0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0};
			  
	int i = 0;
	float max = 0;
	
    while(i < num_samples){
    	int k;
    	short sample_in = 0;
		float sumaAux = 0;
    	
		for ( k = 100 ; k > 0 ; k--){
			 aux[k] = aux[k-1];
		}
		
		fread(&sample_in,sizeof(short),1,entrada);
		aux[0]=sample_in;
		for ( k = 0 ; k < 100 ; k++){
			 sumaAux = sumaAux +  (aux[k] * h[k]);
		}
		
		int16_t sample_out = (int) ((float)sumaAux*0.247951);
		
		fwrite(&sample_out,sizeof(int16_t),1,salida);
		
		i++;
	}
	
	i = 0;
	while( fread(&c, sizeof(c), 1, entrada) ) {
        fwrite(&c, sizeof(c), 1, salida);
    }
    fclose(entrada);
    fclose(salida);
	
	return 0;
}

float * generar_impulso (int TAM_ARREGLO)
{
	int fc = 2000;
	int fs = 44100;
	int i;
	float * impulso = (float *) malloc (sizeof (float) * 100);
	for (i = 0; i < TAM_ARREGLO; i ++)
	{
		impulso [i] = (exp ((-2 * M_PI * fc * i) / fs));
	}
	return impulso;
}

