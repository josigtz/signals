#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <stdint.h> 

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

int is_big_endian(void);

void printheader(struct HEADER);

int main(int argc, char *argv[]) {

    char *filename = argv[1] ;
	char *filename2 = argv[2] ;
	  
    FILE *file = fopen(filename,"rb");

    if ( file == NULL ) {
        perror("No se pudo abrir el archivo origen");
        exit(1);
    }
    
    FILE *fileo = fopen(filename2, "wb");

    if ( fileo == NULL ) {
        perror("No se pudo abrir el archivo destino");
        exit(1);
    }
    
    
    struct HEADER header;
    
    // read header
    if ( fread(&header, sizeof(header), 1, file) < 1 ) {
        fprintf(stderr,"No se pudo leer la cabecera %s\n", filename);
        exit(1);
    }

    printf("Cabecera del archivo\n");
    printheader(header);
    fwrite(&header, sizeof(header), 1, fileo);

    char c;
    int samples_readed = 0, num_samples;
    num_samples = (8 * header.bytes_in_data) / (header.bits_per_sample);
    
    // read data
    int16_t sample_in = 0, sample_out = 0, sample_anterior = 0;
	long long int data_in = 0, data_out = 0;
	int total=0;
    while( fread(&sample_in, sizeof(sample_in), 1, file) && total <= num_samples ) {
        total++;
		sample_out = sample_in / 2;
		fwrite(&sample_out, sizeof(sample_out), 1, fileo);
    }
    
	while( fread(&c, sizeof(c), 1, file) ) {
        fwrite(&c, sizeof(c), 1, fileo);
    }
    
    fclose(file);
    fclose(fileo);
    exit(0);
}

int is_big_endian(void){
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01000000};
    return bint.c[0]==1;
}

void printheader(struct HEADER header){
printf("ID: %s\n", header.id);
    printf("ChunkSize: %d\n", header.totallength);
    printf("Channels: %d\n", header.channels);
    printf("Frequency: %d\n", header.frequency);
    printf("Byte rate: %d\n", header.bytes_per_second);
    printf("Byte per capture: %d\n", header.bytes_by_capture);
    printf("Bits per sample: %d\n", header.bits_per_sample);
    printf("Bits in data: %d\n", header.bytes_in_data);
}
