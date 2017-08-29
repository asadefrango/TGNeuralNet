#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "set_log.h"
#include "api/API_net.h"

int main(int argc, char **argv){
	set_log("\n\nTRAIN");
	bool isCaseInsensitive = false;
	int opt,i;
	FILE *fconf,ftreino;
	char *conf=NULL;
	char *rede=NULL;
	char *treino=NULL;
	char *saida=NULL;
	char tmp[100];
	float erro;
	unsigned int max,report;
	while ((opt = getopt(argc, argv, "n:t:m:r:e:s:")) != -1) {
		switch (opt) {

			case 'n':
				rede=optarg;
				printf("Nome do arquivo da rede: %s\n",rede);
				break;

			case 't':
				treino=optarg;
				printf("Nome do arquivo de treino: %s\n",treino);
				break;

			case 'm':
				max=strtoul(optarg,&tmp,10);
				printf("Numero maximo de epocas: %d\n",max);
				break;

			case 'r':
				report=strtoul(optarg,&tmp,10);
				printf("Numero de epocas ate reportar: %d\n",report);
				break;

			case 'e':
				erro = atof(optarg);
				printf("erro desejado %f\n",erro);
				break;

			case 's':
				saida = optarg;
				printf("nome do arquivo de saida %s\n",saida);
				break;
			default:
				fprintf(stderr, "%s\nparametros:\n-n arquivo com a rede\n-t arquivo de treino\n-m numero maximo de epocas\n-r numero de epocas ate reportar o resultado parcial\n-e erro desejado\n-s nome do arquivo de saida\n", argv[0]);
				exit(EXIT_FAILURE);
		}

	}

	if(opterr){
		fprintf(stderr, "%s\nparametros:\n-n arquivo com a rede\n-t arquivo de treino\n-m numero maximo de epocas\n-r numero de epocas ate reportar o resultado parcial\n-e erro desejado\n-s nome do arquivo de saida\n", argv[0]);
		exit(EXIT_FAILURE);
	}
struct fann * ann = load_neural_net_from_file(rede);
	sprintf(tmp,"\nrede carregada de %s",rede);
	set_log(tmp);
	
	
train(ann,treino,max,report,erro,saida );


	sprintf(tmp,"\nFIM TRAIN\n ");
	set_log(tmp);


}

