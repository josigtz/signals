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

int main(int argc, char *argv[]){
	char *filename = argv[1];
	char *outputf = argv[2];
	
	FILE *entrada = fopen(filename,"rb");	
	FILE *salida = fopen(outputf,"wb");
	
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
    
    char c;
    int num_samples = (8 * header.bytes_in_data) / (header.bits_per_sample);
	header.totallength = 2 * header.bytes_in_data + 110;
	header.channels = 2;
	header.bytes_per_second = header.frequency * header.bits_per_sample * header.channels / 8;
	header.bytes_by_capture = header.channels * header.bits_per_sample / 8;
	header.bytes_in_data = header.bytes_in_data*2;
	
    fwrite(&header, sizeof(header), 1, salida);
 
	int n, k, samples_readed;
	short sample_outl, sample_outr;
	
	short sample, sample_in, samples[num_samples];
    float arg;
	
	while( fread(&sample, sizeof(sample), 1, entrada) ) {   
        samples[samples_readed++] = sample;
		if(samples_readed == num_samples)
           break;
    }
	
	
	for (k = 0 ; k < num_samples ; k++){
		float a=0, b=0;
		for (n = 0; n < num_samples ; n++){
			arg = (2*M_PI*k*n)/num_samples;
			sample_in = samples[n];
			a += (float)(sample_in * cos(arg));
			b -= (float)(sample_in * sin(arg));
		}
		
		sample_outl = (short) (a/num_samples);
		sample_outr = (short) (b/num_samples);
		
		fwrite(&sample_outl,sizeof(short),1,salida);
		fwrite(&sample_outr,sizeof(short),1,salida);
			
	}	
   
	n = 0;
	while( fread(&c, sizeof(c), 1, entrada) ) {
        fwrite(&c, sizeof(c), 1, salida);
    }
    
    fclose(entrada);
    fclose(salida);
	
	return 0;
}
