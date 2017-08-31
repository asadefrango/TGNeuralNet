#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "set_log.h"
#include "api/API_net.h"

int main(int argc, char **argv){
	set_log("\n\nGEN_TRAIN");
	bool isCaseInsensitive = false;
	int opt,i,dt;
	FILE *fsaida;
	char *entrada=NULL;
	char *saida=NULL;
	char *lista=NULL;
	char tmp[100];
	float *data,tr,*picks;
	int numero_entrada,numero_saida,pick;
	while ((opt = getopt(argc, argv, "l:s:i:o:p:e:t:d:")) != -1) {
		switch (opt) {

			case 'l':
				lista=optarg;
				printf("Nome do arquivo com lista de picks: %s\n", lista);
				break;

			case 's':
				saida=optarg;
				printf("Nome do arquivo de saida: %s\n", saida);
				break;

			case 'i':
				numero_entrada=atoi(optarg);
				printf("Numero de entradas: %d\n", numero_entrada);
				break;

			case 'o':
				numero_saida=atoi(optarg);
				printf("Numero de saidas: %d\n", numero_saida);
				break;

			case 'p':
				pick=atoi(optarg);
				printf("posicao do pick na janela %d\n", pick);
				break;

			case 'e':
				entrada=optarg;
				printf("Nome do arquivo de entrada: %s\n", entrada);
				break;

			case 't':
				tr=atoi(optarg);
				printf("Numero de saidas: %d\n",tr);
				break;

			case 'd':
				dt=atof(optarg);
				printf("Numero de saidas: %f\n",dt);
				break;

			default:
				fprintf(stderr, "%s \nparametros:\n-l lista de picks(tempo)\n-e arquivo de entrada\n-s arquivo de saida\n-i numero de entradas\n-o numero de saidas\n-p posicao do pick na janela\n-t numero de tracos\n-dtaxa de amostragem", argv[0]);
				exit(EXIT_FAILURE);
		}

	}
	if(opterr){
				fprintf(stderr, "%s \nparametros:\n-e arquivo de entrada\n-s arquivo de saida\n-i numero de entradas\n-o numero de saidas\n-p posicao do pick na janela\n-t numero de tracos\n-dtaxa de amostragem", argv[0]);
		exit(EXIT_FAILURE);
	}

	sprintf(tmp,"\narquivo de entrada %s",entrada);
	set_log(tmp);

	sprintf(tmp,"\narquivo de saida %s",saida);
	set_log(tmp);

	sprintf(tmp,"\nlendo arquivo de entrada...");
	set_log(tmp);

	readFile(entrada,data);
	readFile(lista,picks);
	
	

       
	sprintf(tmp,"\nFIM GEN_TRAIN\n ");
	set_log(tmp);

}
