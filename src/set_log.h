#ifndef SETLOG_H
#define SETLOG_H
#include <stdio.h>

void set_log( char * mensagem){      // log error
	FILE *log_file = fopen("log.txt", "a");
	if (log_file == NULL){
		printf("Error opening log file!\n");
		exit(1);
	}

	fprintf(log_file,"%s\n",mensagem);

	fclose(log_file);
	log_file = NULL;
}



#endif
