#include <stdio.h>
#include <stdlib.h>
#include "fann/floatfann.h"


FILE file_name;

unsigned int rec_log = 1;
void set_rec_log(unsigned int flag_rec){
    rec_log = flag_rec;
}

static void set_log( char * mensagem){      // log error
    FILE *log_file = fopen("log.txt", "a");
    if (log_file == NULL){
        printf("Error opening log file!\n");
        exit(1);
    }

    if(rec_log){
        fprintf( log_file,"%s",mensagem );
    }

    fclose(log_file);
}

struct fann * create_neural_net( const unsigned int* layers,
                                unsigned int size_layer,
                                unsigned int shortcut,
                                unsigned int * layer_activation_function ){
    size_t count_layer;
    struct fann * ann;
    char * log_men;
    log_men = "Numero de layers ";
   // sprintf(log_men,"%s %d",log_men,size_layer);

    if(shortcut)
        ann = fann_create_shortcut_array(size_layer,layers);
    else
        ann = fann_create_standard_array(size_layer,layers);

    for(count_layer=1;count_layer<size_layer;count_layer++)
        fann_set_activation_function_layer( ann,layer_activation_function[count_layer],count_layer);

    set_log("rede criada\n");

    //free(log_men);
    log_men= NULL;
    return ann;

}

void set_activation_function_hidden_and_out(struct fann * ann, int name_func_hidden, int name_func_out){

    fann_set_activation_function_hidden( ann, name_func_hidden );
    fann_set_activation_function_output( ann, name_func_out );
}

int save_neural_net(struct fann * ann, char * file_save ){

    return fann_save(ann,file_save);

}

void train(struct fann * ann,
           const char * train_file,
           unsigned int max_epochs,
           unsigned int epochs_between_reports,
           unsigned int desired_error,
           const char * file_save ){

    fann_train_on_file(ann, train_file, max_epochs, epochs_between_reports, desired_error);
    fann_save(ann, file_save);

}

struct fann * load_neural_net_from_file(const char * file_neural_net){
    struct fann * ann = fann_create_from_file(file_neural_net);
    return ann;
}

static void data_to_vec_input(float * data , fann_type * in, unsigned int size){
    unsigned int i;
    for(i = 0 ; i < size; i++)
        in[i] = data[i];
}

static float * normalized_vector(float * vec, unsigned int size){
    int i;
    float * ret;
    float maior = vec[0];
    for(i=1;i<size;i++)
        if(maior < vec[i])
            maior = vec[i];

    ret = malloc(size*sizeof(float));

    for(i = 0 ; i < size ; i++)
        ret[i] = vec[i]/maior;

    return ret;
}

static int readFile(char * file_name, float * data){
    FILE * file;
    float point_on_file;
    data = NULL;



    if ((file=fopen(file_name, "rb")) == NULL) {
        // error log and exit
    }

    int i = 0 ;
    data = malloc( sizeof(float) );
    while(fread(&point_on_file, sizeof(float), 1,file)){
        if(i)
            data = realloc( data, (i+1)*sizeof(float) );
        data[i++] = point_on_file;

    }

    return i;
}

void exec_neural_net(char * file_name, struct fann * ann){

    fann_type *input;
    fann_type *calc_out;
    float *temp_input;
    float *data_file;
    int size_data_file;
    size_data_file = readFile(file_name,&data_file);
    temp_input = malloc(fann_get_num_input(ann)*sizeof(fann_type));
    input = malloc(fann_get_num_input(ann)*sizeof(fann_type));
    int i,j;
    for(i = 0; i < size_data_file; i++){
        for(j = i; fann_get_num_input(ann); j++)
            temp_input[j-i] = data_file[j];
        data_to_vec_input(normalized_vector(temp_input,fann_get_num_input),input,fann_get_num_input(ann));
        calc_out = fann_run(ann, input); // exec calc output from ann
    }


}


