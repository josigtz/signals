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
	char *filename1 = argv[1];
	char *filename2 = argv[2];
	char *outputf = argv[3];
	int N;
	FILE *entrada = fopen(filename1,"rb");	
	FILE *entrada2 = fopen(filename2,"rb");	
	FILE *salida = fopen(outputf,"wb");
	struct HEADER h1, h2, header;
	char c;
	float aux, auxI, auxR, scala;
	scala = ((32767*32767)+(32767*32767));
 	int i;
 	short sample;
 	
	if ( entrada == NULL ) {
        perror("No se pudo abrir el archivo origen");
        exit(1);
    }
    if ( entrada2 == NULL ) {
        perror("No se pudo abrir el archivo origen");
        exit(1);
    }
    if ( salida == NULL ) {
        perror("No se pudo abrir el archivo destino");
        exit(1);
    }
    
    if ( fread(&h1, sizeof(h1), 1, entrada) < 1 ) {
        fprintf(stderr,"No se pudo leer la cabecera %s\n", salida);
        exit(1);
    } 
	if ( fread(&h2, sizeof(h2), 1, entrada2) < 1 ) {
        fprintf(stderr,"No se pudo leer la cabecera %s\n", salida);
        exit(1);
    }    
    
	if(h1.channels != h2.channels){
		printf("Distinto numero de canales");
		exit(0);
	}
	
	int nc = h1.channels;
    int ms1 = (8 * h1.bytes_in_data) / (h1.bits_per_sample*h1.channels);
	int ms2 = (8 * h2.bytes_in_data) / (h2.bits_per_sample*h2.channels);
	
	if(ms1>=ms2){
		N=ms1;
		fwrite(&h1,2,sizeof(h1)/2,salida); 
	} else if(ms1<ms2){
		N=ms2;
		fwrite(&h2,2,sizeof(h1)/2,salida); 
	}    
	
	if(nc==1){
		short aux1,aux2;
		for(i = 0 ; i < N ; i++){
			if( i%ms1==0 && i!=0) fseek(entrada,44,SEEK_SET);
			if( i%ms2==0 && i!=0) fseek(entrada2,44,SEEK_SET);			
		    fread(&aux1,2,1,entrada); 
		    fread(&aux2,2,1,entrada2);
			aux=(float)(aux1*aux2); 
			sample = (short)(aux/32767);
			fwrite(&sample,2,1,salida);
	    }
	}
	else{
		short a,b,c,d;
		for(i = 0 ; i < N ; i++){
			if( i%ms1==0 && i!=0) fseek(entrada,44,SEEK_SET);
			if( i%ms2==0 && i!=0) fseek(entrada2,44,SEEK_SET);
		    fread(&a,2,1,entrada); 
		    fread(&b,2,1,entrada); 
		    fread(&c,2,1,entrada2); 
		    fread(&d,2,1,entrada2); 
			auxR=(float)(a*c)-(float)(b*d);
			sample = (short)((auxR*32767)/scala);
			fwrite(&sample,2,1,salida);
			auxI=(float)(a*d)+(float)(b*c);
			sample = (short)((auxI*32767)/scala);
			fwrite(&sample,2,1,salida);
	    }
	}
	
	if(ms1>=ms2){
		fseek(entrada,44+N*2*nc,SEEK_SET);
		while(!feof(entrada)){
			fputc(fgetc(entrada),salida);
		}
	}
	else{
		fseek(entrada2,44+N*2*nc,SEEK_SET);
		while(!feof(entrada2)){
			fputc(fgetc(entrada2),salida);
		}
	}
	
    fclose(entrada);
    fclose(salida);
	return 0;
}
