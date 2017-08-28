#ifndef API_H
#define API_H

void set_rec_log(unsigned int flag_rec);

struct fann * create_neural_net(const unsigned int* layers,
                        unsigned int size_layer,
                        unsigned int shortcut,
                        unsigned int * layer_activation_function );

void train(struct fann * ann,
           const char * train_file,
           unsigned int max_epochs,
           unsigned int epochs_between_reports,
           unsigned int desired_error,
           const char * file_save );

#endif // API_H
