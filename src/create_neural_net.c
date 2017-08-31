#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "set_log.h"
#include "api/API_net.h"
int main(int argc, char **argv){
	set_log("\n\nCREATE");
	bool isCaseInsensitive = false;
	int opt,i;
	unsigned int errS=0,errE=0 ;
	FILE *fentrada;
	char *entrada=NULL;
	char *saida=NULL;
	char tmp[100];
	int numero_layers,*layers,atalhos,*func_ativ;
	if( argc <= 1) {
		fprintf(stderr, "\nparametros:\n-e arquivo de entrada\n-s arquivo de saida\n");
		exit(EXIT_FAILURE);
	}
	while ((opt = getopt(argc, argv, "e:s:")) != -1) {
		switch (opt) {

			case 's':
				saida=optarg;
				printf("Nome do arquivo de saida: %s\n", saida);
				errS++;
				break;

			case 'e':
				entrada=optarg;
				printf("Nome do arquivo de entrada: %s\n", entrada);
				errE++;
				break;


			case '?':
				fprintf(stderr, "\nFALTA PARAMETROS\n");

			default:
				fprintf(stderr, "%s \nparametros:\n-e arquivo de entrada\n-s arquivo de saida\n", argv[0]);
				exit(EXIT_FAILURE);
		}

	}
	if (!(errS&errE)) {
		fprintf(stderr, "\nFALTA ARGUMENTOS\n");
		if(!errS)
			fprintf(stderr, "-s NOME ARQUIVO SAIDA \n");
		if(!errE)
			fprintf(stderr, "-e NOME ARQUIVO ENTRADA \n");
		exit(1);
	}

	fentrada = fopen(entrada,"r");

	sprintf(tmp,"\narquivo de entrada %s",entrada);
	set_log(tmp);

	fscanf(fentrada,"%d",&numero_layers); //numero layers
	sprintf(tmp,"\nnumero de layers %d",numero_layers);
	set_log(tmp);

	layers = (int*)malloc(sizeof(int)); 
	fscanf(fentrada,"%d",&layers[0]); // layer
	sprintf(tmp,"\nnumero de neuronios no layer 1 %d",layers[0]);
	set_log(tmp);

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

	sprintf(tmp,"\nFIM CREATE\n ");
	set_log(tmp);
	fclose(fentrada);

}
