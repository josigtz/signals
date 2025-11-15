#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265

float magnitud(float a, float b);
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

	FILE *entrada = fopen(filename,"rb");
	
	if ( entrada == NULL ) {
        perror("No se pudo abrir el archivo origen");
        exit(1);
    }
    
	struct HEADER header;
	
    if ( fread(&header, sizeof(header), 1, entrada) < 1 ) {
        fprintf(stderr,"No se pudo leer la cabecera %s\n", filename);
        exit(1);
    }    
    
    int num_samples = (8 * header.bytes_in_data) / (header.bits_per_sample);
 
	int n, k, samples_readed;
	
	short sample, sample_in, samples[num_samples];
    float arg;
	
	while( fread(&sample, sizeof(sample), 1, entrada) ) {   
        samples[samples_readed++] = sample;
		if(samples_readed == num_samples)
           break;
    }
    
    int frec[8] = {697,770,852,941,1209,1336,1477,1633};
	float dmtf[8] = {0,0,0,0,0,0,0,0};
	int s = header.frequency/num_samples;
	
	for(k = 0 ; k < 8; k++){
		float a = 0, b = 0;
		for (n = 0; n < num_samples ; n++){
			arg = (2*M_PI*((frec[k]/s)+0)*n)/num_samples;
			sample_in = samples[n];
			a += (float)(sample_in * cos(arg));
			b -= (float)(sample_in * sin(arg));
		}
		dmtf[k]=magnitud(a/num_samples,b/num_samples);		
	}
	
	if(dmtf[0]!=0 && dmtf[4]!=0)
		printf("1");
	if(dmtf[0]!=0 && dmtf[5]!=0)
		printf("2");
	if(dmtf[0]!=0 && dmtf[6]!=0)
		printf("3");
	if(dmtf[0]!=0 && dmtf[7]!=0)
		printf("A");
	if(dmtf[1]!=0 && dmtf[4]!=0)
		printf("4");
	if(dmtf[1]!=0 && dmtf[5]!=0)
		printf("5");
	if(dmtf[1]!=0 && dmtf[6]!=0)
		printf("6");
	if(dmtf[1]!=0 && dmtf[7]!=0)
		printf("B");
	if(dmtf[2]!=0 && dmtf[4]!=0)
		printf("7");
	if(dmtf[2]!=0 && dmtf[5]!=0)
		printf("8");
	if(dmtf[2]!=0 && dmtf[6]!=0)
		printf("9");
	if(dmtf[2]!=0 && dmtf[7]!=0)
		printf("C");
	if(dmtf[3]!=0 && dmtf[4]!=0)
		printf("*");	
	if(dmtf[3]!=0 && dmtf[5]!=0)
		printf("0");
	if(dmtf[3]!=0 && dmtf[6]!=0)
		printf("#");
	if(dmtf[3]!=0 && dmtf[7]!=0)
	    printf("D");	

    fclose(entrada);
	
	return 0;
}
float magnitud(float a, float b){
	float m, aux;
	aux = (a*a) + (b*b);
	m = sqrt(aux);
	if(m<900)
		return 0;
	else
		return m;
}
