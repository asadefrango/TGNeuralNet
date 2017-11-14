#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "set_log.h"
#include "api/API_net.h"

int main(int argc, char **argv){
	set_log("\n\nGEN_TRAIN");
	bool isCaseInsensitive = false;
	unsigned int errL=0,errS=0,errI=0,errO=0,errP=0,errE=0,errT=0,errD=0,errX=0;
	int opt,i;
	FILE *fsaida;
	char *entrada=NULL;
	char *saida=NULL;
	char *lista=NULL;
	char tmp[100];
	float *data,tr,t,dt,*picks;
	int numero_entrada,numero_saida,pick;
	while ((opt = getopt(argc, argv, "l:s:i:o:p:e:t:d:x:")) != -1) {
		switch (opt) {

			case 'l':
				lista=optarg;
				printf("Nome do arquivo com lista de picks: %s\n", lista);
				errL++;
				break;

			case 's':
				saida=optarg;
				printf("Nome do arquivo de saida: %s\n", saida);
				errS++;
				break;

			case 'i':
				numero_entrada=atoi(optarg);
				printf("Numero de entradas: %d\n", numero_entrada);
				errI++;
				break;

			case 'o':
				numero_saida=atoi(optarg);
				printf("Numero de saidas: %d\n", numero_saida);
				errO++;
				break;

			case 'p':
				pick=atoi(optarg);
				printf("posicao do pick na janela %d\n", pick);
				errP++;
				break;

			case 'e':
				entrada=optarg;
				printf("Nome do arquivo de entrada: %s\n", entrada);
				errE++;
				break;

			case 't':
				tr=atoi(optarg);
				printf("Numero de Tracos: %d\n",tr);
				errT++;
				break;

			case 'd':
				t=atof(optarg);
				printf("Numero de amostras por traco: %f\n",t);
				errD++;
				break;

			case 'x':
				dt=atof(optarg);
				printf("taxa de amostragem: %f\n",dt);
				errX++;
				break;

			case '?':
				fprintf(stderr, "\nFALTA PARAMETROS\n");

			default:
				fprintf(stderr, "%s \nparametros:\n-l lista de picks(numero do pick absoluto)\n-e arquivo de entrada\n-s arquivo de saida\n-i numero de entradas\n-o numero de saidas\n-p posicao do pick na janela\n-t numero de tracos\n-d numero de amostras por traco \n-x taxa de amostragem", argv[0]);
				exit(EXIT_FAILURE);
		}

	}
	int aa = errL&errS&errI&errO&errP&errE&errT&errD&errX;
	if(!(aa)) {
		fprintf(stderr, "\nFALTA ARGUMENTOS %d\n",aa );
		if(!errS)
			fprintf(stderr, "-s NOME ARQUIVO SAIDA\n");
		if(!errE)
			fprintf(stderr, "-e NOME ARQUIVO ENTRADA\n");
		if(!errL)
			fprintf(stderr, "-l NOME DO ARQUIVO COM LISTA DE PICKS\n");
		if(!errI)
			fprintf(stderr, "-i NUMERO DE ENTRADAS\n");
		if(!errO)
			fprintf(stderr, "-o NUMERO DE SAIDAS\n");
		if(!errP)
			fprintf(stderr, "-p POSICAO DO PICK NA JANELA\n");
		if(!errT)
			fprintf(stderr, "-t NUMERO DE TRACOS\n");
		if(!errD)
			fprintf(stderr, "-d NUMERO DE AMOSTRAS POR TRACO \n");
		if(!errX)
			fprintf(stderr, "-x TAXA DE AMOSTRAGEM \n");

		exit(EXIT_FAILURE);
	}

	sprintf(tmp,"\narquivo de entrada %s",entrada);
	set_log(tmp);

	sprintf(tmp,"\narquivo de saida %s",saida);
	set_log(tmp);

	sprintf(tmp,"\nlendo arquivo de entrada...");
	set_log(tmp);

	readFile(entrada,data);
	sprintf(tmp,"\nlendo list de picks...");
	set_log(tmp);
	int lenPick = readFilePicks(lista,picks,dt,t);
	int *index;
	int j=1,k,x;

	index =(int *) malloc(sizeof(int));
	for(k = 0; k < tr*dt; k +=dt )
		for(i = - numero_entrada ; i < dt + numero_entrada ; i++){

			if( i < 0 || i >= dt )
				index[j] = -1;  
			else 
				index[j]=i+k;
			index = (int *) realloc(index,++j*sizeof(int));
		}
	float *res;
	res = (float  *)malloc(numero_entrada*sizeof(float));
	for(i = 0; i < lenPick; i++){
		for(k = 0; k < j; k++)
			if(picks[i]==index[k])
				for( x = 0 ; x < numero_entrada ; x++ ){
					if(index[k+x-pick] < 0)
						res[x] = 0;
					else 
						res[x] = data[index[k + x - pick]];

				}
	}

	fsaida = fopen(saida,'w');	
	fprintf(fsaida,"%d %d %d\n",lenPick,numero_entrada,numero_saida);
	for(i = 0 ; i < lenPick; i++){
		for(x = 0 ; x < numero_entrada ; x++)
			fprintf(fsaida,"%f ",res[x]);
		fprintf(fsaida,"\n1 ");
	}
	fclose(fsaida);

	sprintf(tmp,"\nFIM GEN_TRAIN\n");
	set_log(tmp);
}
