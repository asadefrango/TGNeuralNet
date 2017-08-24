#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "set_log.h"
#include "fann/floatfann.h"
/*
struct fann * create_neural_net( const unsigned int* layers,
		unsigned int size_layer,
		unsigned int shortcut,
		unsigned int * layer_activation_function ){
	size_t count_layer;
	struct fann * ann;

	if(shortcut)
		ann = fann_create_shortcut_array(size_layer,layers);
	else
		ann = fann_create_standard_array(size_layer,layers);

	for(count_layer=1;count_layer<size_layer;count_layer++)
		fann_set_activation_function_layer( ann,layer_activation_function[count_layer],count_layer);

	set_log("rede criada\n");

	//free(log_men);
	return ann;

}
*/
int main(int argc, char **argv){

	bool isCaseInsensitive = false;
	int opt;
	
	char *entrada=NULL;
	char *saida=NULL;

	while ((opt = getopt(argc, argv, "e:s:")) != -1) {
		switch (opt) {
		
			case 'e':
				saida=optarg;
				printf("Nome do arquivo de saida: %s\n", saida);
				break;
		
			case 's':
				entrada=optarg;
				printf("Nome do arquivo de entrada: %s\n", entrada);
				break;
		
			default:
				fprintf(stderr, "Usage: %s [-es] [file...]\n", argv[0]);
				exit(EXIT_FAILURE);
		}

	}

		
	


	
}
