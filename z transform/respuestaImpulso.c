#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int i;
	FILE *debug = fopen("debug.txt","wb");
	float aux;
	for (i = -100 ; i < 100 ; i++){
		aux = 0.000087362*pow(0.402864,(i-1))*pow(-2.348058,(i-1));
		fprintf(debug,"a %d %f \r\n",i,aux);
	}
	return 0;
}
