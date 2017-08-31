#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "set_log.h"
#include "api/API_net.h"

int main(int argc, char **argv){
	set_log("\n\nGEN_TRAIN");
	bool isCaseInsensitive = false;
	int opt,i;
	FILE *fsaida;
	char *entrada=NULL;
	char *saida=NULL;
	char tmp[100];
	float *data;
	int numero_layers,*layers,atalhos,*func_ativ;
	while ((opt = getopt(argc, argv, "e:s:")) != -1) {
		switch (opt) {

			case 's':
				saida=optarg;
				printf("Nome do arquivo de saida: %s\n", saida);
				break;

			case 'e':
				entrada=optarg;
				printf("Nome do arquivo de entrada: %s\n", entrada);
				break;

			default:
				fprintf(stderr, "%s \nparametros:\n-e arquivo de entrada\n-s arquivo de saida\n", argv[0]);
				exit(EXIT_FAILURE);
		}

	}
	if(opterr){
		fprintf(stderr, "%s \nparametros:\n-e arquivo de entrada\n-s arquivo de saida\n", argv[0]);
		exit(EXIT_FAILURE);

	}
	sprintf(tmp,"\narquivo de entrada %s",entrada);
	set_log(tmp);

	sprintf(tmp,"\narquivo de saida %s",saida);
	set_log(tmp);


	sprintf(tmp,"\nlendo arquivo de entrada...");
	set_log(tmp);

	readFile(entrada,data);

	

	for(i = 1 ; i < numero_layers; i++){
		layers = (int*)realloc(layers,i*sizeof(int));
		fscanf(fentrada,"%d",&layers[i]);
		sprintf(tmp,"\nnumero de neuronios no layer %d %d",i,layers[i]);
		set_log(tmp);
	}
	fscanf(fentrada,"%d",&atalhos); //atalhos

	func_ativ = malloc(sizeof(int));
	fscanf(fentrada,"%d",&func_ativ[0]);
	sprintf(tmp,"\n funcao ativacao layer 1 %d",layers[0]);
	set_log(tmp);
	for(i = 1; i < numero_layers; i++){
		func_ativ = realloc(func_ativ,i*sizeof(int));
		fscanf(fentrada,"%d",&func_ativ[i]);
		sprintf(tmp,"\nfuncao ativacao layer %d %d",i,layers[i]);
		set_log(tmp);
	}

	save_neural_net(create_neural_net(layers, numero_layers, atalhos, func_ativ ),saida);


	sprintf(tmp,"\nFIM GEN_TRAIN\n ");
	set_log(tmp);
	fclose(fentrada);
	free(entrada);
	entrada = NULL;
	free(saida);
	saida = NULL;
	free(layers);
	layers = NULL;

}
