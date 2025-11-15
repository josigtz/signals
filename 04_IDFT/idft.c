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
	struct HEADER h1,h2;
	
	if ( entrada == NULL ) {
        perror("No se pudo abrir el archivo origen");
        exit(1);
    }
    
    if ( salida == NULL ) {
        perror("No se pudo abrir el archivo destino");
        exit(1);
    }
    
    if ( fread(&h1, sizeof(h1), 1, entrada) < 1 ) {
        fprintf(stderr,"No se pudo leer la cabecera %s\n", filename);
        exit(1);
    }    
    
    h2=h1;
	h2.bytes_in_data=h1.bytes_in_data/2;
	h2.totallength=110+(h1.bytes_in_data/2);
	h2.channels=1;
	h2.bytes_by_capture=h2.bits_per_sample/8;
	h2.bytes_per_second=h2.frequency*h2.bits_per_sample/8;
    
    char c;
    int num_samples = (8 * h1.bytes_in_data) / (h1.bits_per_sample*2);
	
    fwrite(&h2,sizeof(h2), 1, salida);
 
	int n, k, i;
	short sample_outl;
	
	short sample, samplesR[num_samples], samplesI[num_samples];
    float arg;
	i = 0;
	
	for(i=0;i<num_samples;i++){
		fread(&sample, sizeof(sample), 1, entrada); 
		samplesR[i] = sample;
		fread(&sample, sizeof(sample), 1, entrada); 
		samplesI[i] = sample;
	}	
	
	for (n = 0 ; n < num_samples ; n++){
		float a=0;
		for (k = 0; k < num_samples ; k++){
			arg = (float)(2*M_PI*k*n)/(float)num_samples;
			a += (float)((float)(cos(arg)*samplesR[k]) - (float)(sin(arg)*samplesI[k]));
		}
		sample_outl = (short) (a);		
		fwrite(&sample_outl,sizeof(short),1,salida);			
	}	
   
	while( fread(&c, sizeof(c), 1, entrada) ) {
        fwrite(&c, sizeof(c), 1, salida);
    }
    
    fclose(entrada);
    fclose(salida);
	
	return 0;
}
